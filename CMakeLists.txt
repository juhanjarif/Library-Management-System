# Set the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(library_management_system)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Set the include directories
include_directories(include)

# Add all source files from the src folder
file(GLOB SRCS
    src/book.cpp
    src/librarian.cpp
    src/main.cpp
    src/staff.cpp
    src/student.cpp
    src/user.cpp
    src/utility.cpp
    src/hashutil.cpp
)


# Add an executable target
add_executable(libraryManagementSystem ${SRCS})

# Set the output directories for binary and object files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
