// https://doc.rust-lang.org/nomicon/ffi.html

extern crate libc;
use libc::{c_char, size_t};
use std::ffi::CString;

extern "C" {
    fn text_conversion_c(buf: *mut c_char, size: size_t);
}

pub fn title_case(input: &str) -> String {
    let c_string = CString::new(input).unwrap();
    let mut buffer: Vec<u8> = c_string.into_bytes_with_nul();

    unsafe {
        text_conversion_c(buffer.as_mut_ptr() as *mut c_char, buffer.len());
    }

    // remove null terminator
    if buffer[buffer.len() - 1] == 0 {
        buffer.pop();
    }

    let string = String::from_utf8_lossy(&buffer).to_string();
    return string;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_title_case() {
      
        let input = "this is a headline!";
        let expected = "This Is a Headline!"; 

        let result = title_case(input);

        println!("Expected `{}`, got `{}` for input `{}`", expected, result, input);

        assert_eq!(result, expected);
    }
}
