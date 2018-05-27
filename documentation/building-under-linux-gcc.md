# Building under Linux/GCC
Open the console.

Change the directory to the directory of this file.

Enter
```
cmake CMakeLists.txt
```
to generate the project files.

Enter
```
make all
```
to build.

To execute the unit tests, enter
```
ctest
```

You can find the build products under `products/<platform>/(bin|lib)`
where `<platform>` is one of `x86` or `x64`.

## Compilation options
For Linux builds, certain CMake options are supported.
The currently supported options are `With-Debug-Information=(ON|OFF)`
and `With-Optimizations=(ON|OFF)`.

For example, to enable both optimizations and debug information enter
```
cmake -DWith-Optimizations=ON -DWith-Debug-Information=ON CMakeLists.txt
```
