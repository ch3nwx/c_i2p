// 10998 — doubly-linked list used as LIFO stack (head = top).
// In Rust, prevPtr is unnecessary for any operation so we use a singly-linked list.
use crate::scanner::Scanner;

struct Node {
    data: i32,
    next: Option<Box<Node>>,
}

struct ListStack {
    head: Option<Box<Node>>,
}

impl ListStack {
    fn new() -> Self {
        ListStack { head: None }
    }

    fn push(&mut self, v: i32) {
        self.head = Some(Box::new(Node { data: v, next: self.head.take() }));
    }

    fn pop(&mut self) {
        if let Some(node) = self.head.take() {
            self.head = node.next;
        }
    }

    fn print(&self) {
        let mut curr = &self.head;
        let mut first = true;
        while let Some(node) = curr {
            if !first { print!(" "); }
            print!("{}", node.data);
            first = false;
            curr = &node.next;
        }
        println!();
    }
}

pub fn run() {
    let mut sc = Scanner::new();
    let mut stack = ListStack::new();
    while sc.has_next() {
        let cmd: String = sc.next();
        match cmd.as_str() {
            "push" => { let n: i32 = sc.next(); stack.push(n); }
            "pop"  => stack.pop(),
            "print" => stack.print(),
            _ => {}
        }
    }
}
