use std::path::Path;

fn setup() -> Result<(), &'static str> {
    
    match std::env::var("C_WRAPPER_LIB_LOCATION") {
        Ok(lib_location) => {

            println!("C_WRAPPER_LIB_LOCATION is: {}", lib_location);
            let path = Path::new(&lib_location);

            if path.exists() && path.is_dir() {
                println!("cargo:rustc-link-search=native={}", lib_location);
            } else {
                return Err("C_WRAPPER_LIB_LOCATION is not an existing directory.");
            }
        },
        Err(_) => {
            return Err("Couldn't read C_WRAPPER_LIB_LOCATION.");
        },
    }

    println!("cargo:rustc-link-lib=static=text_conversion_c");
    println!("cargo:rustc-link-lib=stdc++");
    println!("cargo:rustc-link-lib=c");

    Ok(())
}

fn main() {

    if let Err(e) = setup()
    {
        panic!("Build setup failed: {}", e);
    } 
}
