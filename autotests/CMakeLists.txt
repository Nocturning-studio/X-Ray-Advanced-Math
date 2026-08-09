file(GLOB_RECURSE TEST_SOURCES_CPP CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB_RECURSE TEST_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

file(GLOB_RECURSE XRMATH_HEADERS
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/include/*.inl
)

add_executable(xrMathTests
    ${TEST_SOURCES_CPP}
    ${TEST_HEADERS}
    ${XRMATH_HEADERS}
)

target_link_libraries(xrMathTests PRIVATE xrMath)

if(MSVC)
    target_compile_options(xrMathTests PRIVATE /arch:SSE4.2)
else()
    target_compile_options(xrMathTests PRIVATE -msse4.2)
endif()

target_compile_features(xrMathTests PRIVATE cxx_std_23)

set_source_files_properties(
    ${TEST_HEADERS}
    ${XRMATH_HEADERS}
    PROPERTIES HEADER_FILE_ONLY TRUE
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Tests" FILES ${TEST_SOURCES_CPP} ${TEST_HEADERS})

source_group(TREE ${CMAKE_SOURCE_DIR}/include PREFIX "xrMath" FILES ${XR_HEADERS})

enable_testing()
add_test(NAME xrMathTests COMMAND xrMathTests)
