use byteorder::{BigEndian, ReadBytesExt, WriteBytesExt};
use std::{
    cmp::Ordering,
    collections::{BinaryHeap, HashMap},
    fs::File,
    io::{self, Cursor, Read, Write},
};
use utf8_read::Reader;

#[derive(Debug)]
enum Huffman {
    Leaf {
        char: char,
        freq: u32,
    },
    Node {
        freq: u32,
        min_char: char,
        left: Box<Huffman>,
        right: Box<Huffman>,
    },
}

impl PartialEq for Huffman {
    fn eq(&self, other: &Self) -> bool {
        self.freq() == other.freq() && self.min_char() == other.min_char()
    }
}

impl Eq for Huffman {}

impl PartialOrd for Huffman {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for Huffman {
    fn cmp(&self, other: &Self) -> Ordering {
        match other.freq().cmp(&self.freq()) {
            Ordering::Equal => self.min_char().cmp(&other.min_char()).reverse(),
            other => other,
        }
    }
}

impl Huffman {
    fn freq(&self) -> u32 {
        match self {
            Huffman::Leaf { freq, .. } => *freq,
            Huffman::Node { freq, .. } => *freq,
        }
    }

    fn min_char(&self) -> char {
        match self {
            Huffman::Leaf { char, .. } => *char,
            Huffman::Node { min_char, .. } => *min_char,
        }
    }

    fn generate_codes(&self, prefix: String, codes: &mut HashMap<char, String>) {
        match self {
            Huffman::Leaf { char, .. } => {
                codes.insert(*char, prefix);
            }
            Huffman::Node { left, right, .. } => {
                left.generate_codes(format!("{}0", prefix), codes);
                right.generate_codes(format!("{}1", prefix), codes);
            }
        }
    }
}

// Frequency and Tree generation functions
fn generate_frequency_map<R: io::Read>(mut file: Reader<R>) -> HashMap<char, u32> {
    let mut map: HashMap<char, u32> = HashMap::new();

    file.into_iter().for_each(|c| {
        if let Ok(char) = c {
            map.entry(char).and_modify(|count| *count += 1).or_insert(1);
        }
    });

    map
}

fn build_huffman_tree(freq_map: &HashMap<char, u32>) -> Option<Huffman> {
    let mut queue: BinaryHeap<Huffman> = freq_map
        .iter()
        .map(|(&char, &freq)| Huffman::Leaf { char, freq })
        .collect();

    while queue.len() > 1 {
        let left = queue.pop().unwrap();
        let right = queue.pop().unwrap();

        let new_freq = left.freq() + right.freq();
        let new_node = Huffman::Node {
            freq: new_freq,
            min_char: left.min_char().min(right.min_char()),
            left: Box::new(left),
            right: Box::new(right),
        };

        queue.push(new_node);
    }

    queue.pop()
}


//Compression functions
fn read_file(path: &str) -> Result<Reader<File>, std::io::Error> {
    let file = File::open(path)?;
    let reader = Reader::new(file);

    Ok(reader)
}

fn byte_encode(text: &str, codes: &HashMap<char, String>) -> Vec<u8> {
    let mut bitstring = text
        .chars()
        .filter_map(|c| codes.get(&c))
        .map(String::as_str)
        .collect::<String>();

    let padding = (8 - (bitstring.len() % 8)) % 8;
    for _ in 0..padding {
        bitstring.push('0');
    }

    bitstring
        .as_bytes()
        .chunks(8)
        .map(|chunk| {
            let chunk_str = std::str::from_utf8(chunk).unwrap();
            u8::from_str_radix(chunk_str, 2).unwrap()
        })
        .collect()
}

fn write_binary_file(
    output_path: &str,
    freq_map: &HashMap<char, u32>,
    encoded_data: &[u8],
) -> io::Result<()> {
    let mut buffer = Cursor::new(Vec::new());
    let mut file = File::create(output_path)?;

    let n = freq_map.len() as u16;
    let t: u32 = freq_map.values().copied().sum();

    buffer.write_u16::<BigEndian>(n)?;
    buffer.write_u32::<BigEndian>(t)?;

    freq_map.iter().try_for_each(|(&ch, &freq)| {
        buffer.write_u32::<BigEndian>(ch as u32)?;
        buffer.write_u32::<BigEndian>(freq)
    })?;

    buffer.write_all(encoded_data)?;
    file.write_all(buffer.get_ref())?;
    Ok(())
}


// Decompression functions
fn read_compressed_file(path: &str) -> (HashMap<char, u32>, Vec<u8>, u32) {
    let mut file = File::open(path).unwrap();
    let mut buffer_vec = Vec::new();
    file.read_to_end(&mut buffer_vec).unwrap();

    let mut buffer = Cursor::new(buffer_vec);
    let n = buffer.read_u16::<BigEndian>().unwrap();
    let total_chars = buffer.read_u32::<BigEndian>().unwrap();

    let freq_map = (0..n)
        .map(|_| {
            let char_code = buffer.read_u32::<BigEndian>().unwrap();
            let freq = buffer.read_u32::<BigEndian>().unwrap();
            let c = char::from_u32(char_code).unwrap();
            (c, freq)
        })
        .collect::<HashMap<_, _>>();

    let mut encoded_data = Vec::new();
    buffer.read_to_end(&mut encoded_data).unwrap();

    (freq_map, encoded_data, total_chars)
}

fn decode_data(encoded_data: &[u8], tree: &Huffman, total_chars: u32) -> String {
    let mut result = String::with_capacity(total_chars as usize);
    let mut node = tree;
    let mut decoded_count = 0;

    for &byte in encoded_data {
        for i in (0..8).rev() {
            let bit = (byte >> i) & 1;

            node = match node {
                Huffman::Node { left, right, .. } => {
                    if bit == 0 {
                        left
                    } else {
                        right
                    }
                }
                Huffman::Leaf { char, .. } => {
                    result.push(*char);
                    decoded_count += 1;
                    if decoded_count == total_chars {
                        return result;
                    }
                    if bit == 0 {
                        match tree {
                            Huffman::Node { left, .. } => left,
                            Huffman::Leaf { .. } => panic!("Tree with single leaf"),
                        }
                    } else {
                        match tree {
                            Huffman::Node { right, .. } => right,
                            Huffman::Leaf { .. } => panic!("Tree with single leaf"),
                        }
                    }
                }
            };
        }
    }

    if let Huffman::Leaf { char, .. } = node {
        if decoded_count < total_chars {
            result.push(*char);
        }
    }

    result
}

fn main() {
    let input_path = "example.txt";
    let compressed_path = "output.bin";
    let decompressed_output_path = "decoded_output.txt";

    let file = read_file(input_path).unwrap();
    let freq_map = generate_frequency_map(file);
    let tree = build_huffman_tree(&freq_map).expect("Input is empty");

    let mut codes = HashMap::new();
    tree.generate_codes(String::new(), &mut codes);

    let text: String = read_file(input_path)
        .unwrap()
        .filter_map(Result::ok)
        .collect();

    let encoded = byte_encode(&text, &codes);
    write_binary_file(compressed_path, &freq_map, &encoded).unwrap();

    let (freq_map_dec, encoded_data, total_chars) = read_compressed_file(compressed_path);
    let tree_dec = build_huffman_tree(&freq_map_dec).expect("Invalid Huffman tree");

    let decoded_text = decode_data(&encoded_data, &tree_dec, total_chars);
    let mut output_file = File::create(decompressed_output_path).unwrap();
    write!(output_file, "{}", decoded_text).unwrap();
}
