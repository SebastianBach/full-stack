// https://doc.rust-lang.org/nomicon/ffi.html

extern crate libc;
use libc::{c_char, size_t};
use std::ffi::CString;
use std::process;
use std::env;

extern "C" {
  fn text_conversion_c(buf: *mut c_char, size: size_t);
}

fn perform_text_conversion(input: &str) -> String {

  let c_string = CString::new(input).unwrap();

  let mut buffer: Vec<u8> = c_string.into_bytes_with_nul();

  unsafe {
    text_conversion_c(buffer.as_mut_ptr() as *mut c_char, buffer.len());
  }

  // check for null terminator
  if buffer[buffer.len() - 1] != 0 {
    buffer.push(0);
  }

  // convert back to string
  let string = String::from_utf8_lossy(&buffer).to_string();
  return string;
}

fn main() {
  
  // get command line args

  let args: Vec<String> = env::args().collect();

  if args.len() < 2 {
    eprintln!("Error: Missing command line argument.");
    process::exit(1);
  }

  let input_string: &str = &args[1];

  println!("Input: \"{}\"", input_string);

  let result = perform_text_conversion(input_string);

  println!("Result: \"{}\"", result);

  process::exit(0);
}
