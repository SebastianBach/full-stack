from conans import ConanFile

# https://docs.conan.io/en/latest/creating_packages/existing_binaries.html

class FuncLibConan(ConanFile):
    name = "func_lib"
    version = "0.1.0"
    description = "Some Functionality"
    settings = "os", "compiler", "build_type", "arch"

    def package(self):
        self.copy("*", src="build/product/lib/", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = self.collect_libs()

