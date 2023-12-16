## Description

Welcome to the reimplementation of the library [PositionBasedDynamics](https://github.com/InteractiveComputerGraphics/PositionBasedDynamics), featuring a comprehensive set of classic Position-Based Dynamics (PBD) algorithms.

Whether you're new to PBD or looking to deepen your understanding, this library provides a step-by-step demonstration to help you grasp these powerful algorithms.

As a newcomer to Computer Graphics and C++ programming, I found this process incredibly helpful for my learning journey.

## File Structure(Only show completed files)

```bash
├── README.md
├── version.txt
├── CMakeLists.txt
├── CMake
│   ├── Common.cmake
│   ├── DataCopyTargets.cmake
│   ├── FindEigen3.cmake
│   ├── GetGitRevisionDescription.cmake
│   ├── GetGitRevisionDescription.cmake.in
├── PositionBasedDynamics
│   ├── CMakeLists.txt
├── Simulation
│   ├── CMakeLists.txt
├── Utils
│   ├── CMakeLists.txt
├── Demos
│   ├── CMakeLists.txt
├── extern
└── .gitignore
```

## Records

- Configured CMakeLists.txt ✅
- Constructed the file structure
- Started with the ClothDemo

## Bug fix

- **#Bug1**:
  After cloning the repository, I ran the following commands:

```bash
mkdir build && cd build
cmake ..
```

The CMake configuration failed with the error:

```bash
-- Could NOT find OpenMP_C (missing: OpenMP_C_FLAGS OpenMP_C_LIB_NAMES) (found version "5.0")
-- Could NOT find OpenMP_CXX (missing: OpenMP_CXX_FLAGS OpenMP_CXX_LIB_NAMES) (found version "5.0")
-- Could NOT find OpenMP (missing: OpenMP_C_FOUND OpenMP_CXX_FOUND)
```

I located the error in the file `CMake/Common.cmake`:

```cmake
FIND_PACKAGE(OpenMP)
```

To fix this, I followed these steps:

- Install libomp using Homebrew:

```bash
brew install libomp
```

- Set CMake variables in `CMake/Common.cmake`:

```cmake
set(OpenMP_C "${CMAKE_C_COMPILER}")
set(OpenMP_C_FLAGS "-Xclang -fopenmp -I/opt/homebrew/Cellar/libomp/17.0.6/include")
set(OpenMP_C_LIB_NAMES "libomp")
set(OpenMP_libomp_LIBRARY "/opt/homebrew/Cellar/libomp/17.0.6/lib/libomp.dylib")

set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
set(OpenMP_CXX_FLAGS "-Xclang -fopenmp -I/opt/homebrew/Cellar/libomp/17.0.6/include")
set(OpenMP_CXX_LIB_NAMES "libomp")
set(OpenMP_libomp_LIBRARY "/opt/homebrew/Cellar/libomp/17.0.6/lib/libomp.dylib")
```

- **Bug2**: It occures when run

```bash
make
```

Build failed with the error

```
CMake Error at /opt/homebrew/Cellar/cmake/3.26.4/share/cmake/Modules/FindPackageHandleStandardArgs.cmake:230 (message):
  Could NOT find OpenMP_C (missing: OpenMP_C_FLAGS OpenMP_C_LIB_NAMES)
Call Stack (most recent call first):
  /opt/homebrew/Cellar/cmake/3.26.4/share/cmake/Modules/FindPackageHandleStandardArgs.cmake:600 (_FPHSA_FAILURE_MESSAGE)
  /opt/homebrew/Cellar/cmake/3.26.4/share/cmake/Modules/FindOpenMP.cmake:577 (find_package_handle_standard_args)
  discregrid/CMakeLists.txt:55 (find_package)
```

It's the same reason as the #Bug1, in the file `discregrid/CMakeLists.txt` add

```cmake
set(OpenMP_C "${CMAKE_C_COMPILER}")
set(OpenMP_C_FLAGS "-Xclang -fopenmp -I/opt/homebrew/Cellar/libomp/17.0.6/include")
set(OpenMP_C_LIB_NAMES "libomp")
set(OpenMP_libomp_LIBRARY "/opt/homebrew/Cellar/libomp/17.0.6/lib/libomp.dylib")

set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
set(OpenMP_CXX_FLAGS "-Xclang -fopenmp -I/opt/homebrew/Cellar/libomp/17.0.6/include")
set(OpenMP_CXX_LIB_NAMES "libomp")
set(OpenMP_libomp_LIBRARY "/opt/homebrew/Cellar/libomp/17.0.6/lib/libomp.dylib")
find_package(OpenMP REQUIRED)
```
