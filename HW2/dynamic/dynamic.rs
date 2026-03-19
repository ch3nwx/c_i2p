use std::io::{self, Read};

struct Array3D {
    data: Vec<Vec<Vec<u32>>>,
}

impl Array3D {
    fn new(n: usize, m: usize, k: usize) -> Self {
        Array3D {
            data: vec![vec![vec![0u32; k]; m]; n],
        }
    }

    fn get(&self, i: usize, j: usize, l: usize) -> u32 {
        self.data[i][j][l]
    }

    fn set(&mut self, i: usize, j: usize, l: usize, val: u32) {
        self.data[i][j][l] = val;
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_ascii_whitespace();

    macro_rules! next {
        ($t:ty) => { iter.next().unwrap().parse::<$t>().unwrap() }
    }

    let t = next!(usize);
    let n = next!(usize);
    let m = next!(usize);
    let k = next!(usize);
    let mut seed = next!(u32);

    let mut random = || -> u32 {
        seed = seed.wrapping_mul(0xdefaced).wrapping_add(1);
        seed
    };

    let mut out = String::new();

    for _ in 0..t {
        let mut arr = Array3D::new(n, m, k);

        for i in 0..n {
            for j in 0..m {
                for l in 0..k {
                    arr.set(i, j, l, random());
                }
            }
        }

        for i in 0..5usize {
            let a = (random() as usize) % n;
            let b = (random() as usize) % m;
            let c = (random() as usize) % k;
            if i > 0 { out.push(' '); }
            out.push_str(&arr.get(a, b, c).to_string());
        }
        out.push('\n');
    }

    print!("{}", out);
}
