cmake_minimum_required(VERSION 3.29.0)
project(UnifyTests LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(PROJECT_NAME "unit_tests")

include(GoogleTest)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 1. Add test source files
add_executable("${PROJECT_NAME}"
    tests_Angle.cpp
    tests_BBox.cpp
    tests_BRectangle.cpp
    tests_Cast.cpp
    tests_Color.cpp
    tests_ColorUnit.cpp
    tests_DataLock.cpp
    tests_LineSegment3.cpp
    tests_Matrix.cpp
    tests_Path.cpp
    tests_Quaternion.cpp
    tests_Ray.cpp
    tests_Result.cpp
    tests_String.cpp
    tests_TexCoords.cpp
    tests_V2.cpp
    tests_V3.cpp
    tests_V4.cpp
    )

target_include_directories("${PROJECT_NAME}" 
    PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

target_link_libraries(unit_tests PRIVATE GTest::gtest_main)

message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}/..")

gtest_discover_tests("${PROJECT_NAME}"
    WORKING_DIRECTORY "$<TARGET_FILE_DIR:unit_tests>"
    TEST_PREFIX "Unify."
)
