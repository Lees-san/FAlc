cmake_minimum_required(VERSION 3.20)

project(FATest VERSION 0.1)

# create interface library to give both FATest and FractalAlchemy the compiler features
add_library(FA_compiler_flags INTERFACE)
target_compile_features(FA_compiler_flags INTERFACE cxx_std_20)

# set stuff
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the library subdirectory
add_subdirectory(FractalAlchemy)

# add the executable and the source of it
add_executable(FATest test.cxx)

# link libraries
target_link_libraries(FATest PUBLIC FractalAlchemy FA_compiler_flags)
target_include_directories(FATest PUBLIC ${PROJECT_SOURCE_DIR})