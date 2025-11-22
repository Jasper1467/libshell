cmake_minimum_required(VERSION 3.10)
project(libshell)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to build example (default OFF)
option(BUILD_EXAMPLE "Build example application" OFF)

# Library
add_library(libshell STATIC
    src/libshell.cpp
)

set_target_properties(libshell PROPERTIES OUTPUT_NAME "shell")

# Set include directories for the library
target_include_directories(libshell PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Example executable (conditionally built)
if(BUILD_EXAMPLE)
    add_executable(libshell_example
        example/example.cpp
    )
    
    target_link_libraries(libshell_example PRIVATE libshell)
    
    # Set output name
    set_target_properties(libshell_example PROPERTIES
        OUTPUT_NAME "libshell-example"
    )
endif()

# Install rules
install(TARGETS libshell
    EXPORT libshellConfig
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)
