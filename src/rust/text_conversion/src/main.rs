extern crate libc;
use libc::{c_char, size_t};
use std::ffi::CString;

extern "C" {
  fn text_conversion_c(buf: *mut c_char, size: size_t);
}

fn main() {
  
  let initial_str = "Hello World";

  let c_string = CString::new(initial_str).unwrap();

  let mut buffer: Vec<u8> = c_string.into_bytes_with_nul();

  unsafe {
  
    text_conversion_c(buffer.as_mut_ptr() as *mut c_char, buffer.len());

    // check for null terminator
    if buffer[buffer.len() - 1] != 0 {
      buffer.push(0);
    }

    // convert back to string
    let string = String::from_utf8_lossy(&buffer);

    println!("Result: {}", string);
  }
}
