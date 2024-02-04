use std::env;

fn main() {

    let dir = env::current_dir().unwrap();
    let lib_path = dir.join("../../../build/product/rust");

    println!("{}", lib_path.display());

    println!("cargo:rustc-link-search=native={}", lib_path.display());

    println!("cargo:rustc-link-lib=static=rustwrapper");

    println!("cargo:rustc-link-lib=stdc++");
    println!("cargo:rustc-link-lib=c");
}

