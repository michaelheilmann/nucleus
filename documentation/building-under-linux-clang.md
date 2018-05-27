# Building under Linux/Clang

Ensure CMake 3.10.1 and Clang 4.0 or higher are installed.
To compile, open a console, change to the directory in which the source of the library is located in, and enter
```
cmake CMakeLists.txt
make all
```
CMake respects the `CC` environment variables upon detecting the C compiler to use.
For building using Clang instead of GCC it might be required to prefix the above commands with
```
export CC=/usr/bin/clang
```
To execute the unit tests, enter
```
ctest
```
