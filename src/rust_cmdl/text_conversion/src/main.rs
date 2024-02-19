use std::env;
use std::process;

mod text_conversion;

fn main() {
    // get command line args

    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        eprintln!("Error: Missing command line argument.");
        process::exit(1);
    }

    let input_string: &str = &args[1];

    println!("Input: \"{}\"", input_string);

    let result = text_conversion::title_case(input_string);

    println!("Result: \"{}\"", result);

    process::exit(0);
}