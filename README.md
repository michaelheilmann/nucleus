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

#### Continuous Integrations Status Maxtrix

|              | master                                                                                                                                                                          | develop                                                                                                                                                                           |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Travis**   | [![Build Status](https://travis-ci.org/primordialmachine/nucleus.svg?branch=master)](https://travis-ci.org/primordialmachine/nucleus)                                           | [![Build Status](https://travis-ci.org/primordialmachine/nucleus.svg?branch=develop)](https://travis-ci.org/primordialmachine/nucleus)                                            |
| **AppVeyor** | [![Build status](https://ci.appveyor.com/api/projects/status/c6ualudcnt8h9pco/branch/master?svg=true)](https://ci.appveyor.com/project/primordialmachine/nucleus/branch/master) | [![Build status](https://ci.appveyor.com/api/projects/status/c6ualudcnt8h9pco/branch/develop?svg=true)](https://ci.appveyor.com/project/primordialmachine/nucleus/branch/develop) |
