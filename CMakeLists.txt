cmake_minimum_required(VERSION 3.10)

project(ivy LANGUAGES C VERSION 0.1)

add_subdirectory("src")
add_subdirectory("include")

if (NOT MSVC)
  target_compile_options(ivy PRIVATE -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -Wconversion)
endif()

target_include_directories(ivy PUBLIC ${PROJECT_BINARY_DIR})
