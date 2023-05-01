use std::fmt;
use std::path::Path;
use std::fs::File;
use std::collections::BTreeMap;
use std::error::Error;

pub struct LinkError<'a> {
    pub msg: &'a str
}

impl fmt::Debug for LinkError<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Zelda error no wait I mean link error, something happened here I guess: {:?}", self.msg)   
    }
}

impl fmt::Display for LinkError<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Zelda error no wait I mean link error, something happened here I guess: {:?}", self.msg)   
    }
}

pub struct LinkedFiles {
    pub tree: BTreeMap<String, File>,
}

impl LinkedFiles {
    pub fn new() -> Self {
        Self {
            tree: BTreeMap::new(),
        }
    }

    pub fn link_file(&mut self, path: &str) -> Result<(), LinkError> {
        if let Some(_) = self.tree.get(path) {
            return Ok(());
        }
        let fp = Path::new(path);
        if let Ok(file) = File::open(fp) {
            self.tree.insert(path.to_string(), file);
            return Ok(());
        };
        Err(LinkError{ msg: "Yeah homie that file looks made up to me try again lol" })
    }
}
