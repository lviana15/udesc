use std::{
    collections::HashMap,
    thread,
    time::{Duration, Instant},
};

struct BenchmarkResult {
    n: usize,
    single_threaded_ms: u128,
    multithreaded_ms: HashMap<usize, u128>, // threads => ms
}

use plotters::prelude::*;

fn plot_results(results: &[BenchmarkResult]) {
    let root = BitMapBackend::new("bench.png", (800, 600)).into_drawing_area();
    root.fill(&WHITE).unwrap();

    let max_time = results
        .iter()
        .flat_map(|r| {
            std::iter::once(r.single_threaded_ms).chain(r.multithreaded_ms.values().cloned())
        })
        .max()
        .unwrap_or(1);

    let mut chart = ChartBuilder::on(&root)
        .caption("Prime Computation Benchmark", ("sans-serif", 30))
        .margin(20)
        .x_label_area_size(40)
        .y_label_area_size(60)
        .build_cartesian_2d(
            results.iter().map(|r| r.n).min().unwrap() as f64
                ..results.iter().map(|r| r.n).max().unwrap() as f64,
            0f64..max_time as f64 * 1.1,
        )
        .unwrap();

    chart
        .configure_mesh()
        .x_desc("Input Size (n)")
        .y_desc("Avg Time (ms)")
        .x_label_formatter(&|x| format!("{}", *x as usize))
        .draw()
        .unwrap();

    // Plot single-threaded
    chart
        .draw_series(LineSeries::new(
            results
                .iter()
                .map(|r| (r.n as f64, r.single_threaded_ms as f64)),
            &RED,
        ))
        .unwrap()
        .label("Single-threaded")
        .legend(|(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], &RED));

    let colors = [&BLUE, &GREEN, &MAGENTA];
    for (i, &threads) in [2, 4, 8].iter().enumerate() {
        let color = colors[i % colors.len()];
        chart
            .draw_series(LineSeries::new(
                results.iter().map(|r| {
                    (
                        r.n as f64,
                        *r.multithreaded_ms.get(&threads).unwrap_or(&0) as f64,
                    )
                }),
                color,
            ))
            .unwrap()
            .label(format!("Multithreaded ({} threads)", threads))
            .legend(move |(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], color));
    }

    chart
        .configure_series_labels()
        .border_style(&BLACK)
        .draw()
        .unwrap();
}

fn single_threaded(n: u128) -> Vec<bool> {
    let mut primes = vec![true; (n + 1) as usize];

    primes[0] = false;
    primes[1] = false;

    if n >= 2 {
        for multiple in (2 * 2..=n as usize).step_by(2) {
            primes[multiple] = false;
        }
    }

    for i in 3..=n as usize {
        if primes[i] {
            for multiple in (i * i..=n as usize).step_by(2 * i) {
                primes[multiple] = false;
            }
        }
    }

    primes
}

fn multithreaded(n: u128, num_threads: u128) -> Vec<bool> {
    if n < 2 {
        return vec![];
    }

    let base_limit = (n as f64).sqrt() as u128;

    let base_flags = single_threaded(base_limit);

    let mut final_flags = vec![true; (n + 1) as usize];
    for i in 0..=(base_limit as usize) {
        if i < final_flags.len() {
            final_flags[i] = base_flags[i];
        }
    }

    let base_primes: Vec<usize> = base_flags
        .into_iter()
        .enumerate()
        .filter(|&(_, is_p)| is_p)
        .map(|(i, _)| i)
        .collect();

    let total_elements = n - base_limit + 1;
    let elements_per_thread = total_elements / num_threads;
    let remainder = total_elements % num_threads;

    let mut handles = vec![];
    let mut current_offset = 0;

    for i in 0..num_threads {
        let mut segment_size = elements_per_thread;
        if (i as u128) < remainder {
            segment_size += 1;
        }

        let thread_start = base_limit + current_offset;
        let thread_end = (thread_start + segment_size - 1).min(n);

        if thread_start > thread_end {
            current_offset += segment_size;
            continue;
        }

        let base_primes_thread = base_primes.clone();

        let handle = thread::spawn(move || {
            let segment_len = (thread_end - thread_start + 1) as usize;
            let mut segment_flags = vec![true; segment_len];

            for &p in &base_primes_thread {
                if p * p > thread_end as usize {
                    break;
                }

                let start_node = (p * p).max(thread_start as usize);
                let current_multiple = ((start_node + p - 1) / p) * p;

                for multiple in (current_multiple..=thread_end as usize).step_by(p) {
                    let local_index = multiple - thread_start as usize;
                    segment_flags[local_index] = false;
                }
            }

            (segment_flags, thread_start)
        });

        handles.push(handle);
        current_offset += segment_size;
    }

    for handle in handles {
        let (segment_flags, segment_start) = handle.join().unwrap();

        for (segment_idx, &is_prime) in segment_flags.iter().enumerate() {
            let global_idx = (segment_start as usize) + segment_idx;
            final_flags[global_idx] = is_prime;
        }
    }

    final_flags
}

fn main() {
    let sizes = [100_000, 1_000_000, 10_000_000, 100_000_000, 1_000_000_000];
    let thread_counts = [2, 4, 8];
    let iterations = 1;
    let mut results = Vec::new();

    for &n in &sizes {
        println!("Testing with n = {}", n);

        let total_duration: Duration = (0..iterations)
            .map(|_| {
                let start = Instant::now();
                let _primes = single_threaded(n);
                start.elapsed()
            })
            .sum();

        let avg_single = total_duration.as_millis() / iterations as u128;

        println!(
            "  [Single-threaded] Avg duration: {} ms ({} iterations)",
            avg_single, iterations
        );

        let mut multi_results = HashMap::new();
        for &threads in &thread_counts {
            let total_duration: Duration = (0..iterations)
                .map(|_| {
                    let start = Instant::now();
                    let _primes = multithreaded(n, threads);
                    start.elapsed()
                })
                .sum();

            let avg_multi = total_duration.as_millis() / iterations as u128;

            println!(
                "  [Multithreaded {} threads] Avg duration: {} ms ({} iterations)",
                threads, avg_multi, iterations
            );
            multi_results.insert(threads as usize, avg_multi);
        }

        results.push(BenchmarkResult {
            n: n as usize,
            single_threaded_ms: avg_single,
            multithreaded_ms: multi_results,
        });

        println!();
    }

    plot_results(&results);
}
