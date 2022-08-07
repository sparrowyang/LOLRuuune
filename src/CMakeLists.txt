
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
# openssl 

set(OPENSSL_ROOT_DIR "D:\\Program Files (x86)\\OpenSSL-Win32")
set(OPENSSL_INCLUDE_DIR "D:\\Program Files (x86)\\OpenSSL-Win32\\include")
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
link_directories("D:\\Program Files (x86)\\OpenSSL-Win32\\lib")
link_libraries(libssl libcrypto)
if(OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIRS})
  message(STATUS "OpenSSL Found!")
endif()

add_subdirectory(lcu)
add_subdirectory(logger)
add_subdirectory(gui)
add_executable(he main.cpp)

target_link_libraries(he PRIVATE Qt5::Widgets)
target_link_libraries(he PRIVATE mainwnd)
# set_target_properties(he PROPERTIES
#     WIN32_EXECUTABLE ON
#     MACOSX_BUNDLE ON
# )