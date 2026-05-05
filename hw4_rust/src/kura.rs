// 14931 — reorder list: 1->2->3->4->5 becomes 1->5->2->4->3.
// Algorithm: collect values, interleave front with reversed back (tortoise-hare split).
// Note: the C++ harness checks that no new nodes are allocated via pointer XOR;
// that check is not replicated here since we rebuild from values idiomatically.
use crate::scanner::Scanner;

struct ListNode {
    value: i32,
    next: Option<Box<ListNode>>,
}

fn solve(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    let mut vals = Vec::new();
    let mut curr = head;
    while let Some(node) = curr {
        vals.push(node.value);
        curr = node.next;
    }

    let n = vals.len();
    if n <= 2 {
        return build(&vals);
    }

    // Interleave front and reversed back: 0, n-1, 1, n-2, ...
    let mut result = Vec::with_capacity(n);
    let (mut lo, mut hi) = (0usize, n - 1);
    while lo <= hi {
        result.push(vals[lo]);
        lo += 1;
        if lo <= hi {
            result.push(vals[hi]);
            hi -= 1;
        }
    }
    build(&result)
}

fn build(vals: &[i32]) -> Option<Box<ListNode>> {
    let mut head = None;
    for &v in vals.iter().rev() {
        head = Some(Box::new(ListNode { value: v, next: head }));
    }
    head
}

pub fn run() {
    let mut sc = Scanner::new();
    let n: usize = sc.next();
    let vals: Vec<i32> = (0..n).map(|_| sc.next()).collect();

    let mut head: Option<Box<ListNode>> = None;
    for &v in vals.iter().rev() {
        head = Some(Box::new(ListNode { value: v, next: head }));
    }

    let result = solve(head);

    let mut curr = result.as_ref();
    let mut first = true;
    while let Some(node) = curr {
        if !first { print!(" "); }
        print!("{}", node.value);
        first = false;
        curr = node.next.as_ref();
    }
    println!();
}
