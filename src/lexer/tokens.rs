#![allow(dead_code)]

use std::str::FromStr;

#[derive(Clone, Copy, PartialEq, Debug)]
pub enum CommentKind {
    Line,
    Block,
}

pub struct CommentError {
    pub msg: std::string::String,
}

impl CommentError {
    pub fn new() -> Self {
        Self {
            msg: "how did you fail this one lol".to_string(),
        }
    }
}

#[derive(Clone, PartialEq, Hash, Debug, Copy)]
pub enum OpToken {
    Assign,
    Plus,
    Minus,
    Power,
    Divide,
    Percent,
    And,
    Or,
}

pub struct ParseErr {
    pub msg: std::string::String,
}

impl ParseErr {
    pub fn new() -> Self {
        Self {
            msg: "Invalid operation token, you idiot. Try harder.".to_string(),
        }
    }
}


impl FromStr for OpToken {
    type Err = ParseErr;
    
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            "hogtie" => Ok(OpToken::Assign),
            "+" => Ok(OpToken::Plus),
            "-" => Ok(OpToken::Minus),
            "*" => Ok(OpToken::Power),
            "/" => Ok(OpToken::Divide),
            "%" => Ok(OpToken::Percent),
            "&&" => Ok(OpToken::And),
            "||" => Ok(OpToken::Or),
            _ => Err(ParseErr::new()),
        }
    }
}

#[derive(Copy, Clone, Debug, PartialEq, Eq, Hash)]
pub enum Delimiter {
    OpeningCurlyBrace,
    ClosingCurlyBrace,
    OpeningBracket,
    ClosingBracket,
    OpeningParenthesis,
    CloseingParenthesis,
    Semicolon,
}

pub enum LitKind {
    Bool,
    Byte,
    Char,
    Integer,
    Float,
    Str,
    StrRaw(u8),
    ByteStr,
    ByteStrRaw(u8),
}


