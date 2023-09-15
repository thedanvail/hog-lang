pub mod tokens;

pub struct Lexer;

impl Lexer {
    
    // A very naive approach to lexing
    pub fn lex(txt: &str) {
        let mut lines = get_lines_by_delim(txt);

    }

    fn get_lines_by_delim(txt: &str) -> Vec<&str> {
        txt.split(";");
    }

}

