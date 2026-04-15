cmake -S . -B build -G "Visual Studio 17 2022" -DUNIFY_BUILD_TESTS=ON

cmake --build build --config Debug --target unify_unit_tests
