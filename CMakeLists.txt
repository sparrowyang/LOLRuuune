PROJECT(Hello)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
if (MSVC)
    # /MT means include msvcrt as static library in the .exe
    add_compile_options(/MT)
endif()
# find_package(sqlite3 REQUIRED)

add_subdirectory(src)

