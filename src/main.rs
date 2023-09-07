#![allow(dead_code, unused_imports)]

extern crate proc_macro;

mod parse;
mod link;
mod lexer;

use clap::Command;

fn main() {
    println!("Pretending to compile hog lang.");
    println!("I really don't know why you would do this.");

    let current_dir = std::path::Path::new("./src");
    println!("{:?}", current_dir);
    assert!(current_dir.exists(), "No directory '/src/' was found. I can't believe how quickly you failed.");
}
