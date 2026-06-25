set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# Native build — prevent CMake from treating this as cross-compilation
set(CMAKE_CROSSCOMPILING FALSE)

# Apple Silicon
set(CMAKE_OSX_ARCHITECTURES arm64)
set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0")

set(CMAKE_C_FLAGS_INIT   "-arch arm64")
set(CMAKE_CXX_FLAGS_INIT "-arch arm64")
