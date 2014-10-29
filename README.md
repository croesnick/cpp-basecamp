About this repository
=====================
This repo aims to provide a full build system for C++-libraries/-projects.
The exact definition of "full" is subject to change, but it at least includes
a test system, automatically generating an API documentation, and running
different checks (like valgrind) to ensure a certain code quality.

Notes on the build system
=========================
The preferred way to use CMake is to do an out-of-source build:
On the top level create a new directory (e.g., build), `cd` into it, then type
`cmake ..` and `make` to build the project. Run the tests with `ctest` or
`ctest -V`. A `make doc` then generates the documentation.

Todos / possible extensions
===========================
* code coverage analysis
* cmake: differentiate between release and debug builds
* add vim-scripts to auto-generate Doxygen comment stubs
* add valgrind to the build process
* add code formatting rules (cpp-lint?)
