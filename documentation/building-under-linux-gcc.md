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
The currently supported options are `<product>-With-Debug-Information=(ON|OFF)`
and `<product>-With-Optimizations=(ON|OFF)`. The former enables/disables debug
information, the latter enables/disables optimizations. `<product>` is     the
target name of the product the options pertain to.

For example, to enable both optimizations and debug information for the product `Nucleus.Interpreter`, enter
```
cmake -DNucleus.Interpreter-With-Optimizations=ON -DNucleus.Interpreter-With-Debug-Information=ON CMakeLists.txt
```
