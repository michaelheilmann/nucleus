# Out of source builds
The build instructions

* [Windows 10/Visual Studio Community 2017](documentation/building-under-windows-10-visual-studio-community-2017.md)
* [Windows 10/Cygwin/GCC](documentation/building-under-windows-10-cygwin-gcc.md)
* [Linux/GCC](documentation/building-under-linux-gcc.md)
* [Linux/Clang](documentation/building-under-linux-clang.md)
* [macOS/Clang](documentation/building-under-macos-clang.md)

use CMake to generate project files for in-source builds.
However, it is recommended to use CMake to generate project files for out-of-source builds.

To generate project files for an out-of-source build,
simple enter some directory (which should be empty). This directory is called the build directory.
In that directory enter the CMake command with options and generators to your liking as described
above. However, instead of writing `CMakeLists.txt` in the end, enter the path to the CMakeLists.txt
file of the product you are building - relative to your build directory.

For example, if you are in the source directory and you want the project files for Visual Studio to be generated
in `./build/visualstudio`, then simply enter `mkdir build; cd build; mkdir visualstudio`. Then tell CMake to
generate the build files in there by invokin

```
cmake -G "Visual Studio 15 2017 Win64" . ./../../CMakeLists.txt
```