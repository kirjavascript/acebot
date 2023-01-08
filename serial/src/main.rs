use serial2::SerialPort;
use std::{thread, time};
use std::io::{Read, Write};

fn main() {
    let port = SerialPort::open("/dev/ttyACM0", 115200).expect("no connection");

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

    let mut data = [0 as u8; 256];
    while match port.read(&mut data) {
        Ok(size) => {
            let chunk = data[0] as usize;
            port.write(&bytes[chunk * 256..((chunk+1) * 256)]);
            println!("w {}", data[0]);

            thread::sleep(time::Duration::from_millis(1));
            true
        },
            Err(e) => {
                println!("{}", e);
                thread::sleep(time::Duration::from_millis(1));
                true
            }
    } {}
}
