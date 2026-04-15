## GNU GENERAL PUBLIC LICENSE (Version 3, 29 June 2007)

# Unify Template Library (UTL)
Unify Template Library is a general-purpose C++ library designed to facilitate cleaner, standardized code across complex systems. While it provides a broad range of utilities, it is architected with a specific focus on 2D and 3D graphical applications and real-time systems.

# Evolution and Vision
Originating in the C++98 era, Unify has evolved through two decades of industry changes. After a major shift to C++11 to integrate smart pointers and modern memory management, the library is currently undergoing a strategic refactor to C++17/20.

The goal of this update is to:

Deprecate legacy mechanisms superseded by modern language standards.

Offload non-core responsibilities to specialized projects (e.g., ETL for embedded containers).

Streamline the API to focus on high-performance math and system primitives.

[Source Code Documentation](https://kit10us.github.io/unify/html/annotated.html)

# Core Philosophy
Unify achieves its goals through several architectural pillars:

Purpose-Driven Types: Provides semantic types (Angles, Vectors, Streams) to replace vague primitives.

Semantic Clarity: Promotes intent-based naming (e.g., using V2 instead of two independent floats).

Dependency Isolation: Minimizes reliance on third-party libraries to ensure maximum portability.

Complexity Reduction: Extensive use of function overloading to reduce API verbosity.

# Features
Multi-platform: First-class support for Windows (MSVC) and Linux (GCC/Clang).

Unit Testing: Fully integrated GoogleTest (GTest) suite via CTest.

# Setup and Development
## Generate Project Files
To generate build files for Windows (Visual Studio 2022):
cmake -S . -B build -G "Visual Studio 17 2022"

## Enable Unit Testing
To include the test suite in your build:
cmake -S . -B build -G "Visual Studio 17 2022" -DUNIFY_BUILD_TESTS=ON

# Standards and Practices
## Separation of Concerns
Unify maintains strict isolation between domains. For example, CMake logic is compartmentalized into a dedicated /cmake folder, keeping the root CMakeLists.txt clean and high-level.

## Directory and Naming Conventions
Naming formats are domain-specific. While this may result in a "clash" between different sections (e.g., build system vs. source code), it ensures that a specialist in one area (like CMake) finds a familiar, standard environment for that specific domain.

# Optimization Philosophy
## Explicit Initialization
Many Unify types (e.g., Color, V3) are not implicitly initialized. This is a deliberate architectural choice:

1. Performance: Avoids redundant writes in tight loops where the data will be immediately overwritten.

2. Debugging: Prevents silent bugs. For instance, initializing a Color to 0 (Transparent Black) could hide a rendering bug behind an invisible object. Random "garbage" values make initialization failures immediately obvious during visual testing.

## Memory and Register Optimization
Unify prioritizes CPU register efficiency:

* Pass-by-Value: Small types (<= 16 bytes, such as V3 or Quaternion) are passed by value. This allows compilers to utilize 128-bit SIMD registers (XMM), keeping data within the CPU's register file and avoiding stack-frame overhead or potential cache misses from pointer dereferencing.

# Source Code Requirements
## Implementation Isolation (.inl)
To maintain clean, readable headers, complex template and function implementations are housed in separate files with a .inl extension. This preserves the header as a clear API reference.

## Documentation Standards
Unify uses the XML Documentation format for high portability between Visual Studio and Doxygen.

* Placement: All documentation resides in header files only to ensure IntelliSense support and prevent duplication.

* Requirements: All Classes, Structs, Enums, and non-trivial functions must include a <summary>.

# Coding Caveats
return string_view
* Ownership: A string_view is a non-owning reference. Never return a string_view that points to a local function-scope string; doing so results in a dangling pointer.

* Usage: Only return a string_view when the underlying data is guaranteed to outlive the view (e.g., constants in the .rodata segment or persistent member variables).

## string_view as a Member
Exercise extreme caution when using string_view as a class member. The class does not own the string memory; ensure the source data remains valid for the entire lifetime of the class instance.

# Final Notes
Unify is considered pre-release at the moment due to needing some modernization and optimizations. That being said, certain names of features will change **NOW** and be committed to for future revisions; this means we need to be pretty explicit in naming so we stick to **SOLID** development prinipals.
