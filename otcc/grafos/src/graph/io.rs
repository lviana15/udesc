use std::{
    fmt,
    fs::File,
    io::{self, BufRead, BufReader},
    num::ParseIntError,
    path::PathBuf,
};

use super::{data_structures::Graph, errors::GraphError};

enum GraphParseError {
    IoError(io::Error),
    ParseError(ParseIntError),
    InvalidFormat(String),
}

impl From<io::Error> for GraphParseError {
    fn from(err: io::Error) -> Self {
        GraphParseError::IoError(err)
    }
}

impl From<ParseIntError> for GraphParseError {
    fn from(err: ParseIntError) -> Self {
        GraphParseError::ParseError(err)
    }
}

impl fmt::Display for GraphParseError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            GraphParseError::IoError(err) => write!(f, "I/O Error: {}", err),
            GraphParseError::ParseError(err) => write!(f, "Parse Error: {}", err),
            GraphParseError::InvalidFormat(msg) => write!(f, "Invalid Format: {}", msg),
        }
    }
}

pub fn parse_from_file<T>(path: PathBuf) -> Result<Vec<(u32, u32)>, GraphParseError> {
    let file = File::open(path)?;
    let reader = BufReader::new(file);

    reader
        .lines()
        .enumerate()
        .map(|(index, line)| {
            let line = line.map_err(GraphParseError::IoError)?;
            let mut pair = line
                .split_whitespace()
                .map(|num| num.parse::<u32>().map_err(GraphParseError::ParseError));

            match (pair.next(), pair.next()) {
                (Some(Ok(start)), Some(Ok(end))) => Ok((start, end)),
                _ => Err(GraphParseError::InvalidFormat(format!(
                    "Line {} is invalid: '{}'",
                    index + 1,
                    line
                ))),
            }
        })
        .collect()
}
