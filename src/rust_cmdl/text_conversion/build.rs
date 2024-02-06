
fn main() {

    match std::env::var("C_WRAPPER_LIB_LOCATION") {
        Ok(lib_location) => {
            println!("C_WRAPPER_LIB_LOCATION is: {}", lib_location);
            println!("cargo:rustc-link-search=native={}", lib_location);
        },
        Err(e) => println!("Couldn't read C_WRAPPER_LIB_LOCATION ({})", e),
    }

    println!("cargo:rustc-link-lib=static=text_conversion_c");

    println!("cargo:rustc-link-lib=stdc++");
    println!("cargo:rustc-link-lib=c");
}
