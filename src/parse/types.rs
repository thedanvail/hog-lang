#![allow(dead_code)]

#[derive(Clone, Copy, PartialEq, Debug)]
pub enum CommentKind {
    Line,
    Block,
}

#[derive(Clone, PartialEq, Hash, Debug, Copy)]
pub enum OpToken {
    Plus,
    Minus,
    Star,
    Slash,
    Percent,
    Caret,
    And,
    Or,
    Shl,
    Shr,
}

#[derive(Copy, Clone, Debug, PartialEq, Eq, Hash)]
pub enum Delimiter {
    Brace,
    Bracket,
    Invisible,
    Parenthesis,
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
    Err,
}


