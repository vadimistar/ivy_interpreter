use std::io::{self, Write};

fn main() {
    println!("Ivy interpreter v0.1");
    loop {
        print!(">>> ");
        let _ = io::stdout().flush();

        let mut input = String::new(); 
        io::stdin().read_line(& mut input).unwrap();

        match input.as_str() {
            "quit\n" => break,
            u => print!("Unknown option: {}", u),
        }
    }
}
