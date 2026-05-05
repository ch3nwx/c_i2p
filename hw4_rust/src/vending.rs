// 14927 — min-heap vending machine implemented manually (no BinaryHeap).
// store = push + sift-up, sell = pop-min + sift-down.
use crate::scanner::Scanner;

struct VendingMachine {
    data: Vec<i32>,
    total_revenue: i64,
    total_sold: i32,
}

impl VendingMachine {
    fn new() -> Self {
        VendingMachine {
            data: Vec::with_capacity(16),
            total_revenue: 0,
            total_sold: 0,
        }
    }

    fn store(&mut self, price: i32) {
        self.data.push(price);
        let mut i = self.data.len() - 1;
        while i > 0 {
            let p = (i - 1) / 2;
            if self.data[p] > self.data[i] {
                self.data.swap(p, i);
                i = p;
            } else {
                break;
            }
        }
    }

    fn sell(&mut self) {
        if self.data.is_empty() { return; }
        self.total_sold += 1;
        self.total_revenue += self.data[0] as i64;
        let last = self.data.pop().unwrap();
        if self.data.is_empty() { return; }
        self.data[0] = last;
        let mut i = 0;
        loop {
            let l = 2 * i + 1;
            let r = 2 * i + 2;
            let mut s = i;
            let len = self.data.len();
            if l < len && self.data[l] < self.data[s] { s = l; }
            if r < len && self.data[r] < self.data[s] { s = r; }
            if s == i { break; }
            self.data.swap(i, s);
            i = s;
        }
    }

    fn print_result(&self) {
        println!("{} {}", self.total_sold, self.total_revenue);
    }
}

pub fn run() {
    let mut sc = Scanner::new();
    let mut vm = VendingMachine::new();
    while sc.has_next() {
        let cmd: String = sc.next();
        match cmd.as_str() {
            "store" => { let price: i32 = sc.next(); vm.store(price); }
            "sell"  => vm.sell(),
            _ => {}
        }
    }
    vm.print_result();
}
