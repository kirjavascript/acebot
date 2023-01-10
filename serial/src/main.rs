use serial2::SerialPort;
use std::{thread, time};
use std::io::{Read, Write};
use std::fs::File;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let mut file = File::open(&args.get(1).expect("cargo run -- ./inputs.txt"))
        .expect("error opening file");

    let mut movie = String::new();
    file.read_to_string(&mut movie).expect("error reading file");

    let lines = movie.split('\n').collect::<Vec<&str>>();
    let mut bytes = Vec::new();
    for line in &lines[2..lines.len()-2] {
        let line = &line[4..12];
        let mut byte = 0;
        for (i, ch) in line.chars().enumerate() {
            let shift = 7-i;
            if ch != '.' {
                byte += 1 << shift;
            }
        }
        bytes.push(byte);
    }

    let len = bytes.len();
    println!("{} frames, {} banks", len, len / 256);

    let mut data = [0 as u8; 256];

    let port = SerialPort::open("/dev/ttyACM0", 9600).expect("no connection");

    loop {
        match port.read(&mut data) {
        Ok(_size) => {
            let chunk = data[0] as usize;
            let start = chunk * 256;
            let end = (chunk+1) * 256;
            if end > len {
                let write = port.write(&bytes[start..len]);
                let write2 = port.write(&bytes[0..end - len]);
                println!("{:#?} {:#?}", write, write2);
                return;
            } else {
                let write = port.write(&bytes[start..end]);
                if let Err(err) = write {
                    println!("{:#?}", err);
                } else {
                    println!("chunk {}", data[0]);
                }
            }
        },
            Err(e) => {
                println!("--{}--", e);
            }
        }
    }

}
