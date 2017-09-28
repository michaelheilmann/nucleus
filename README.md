# Nucleus
nucleus is basic C project with CMake support.
Nucleus works for Windows and Linux.

## Building the demo (Windows)
Visual Studio is currently *still* supported.

Open the console.

Change the directory to the directory of this file.

Enter
```
cmake CMakeLists.txt 
```
to generate the project files.

Open the files using Visual Studio 2017.

## Building the demo (Linux and Cygwin)
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
to build the demo.

#### Travis CI Build Status
Build status of [master](https://github.com/primordialmachine/nucleus/tree/master) branch:
[![Build Status](https://travis-ci.org/primordialmachine/nucleus.svg?branch=master)](https://travis-ci.org/primordialmachine/nucleus)

Build status of [develop](https://github.com/primordialmachine/nucleus/tree/develop) branch:
[![Build Status](https://travis-ci.org/primordialmachine/nucleus.svg?branch=develop)](https://travis-ci.org/primordialmachine/nucleus)

#### Appveyor CI Build Status
Build status of [master](https://github.com/primordialmachine/nucleus/tree/master) branch:
[![Build status](https://ci.appveyor.com/api/projects/status/tdcxnqmma5q6etfl/branch/master?svg=true)](https://ci.appveyor.com/project/michaelheilmann/nucleus/branch/master)

Build status of [develop](https://github.com/primordialmachine/nucleus/tree/develop) branch:
[![Build status](https://ci.appveyor.com/api/projects/status/tdcxnqmma5q6etfl/branch/develop?svg=true)](https://ci.appveyor.com/project/michaelheilmann/nucleus/branch/develop)
