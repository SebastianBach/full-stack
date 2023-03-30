
# https://docs.conan.io/2/tutorial/creating_packages/other_types_of_packages/package_prebuilt_binaries.html

import os
from conan import ConanFile
from conan.tools.files import copy

class MyLibConan(ConanFile):
    name = "text_conversion"
    version = "0.1.1"
    settings = "os", "arch"
    exports_sources = "build/product/lib/*"

    def layout(self):
        _os = str(self.settings.os).lower()
        _arch = str(self.settings.arch).lower()
        self.folders.build = os.path.join("build", "product", "lib")
        self.folders.source = self.folders.build
        self.cpp.source.includedirs = ["header"]
        self.cpp.build.libdirs = ["lib"]

    def package(self):
        local_include_folder = os.path.join(self.source_folder, self.cpp.source.includedirs[0])
        local_lib_folder = os.path.join(self.build_folder, self.cpp.build.libdirs[0])
        copy(self, "*.h", local_include_folder, os.path.join(self.package_folder, "include"), keep_path=False)
        copy(self, "*.lib", local_lib_folder, os.path.join(self.package_folder, "lib"), keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["text_conversion"]

