cmake_minimum_required(VERSION 3.10)

project(JsonParser VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

# Define the library
add_library(JsonLib SHARED 
    src/json.cc
    src/parser.cc
    src/scanner.cc
    src/token.cc
    src/value.cc
)

target_include_directories(JsonLib PUBLIC include)

# Install the library
install(TARGETS JsonLib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)
install(DIRECTORY include/JsonLib
        DESTINATION include)
