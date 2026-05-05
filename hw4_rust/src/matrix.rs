// 14605 — N×N matrix with add/subtract/multiply/transpose/power.
// power uses fast exponentiation (binary exponentiation), O(n^3 log x).
use crate::scanner::Scanner;

struct Matrix {
    n: usize,
    data: Vec<Vec<i64>>,
}

// Free function so power() can square `base` without a self-borrow conflict.
fn mat_mul(a: &[Vec<i64>], b: &[Vec<i64>], n: usize) -> Vec<Vec<i64>> {
    let mut r = vec![vec![0i64; n]; n];
    for i in 0..n {
        for k in 0..n {
            let a_ik = a[i][k];
            if a_ik == 0 { continue; }
            for j in 0..n {
                r[i][j] += a_ik * b[k][j];
            }
        }
    }
    r
}

impl Matrix {
    fn from_grid(data: Vec<Vec<i64>>) -> Self {
        let n = data.len();
        Matrix { n, data }
    }

    fn print(&self) {
        for row in &self.data {
            for v in row { print!("{} ", v); }
            println!();
        }
    }

    fn add(&mut self, rhs: &Matrix) {
        for i in 0..self.n {
            for j in 0..self.n {
                self.data[i][j] += rhs.data[i][j];
            }
        }
    }

    fn subtract(&mut self, rhs: &Matrix) {
        for i in 0..self.n {
            for j in 0..self.n {
                self.data[i][j] -= rhs.data[i][j];
            }
        }
    }

    fn multiply(&mut self, rhs: &Matrix) {
        self.data = mat_mul(&self.data, &rhs.data, self.n);
    }

    fn transpose(&mut self) {
        let n = self.n;
        for i in 0..n {
            for j in (i + 1)..n {
                let t = self.data[i][j];
                self.data[i][j] = self.data[j][i];
                self.data[j][i] = t;
            }
        }
    }

    fn power(&mut self, mut x: i64) {
        let n = self.n;
        let mut base = self.data.clone();
        // reset self to identity
        for i in 0..n {
            for j in 0..n {
                self.data[i][j] = if i == j { 1 } else { 0 };
            }
        }
        while x > 0 {
            if x & 1 == 1 {
                self.data = mat_mul(&self.data, &base, n);
            }
            x >>= 1;
            if x > 0 {
                base = mat_mul(&base, &base, n);
            }
        }
    }
}

fn read_grid(sc: &mut Scanner, n: usize) -> Vec<Vec<i64>> {
    (0..n).map(|_| (0..n).map(|_| sc.next::<i64>()).collect()).collect()
}

pub fn run() {
    let mut sc = Scanner::new();
    let n: usize = sc.next();
    let t: i64 = sc.next();
    let mut res = Matrix::from_grid(read_grid(&mut sc, n));
    for _ in 0..t {
        let o: i32 = sc.next();
        match o {
            1 => { let m = Matrix::from_grid(read_grid(&mut sc, n)); res.add(&m); }
            2 => { let m = Matrix::from_grid(read_grid(&mut sc, n)); res.subtract(&m); }
            3 => { let m = Matrix::from_grid(read_grid(&mut sc, n)); res.multiply(&m); }
            4 => res.transpose(),
            5 => { let x: i64 = sc.next(); res.power(x); }
            _ => {}
        }
    }
    res.print();
}
