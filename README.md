# Signals : A simple, easy to use signal / slot library


An easy to use, header only, one file signal slot library.

## License

This project is providen under the terms of the MIT license,
you should have received a copy of this license

Pleas see te Copyright.txt file for more information about this.

<a id="1"></a>
## Requirements 

The absolute minimum requirement is to use a C++14 (C++17 is best) compliant
compiler if you consider to simply copy the `Signal.hpp` in your own
project's include directory

In addition, if you may have to use CMake (version >= 3.8 ) and Doxygen 
(version >= 1.8.13) for specific uses.

<a id="2"></a>
## Used and tested tools

This project is developped on a basic -- but up to date -- debian *testing* (codename **buster**) distribution 

<a id="2.1"></a>
### Tested compilers
On this day, the project has correctly been build and passed unit tests with: 

	Gcc 7.3.0 (debian)
	Gcc 8.1.0 (debian)
	clang 6.0 (debian)
	
<a id="2.2"></a>
### No mandatory tools

Those tools have been tested in the mean time:

	CMake 3.11.1 (debian)
	doxygen 1.8.13 (debian)

> **Note :** If you are able to compiling and passing unit tests on diferent
> architectures, with different compilers or with different tools versions,
> feel free add let me know it.  I'll be glad to add the information here.

<a id="3"></a>
## How to Use? 

- Just put the `Signal.hpp` in a directory known by the compiler to
hold header files and ensure that it is part of your project.
- If you considere to generate documentation or to use the unit tests policy,
 please refer to the [Using Cmake section](#5)

<a id="4"></a>
## Directory structure 
If we consider that `<root_dir>` correspond here to my toolbox/Signal subdirecty,
here his the structure of this directory

```

        <root_dir>                         // main library root directory
            |-> 3rdParty                   // contains some 3rd party external libraries 
            |                              // (mainely CATCH, which is used for unit test policy)
            |-> doxygen                    // contains doxygen documentation generator related files
            |    |-> examples              // contains some (compilable) *.cpp files used exclusively
            |                              // by doxygen to generate examples
            |-> lib                        // contains the library source code
            |    |-> Tools                 // as possiblely part of a more general use (Tools) library
            |    |   |                     // all Signal source files will live in its general use library directory
            |    |   |->include            // contains all header files (only Signal.hpp for this project)
            |-> tests                      // Contains files required for the unit test policy
            |    |->Tools                  // As part as a more general use (Tools)library, 
            |    |    |                    // all Signal source files will live in its general use library directory
            |    |    |-> Signal           // all Signal unit tests related files are in them own subtree
            |    |        |-> include      // contains specifics headers required for testing Signal library
            |    |        |-> src          // contains specifics implementationf files for testing Signal library
```

All "first level" (`<root_dir>`, `3rdParty`, `doxygen`, `lib` and `tests`)
and all `Signal` subdirectory contains CMake related files making the `<root_dir>`
usable as the perfect base to create a new project

Different toolbox parts (like `Locator` subdirectory) will follow exactely the same
directory structure (but for `tests/Tools/<dirname>`) and eatch CMake related file
will has similar effects to allow you to use so many tools part as y need 
to start a new project.
<a id="5"></a>
# Building and installing
The easiest way to build this project is to

	1 using CMake to configure it see the [Using Cmake section](#5) for more informations
	2 using the `make` command fort building (if requested : only needed if unit tests are selected) the project 
	3 using the `make doc` command for generating documentation (if requested)
	4 (if wanted) going in the tests build dir and launching unit tests with the `ctest` command
	5 (if wanted) going back in the <root_builddir> and creating packages with the `cpack` command
	6 (if wanted) installing library files using the ` make install` command
	7 (if wanted) installing the documentation using the `make install doc` command

<a id="6"></a>
## Using CMake 

CMake is a great, effiscient tool helping to manage project configuration work.
