## GNU GENERAL PUBLIC LICENSE (Version 3, 29 June 2007)

# Testing Unify
This project utilizes GoogleTest (GTest) for unit testing and CTest for test orchestration. All developer-led testing should follow the standard CMake workflow outlined below.

# Developer Workflow
To validate local changes, the project must be configured with testing enabled, built, and then executed via the CTest driver.

## 1. Configuration
Enable test generation by passing the BUILD_TESTS flag to CMake.

cmake -S . -B build -G "Visual Studio 17 2022" -DBUILD_TESTS=ON

## 2. Compilation
Build the test suite target.

cmake --build build --config Debug --target unify_unit_tests

## 3. Execution
Run all registered tests via CTest. Use the --output-on-failure flag to streamline debugging.

ctest --test-dir build -C Debug --output-on-failure

A task is available to execute the above (ctrl + shift + P, then "Run Tests Quick").

# Troubleshooting
* Missing GTest: The project uses FetchContent. Ensure you have an active internet connection during the first configuration to allow CMake to download the GTest dependency.

* Partial Testing: You can run specific test cases by passing a regex to ctest: ctest -R "AABBox*"

* Clean Builds: If tests fail to find updated source logic, perform a clean build by deleting the build/ directory and re-running the workflow.