# Nucleus

Nucleus is a C cross-platform utility library for Windows, Linux, and OS X.
Nucleus is made available publicly under the
[MIT license](https://github.com/primordialmachine/nucleus/blob/master/LICENSE.md)
on
[Github](https://github.com/primordialmachine/nucleus).

## Building the demo (Windows)
Visual Studio is currently *still* supported.

Open the console.

Change the directory to the directory of this file.

Enter
```
cmake -a Win32 CMakeLists.txt
```
to generate the project files for Win32.

Enter
```
cmake -a x64 CMakeLists.txt
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

### Compilation options (Linux and Cygwin)
For Linux and Cygwin builds, certain CMake options are supported.
The currently supported options are `With-Debug-Information=(ON|OFF)`
and `With-Optimizations=(ON|OFF)`.

For example, to enable both optimizations and debug information enter
```
cmake -DWith-Optimizations=ON -DWith-Debug-Information=ON CMakeLists.txt
```

## Documentation
The documentation of Nucleus is in the process of being converted to Markdown for being directly available on Github.

### Nucleus Annotations Module
The Nucleus Annotations module provides annotations for functions, parameters, and expressions.

#### Reference

The following annotations are currently available.

- [Nucleus_NonNull](documentation/Nucleus_NonNull.md)
- [Nucleus_NoReturn](documentation/Nucleus_NoReturn.md)
- [Nucleus_Likely](documentation/Nucleus_Likely.md)
- [Nucleus_Unlikely](documentation/Nucleus_Unlikely.md)

### Nucleus Memory Module
The Nucleus Memory Module provides functionality to allocate and deallocate memory blocks, as well as valuation and manipulation of memory blocks and their contents.

For the purpose of this documentation, any consecutive - possibly empty - sequence of Bytes starting at some address is called a memory block.
As usual with C, a pointer p to the first Byte of a memory block increment by 1 will point to the second Byte, a pointer p to the second Byte increment by 1 will point to the third Byte an so on.
The number of Byte variables of a memory block is the size of a memory region. The Nucleus memory module provides functionality to allocate and deallocate memory blocks, as well as valutation and manipulation of memory blocks and their contents.

The tasks of allocation and deallocation of memory blocks, valuation and manipulation of memory blocks and their contents are in C frequently performed over memory blocks
of which their sizes are specified in terms of array semantics: The memory block is considered as an array and it size is specified as its number of elements and the size,
in Bytes, of an element. Consequently, each function taking a specification of a size of a memory block as a single value, is accompanied by function taking the specification
of the size of the memory block as two values. In this API, you You can easily find the related functions:
- The functions taking the size, in Bytes, do not include the word `Array` in their function names,
- the functions taking the number of elements and the element size, in Bytes, include the word `Array` somewhere in their function names.

The Array-functions do not only exist for convenience, but also for safety: These function fail if the multiplication of the number of elements and the element size would overflow.

#### Reference

- [Nucleus_allocateMemory](documentation/Nucleus_allocateMemory.md)
- [Nucleus_allocateArrayMemory](documentation/Nucleus_allocateArrayMemory.md)
- [Nucleus_reallocateMemory](documentation/Nucleus_reallocateMemory.md)
- [Nucleus_reallocateArrayMemory](documentation/Nucleus_reallocateArrayMemory.md)
- [Nucleus_deallocateMemory](documentation/Nucleus_deallocateMemory.md)
- [Nucleus_copyMemory](documentation/Nucleus_copyMemory.md)
- [Nucleus_copyArrayMemory](documentation/Nucleus_copyArrayMemory.md)
- [Nucleus_compareMemory](documentation/Nucleus_compareMemory.md)
- [Nucleus_compareArrayMemory](documentation/Nucleus_compareArrayMemory.md)
- [Nucleus_hashMemory](documentation/Nucleus_hashMemory.md)
- [Nucleus_hashArrayMemory](documentation/Nucleus_hashArrayMemory.md)
- [Nucleus_getPageSize](documentation/Nucleus_getPageSize.md)

### Nucleus Floating Point Module
The Nucleus Floating Point Module provides functionality to evaluate and generate single, double, and quadruple precision floating point values.

#### Reference

- [Nucleus_Single,
   Nucleus_Double,
   Nucleus_Quadruple](documentation/[Floating-Point-Type].md)
- [Nucleus_Single_hash,
   Nucleus_Double_hash,
   Nucleus_Quadruple_hash](documentation/[Floating-Point-Type]_hash.md)
- [Nucleus_Single_isNaN,
   Nucleus_Double_isNaN,
   Nucleus_Quadruple_isNaN](documentation/[Floating-Point-Type]_isNaN.md)
- [Nucleus_Single_isSubnormal,
   Nucleus_Double_isSubnormal,
   Nucleus_Quadruple_isSubnormal](documentation/[Floating-Point-Type]_isSubnormal.md)

### Nucleus Hash Module
The Nucleus Hash provides functionality to compute hash values from boolean values, numeric values, pointer values,
and Byte array values as well hash value combinators.

#### Reference

- [Nucleus_hash[NumericType]](documentation/Nucleus_hash[NumericType].md)
- [Nucleus_hashPointer](documentation/Nucleus_hashPointer_hash.md)
- [Nucleus_hashBoolean](documentation/Nucleus_hashBoolean.md)
- [Nucleus_hashHashValue](documentation/Nucleus_hashHashValue.md)
- [Nucleus_hashMemory](documentation/Nucleus_hashMemory.md)
- [Nucleus_hashArrayMemory](documentation/Nucleus_hashArrayMemory.md)
- [Nucleus_combineHashValues](documentation/Nucleus_combineHashValues.md)

### Nucleus File System Module
The Nucleus Dynamic Byte Array Module provides functionality related to the filesystem.

#### Reference

- [Nucleus_setFileContents](documentation/Nucleus_setFileContents.md)

### Nucleus Collections Module __DRAFT__
The Nucleus Collections Module provides collections e.g. arrays, deques.
Any collection provided supports
Its documentation can be found [here](documentation/Nucleus_Collections_ByteArray.md).

#### Reference

- [Nucleus_Collections_ByteArray_getSize,
   Nucleus_Collections_PointerArray_getSize,
   Nucleus_Collections_PointerDeque_getSize](documentation/Nucleus_Collections_[Collection-Type]_getSize.md).

- [Nucleus_Collections_ByteArray_getCapacity,
   Nucleus_Collections_PointerArray_getCapacity,
   Nucleus_Collections_PointerDeque_getCapacity](documentation/Nucleus_Collections_[Array-Collection-Type]_getCapacity.md).

- [Nucleus_Collections_ByteArray_getFreeCapacity,
   Nucleus_Collections_PointerArray_getFreeCapacity,
   Nucleus_Collections_PointerDeque_getFreeCapacity](documentation/Nucleus_Collections_[Array-Collection-Type]_getFreeCapacity.md).

- [Nucleus_Collections_ByteArray_ensureFreeCapacity,
   Nucleus_Collections_PointerArray_ensureFreeCapacity,
   Nucleus_Collections_PointerDeque_ensureFreeCapacity](documentation/Nucleus_Collections_[Array-Collection-Type]_ensureFreeCapacity.md)

- [Nucleus_Collections_ByteArray_clear,
   Nucleus_Collections_PointerArray_clear,
   Nucleus_Collections_PointerDeque_clear](documentation/Nucleus_Collections_[Collection-Type]_clear.md).

- [Nucleus_Collections_ByteArray_insert,
   Nucleus_Collections_PointerArray_insert,
   Nucleus_Collections_PointerDeque_insert](documentation/Nucleus_Collections_[Array-Collection-Type]_insert.md).

- [Nucleus_Collections_ByteArray_append,
   Nucleus_Collections_PointerArray_append,
   Nucleus_Collections_PointerDeque_append](documentation/Nucleus_Collections_[Array-Collection-Type]_append.md).

- [Nucleus_Collections_ByteArray_prepend,
   Nucleus_Collections_PointerArray_prepend,
   Nucleus_Collections_PointerDeque_prepend](documentation/Nucleus_Collections_[Array-Collection-Type]_prepend.md).

## Continuous Integrations Status Maxtrix

|              | master                                                                                                                                                                          | develop |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------- |
| **Travis**   | [![Build Status](https://travis-ci.org/primordialmachine/nucleus.svg?branch=master)](https://travis-ci.org/primordialmachine/nucleus)                                           |    -    |
| **AppVeyor** | [![Build status](https://ci.appveyor.com/api/projects/status/c6ualudcnt8h9pco/branch/master?svg=true)](https://ci.appveyor.com/project/primordialmachine/nucleus/branch/master) |    -    |
