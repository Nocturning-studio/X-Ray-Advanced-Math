cmake_minimum_required(VERSION 3.14)
project(xrMath VERSION 1.0.0 LANGUAGES CXX)

add_library(xrMath INTERFACE)
target_include_directories(xrMath INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(xrMath INTERFACE cxx_std_17)

if(MSVC)
    target_compile_options(xrMath INTERFACE /W3)
else()
    target_compile_options(xrMath INTERFACE -Wall -Wextra)
endif()

include(GNUInstallDirs)
install(TARGETS xrMath EXPORT xrMathTargets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

enable_testing()
add_subdirectory(autotests)
