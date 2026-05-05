mod scanner;
mod stack;
mod matrix;
mod vending;
mod kura;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        eprintln!("usage: {} <stack|matrix|vending|kura>", args[0]);
        std::process::exit(1);
    }
    match args[1].as_str() {
        "stack"   => stack::run(),
        "matrix"  => matrix::run(),
        "vending" => vending::run(),
        "kura"    => kura::run(),
        other => {
            eprintln!("unknown problem: {}", other);
            std::process::exit(1);
        }
    }
}
