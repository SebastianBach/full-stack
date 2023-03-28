# powershell.exe -ExecutionPolicy UnRestricted -File .\\conan.ps1

conan remove text_conversion/* -c
conan export-pkg .
conan list text_conversion
conan test ./src/test_package text_conversion/0.1.1


