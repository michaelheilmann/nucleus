# Building under macOS/Clang

Ensure CMake 3.10.1 and Clang 4.0 or higher are installed.
To compile, open a console, change to the directory in which the source of the library is located in, and enter
```
cmake CMakeLists.txt
make all
```
To execute the unit tests, enter
```
ctest
```
