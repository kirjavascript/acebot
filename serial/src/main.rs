use serial2::SerialPort;
use std::{thread, time};
use std::io::{Read, Write};

fn main() {

    let movie = include_str!("../../Input Log.txt");
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
    println!("{} frames, {} banks", bytes.len(), bytes.len() / 256);

    let mut data = [0 as u8; 256];

    let port = SerialPort::open("/dev/ttyACM0", 115200).expect("no connection");
    while match port.read(&mut data) {
        Ok(_size) => {
            let chunk = data[0] as usize;
            let write = port.write(&bytes[chunk * 256..((chunk+1) * 256)]);
            if let Err(err) = write {
                println!("{:#?}", err);
            } else {
                println!("w {}", data[0]);
            }
            true
        },
            Err(e) => {
                println!("--{}--", e);
                true
            }
    } {}


}
