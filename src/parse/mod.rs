pub mod line;

use proc_macro::TokenStream;

use std::fmt;

pub enum Ops {
    Assign,
}

pub struct Parser;

pub struct ParseError<'a> {
    pub msg: &'a str,
}

impl fmt::Debug for ParseError<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "You suck, something happened here I guess: {:?}", self.msg)   
    }
}

impl fmt::Display for ParseError<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "You suck, something happened here I guess: {:?}", self.msg)   
    }
}

impl Parser {
    pub fn parse(text: &str) -> TokenStream {
        todo!()
    }

    pub fn parse_block(text_block: &str) -> TokenStream {
        todo!()
    }

    pub fn parse_line(text_line: &str) -> Result<&[&str], ParseError> {
        
    }
}
