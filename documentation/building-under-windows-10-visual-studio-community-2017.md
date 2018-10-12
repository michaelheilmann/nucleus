# Building under Visual Studio 2017/Windows
Visual Studio is currently *still* supported.

Open the console.

Change the directory to the directory of this file.

Enter
```
cmake -G "Visual Studio 15 2017" CMakeLists.txt
```
to generate the project files for Win32.

Enter
```
cmake -G "Visual Studio 15 2017 Win64" CMakeLists.txt
```
to generate the project files for x64.

Open the files using Visual Studio 2017 and build all configurations.

To execute the unit tests for a particular configuration, enter
```
ctest -C <configuration>
```

```configuration``` is one of `Debug`, `Release`, `MinSizeRel`, `RelWithDebInfo`.

You can find the build products under `products/<configuration>/<platform>/(bin|lib)`
where `<configuration>` is one of `debug`, `release`, `minsizerel`, `relwithdebinfo`
and
where `<platform>` is one of `x86` or `x64`.

### Compilation options (Visual Studio)

#### `<product>-With-Static-Runtime`
For Visual Studio builds, the option `<product>-With-Static-Runtime=(ON|OFF)` is supported
where `<product>` is the product the option pertains to.
`ON` enables the statically linked C runtime,
`OFF` enables the dynamically linked C runtime.
The default value is `ON`.

For example, to enable the dynamically linked C runtime for the product `Nucleus.Interpreter`, enter
```
cmake -D"Nucleus.Interpreter-With-Static-Runtime=OFF" CMakeLists.txt
```

*This option is inherited:*
The value you specified for a parent product is transitively propagated through all child products.

*Warning:*
It is strictly not recommended to use different values when building products which are linking to each other.

#### `<product>-With-Pthreads`
For Visual Studio builds, the option `<product>-With-Pthreads=(ON|OFF)` is supported. `ON` determines
that the threading is done using the _pthreads-win32_ backend instead of the _Winapi_ backend. The
default value is `OFF`.

*This option is inherited:*
The value you specified for a parent product is transitively propagated through all child products.

*Warning:*
It is strictly not recommended to use different values when building products which are linking to each other.
