cmake_minimum_required(VERSION 3.29.0)
project(UnifyTests LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
add_executable(unify_unit_tests
    tests_Result.cpp
    tests_Angle.cpp
    tests_V2.cpp
    tests_V3.cpp
    tests_V4.cpp
    tests_LineSegment3.cpp
    tests_Ray.cpp
    tests_BBox.cpp
    tests_BRectangle.cpp
    tests_Matrix.cpp
    tests_Cast.cpp
    )

target_include_directories(unify_unit_tests 
    PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

target_link_libraries(unify_unit_tests PRIVATE GTest::gtest_main)

message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}/..")

#set(CMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)

# 2. Add test cases
#add_test(NAME Unify.Angle COMMAND unify_unit_tests --gtest_filter=AngleTests.*)
#add_test(NAME Unify.V2 COMMAND unify_unit_tests --gtest_filter=V2Tests.*)
#add_test(NAME Unify.V3 COMMAND unify_unit_tests --gtest_filter=V3Tests.*)
#add_test(NAME Unify.V4 COMMAND unify_unit_tests --gtest_filter=V4Tests.*)
#add_test(NAME Unify.LineSegment3 COMMAND unify_unit_tests --gtest_filter=LineSegment3Tests.*)
#add_test(NAME Unify.Ray COMMAND unify_unit_tests --gtest_filter=RayTests.*)
#add_test(NAME Unify.BBox COMMAND unify_unit_tests --gtest_filter=BBoxTests.*)
#add_test(NAME Unify.Matrix COMMAND unify_unit_tests --gtest_filter=MatrixTests.*)


gtest_discover_tests(unify_unit_tests 
    WORKING_DIRECTORY "$<TARGET_FILE_DIR:unify_unit_tests>"
    TEST_PREFIX "Unify."
)

# 3. Set test properties (optional)
#set_tests_properties(Unify.Angle PROPERTIES LABELS "Angle")
#set_tests_properties(Unify.V2 PROPERTIES LABELS "V2")
#set_tests_properties(Unify.V3 PROPERTIES LABELS "V3")
#set_tests_properties(Unify.V4 PROPERTIES LABELS "V4")
#set_tests_properties(Unify.LineSegment3 PROPERTIES LABELS "LineSegment3")
#set_tests_properties(Unify.Ray PROPERTIES LABELS "Ray")
#set_tests_properties(Unify.BBox PROPERTIES LABELS "BBox")
#set_tests_properties(Unify.Matrix PROPERTIES LABELS "Matrix")