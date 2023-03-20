import os
from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.build import can_run

# https://docs.conan.io/2.0/reference/tools/cmake/cmakedeps.html
# https://docs.conan.io/2/tutorial/creating_packages/test_conan_packages.html#tutorial-creating-test

class FuncLibTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators =  "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def layout(self):
        cmake_layout(self)

    def test(self):
        if can_run(self):
            cmd = os.path.join(self.cpp.build.bindir, "test")
            self.run(cmd, env="conanrun")
