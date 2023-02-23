from conans import ConanFile

# https://docs.conan.io/en/latest/creating_packages/existing_binaries.html

class TextConversionConan(ConanFile):
    name = "text_conversion"
    version = "0.1.0"
    description = "Text Conversion and Formatting Library"
    settings = "os", "compiler", "build_type", "arch"

    def package(self):
        self.copy("*lib", src="build/product/lib/", dst="lib", keep_path=False)
        self.copy("*h", src="build/product/lib/", dst="include", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = self.collect_libs()
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.libdirs = ["lib"]

