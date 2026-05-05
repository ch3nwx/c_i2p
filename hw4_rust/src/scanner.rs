use std::io::{self, Read};

pub struct Scanner {
    tokens: Vec<String>,
    pos: usize,
}

impl Scanner {
    pub fn new() -> Self {
        let mut input = String::new();
        io::stdin().read_to_string(&mut input).unwrap();
        Scanner {
            tokens: input.split_whitespace().map(String::from).collect(),
            pos: 0,
        }
    }

    pub fn next<T: std::str::FromStr>(&mut self) -> T
    where
        T::Err: std::fmt::Debug,
    {
        let tok = self.tokens[self.pos].parse().unwrap();
        self.pos += 1;
        tok
    }

    pub fn has_next(&self) -> bool {
        self.pos < self.tokens.len()
    }
}
