# Nucleus
nucleus is basic C project with CMake support.
Nucleus works for Windows and Linux.

## Building the demo (Windows)
Visual Studio is currently *still* supported.

Open the console.

Change the directory to the directory of this file.

Enter
```
cmake CMakeLists.txt -a Win32
```
to generate the project files for Win32.

Enter
```
cmake CMakeLists.txt -a x64
```
to generate the project files for x64.

Open the files using Visual Studio 2017 and build all configurations.

To execute the unit tests for a particular configuration, enter
```
ctest -C <configuration>
```

```configuration``` is one of `Debug`, `Release`, `MinSizeRel`, `RelWithDebInfo`.

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
to build.

To execute the unit tests, enter
```
ctest
```

#### Continuous Integrations Status Maxtrix

|              | master                                                                                                                                                                          | develop                                                                                                                                                                           |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Travis**   | [![Build Status](https://travis-ci.org/primordialmachine/nucleus.svg?branch=master)](https://travis-ci.org/primordialmachine/nucleus)                                           | [![Build Status](https://travis-ci.org/primordialmachine/nucleus.svg?branch=develop)](https://travis-ci.org/primordialmachine/nucleus)                                            |
| **AppVeyor** | [![Build status](https://ci.appveyor.com/api/projects/status/c6ualudcnt8h9pco/branch/master?svg=true)](https://ci.appveyor.com/project/primordialmachine/nucleus/branch/master) | [![Build status](https://ci.appveyor.com/api/projects/status/c6ualudcnt8h9pco/branch/develop?svg=true)](https://ci.appveyor.com/project/primordialmachine/nucleus/branch/develop) |
