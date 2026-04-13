**GNU GENERAL PUBLIC LICENSE** (Version 3, 29 June 2007)
# Unify
Unify is a library of general purpose data structures and functionality to support the creation of cleaner, standized code. While it supports many general features, it is strongly developed for use with 2D and 3D graphical applications.

The original interation of the library dates back to around C++98, and you will find some legacy mechanism and paradigms with it that are exist in their form to support features that have been integrated into existing projects. The project had a first major overhaul with the integration of C++11. Before this, it leaned heavily on Boost, such as for smart pointers, and other features (some are still included in one form or another to support legacy projects).

While the library had been held together for over two decades, with step ups based on C++ version iterations and other techincal improvements, it is target for another major refactor to C++17. This update intends to remove many legacy features that have been superceeded by C++ language advances, that are best supported with other, more dedicated projects (such as https://www.etlcpp.com/), and those features that are niche or just don't fit the overall theme and responsibility of the Unify library.

Attempts will be made throughout the transition to document alternatives to important features, and those other projects external to Unify have depended upon (such as the DataLock, Stream, and Containers/Buffers features).

[Source Code Documentation](https://kit10us.github.io/unify)

It attempts to accomplish this in several ways:
- Create common named data structure types specific to purpose and need. Such as *angles, vectors, data streams, etc*.
- Provide a place for common type functionality, reducing duplicate and possibly vague implementations.
- Support named functionality to provide clearer implementation intention. For example, instead of *float positionX, positionY* you have *V2 position*.
- Have a single place to support holistic functional improvements and fixes.
- Allow independence from 3rd party libraries which helps promote portable solutions.
- Reduce code complexity and verbosity by supporting function overloading. For example, instead of *MoveCarDirectionV2(float x, float y)* you have *MoveCar(V2 direction)*.

# Optimizations
Numerous classes are not implicitly initialized, such as the Color class. For some of these, these are optimization is a consideration, however, for others, it is for troubleshooting. Determining the default value is not typically straight forward for these types, and implicitly initializing them to a _reasonable_ value would likely hide bugs. For example, with a Color, initializing to components all 0s is trivial, and it could be argued that there is little to no performance related issues for doing so, however, if all components were 0, this could include the alpha channel. This could result in geometry not visably render at all. I could imagine that the color not having been set would be very low on the minds of the poor sole having to troubleshoot missing geometry. Worst case, and quite reasonably, the troubleshooting blame would fall on the naturally complex rendering pipeline, all for missing a one line, possibly one number, change. In this particular case, random garbage values would likely standout as the geometry would look akin to psychopharmacudical trip. This would apply to other types as well, such as vectors and rectables.

## Pass parameter by-value Versus by-pointer (by-Reference)
When determining when parameters should be passed by value, or by reference, we should consider what is best for optimal performance. 

- By-value avoids a pointers and references require derefrencing, which might cause a cache miss.
- Modern x64 processors utilize 128-bit SIMD registers (such as XMM0 through XMM15). A 16-byte object (such as a 4-float quaternion) fits exactly into a single register. By passing these by value, the compiler can often keep the data entirely within the CPU's register file, avoideing the need to ever write the data to the stack or read it from memory.

# The History
Initially, the Unify library was for educational purposes. It provided a place where you could learn implementation details of game data structure functionality, without just relying on 3rd party libraries. Additionally, it was a place for public example, as many examples of these implementations are isolated pieces of code, disconnected from the greater picture and related example functionality.

It continued to mature into a library of features that could be shared across multiple projects.    

# Source Code Requirements
The following section covers requirements when developing within Unify. These are not standards, as much as compatibility requirements.

## Header Function Definitions
To keep headers clean, and easier to reference for in-source documentation, function implementations should be housed in a separate header file with an _.inl_ extension. While a _.hpp_ file extension is often used for this purpose, files with that extension are commonfor various projects, and so we would like to prevent further confusion. The _.inl_ extension was used in legacy *(read: very old)* code, and is what the original Unify had used - for better or for worse.

## In-line Document Generation Comments
Code comments in Unify are in the XML doc format, see: https://learn.microsoft.com/en-us/cpp/build/reference/xml-documentation-visual-cpp?view=msvc-170

XML commenting is supported both with Visual Studio, as well as Doxygen, however, Doxygen style commenting is not well supported with Visual Studio, making XML commenting more portable. The XML comments are also more robust and allows for richer features like <remarks>, <seealso>, and <exception>.

Inline code comments should only be within headers (whatever the extension is), and not within the c/cpp files. This is for a number of reasons:
- Libraries are seldom distributed with their headers.
- IDE supported (e.g. hover, intellisence).
- To ensure no comment duplication.

The following should be commented before pushing code into the repo:
- class and struct types with (min req: summary).
- enum types with (min req: summary).
- All functions, except for constructors, operators, and simple accessors/mutators (getters/setters).

Additional, non-duplicate, comments should be added at the developers discretion where clarity requires.

## To/From String Conversions
A DSL (Domain Specific Language) is used when casting to and from strings. All other options considered, this is the greatest option for speed and readability.

# Coding Caveats
For every good practice in C++, there are exponentially that many bad practices. Be they by habbit, out-dated understandings, or inacurate knowledge propegation. This section will attempt to cover some the more common mal-practices.

## Return string_view
### *string_view* as a return
A string_view is loosely a safe char pointer, as such that it doesn't have ownership of the memory for the string. This means that a temporary heap-allocated string does not move the life-time management responsibility to the string_view. When returning a temporary string, whose heap allocation has function scope lifetime, as a string_view, the contents of the string_view will become invalidated. This generally means that you should *only* return a string_view when it points to a string in the .rodata segment.

### *string_view* as a member
Per the above section on string_view as a return type, and the lifetime/ownership of the memory, this goes for member variables as well. The string_view does not own the memory, it is basically just a pointer.

# Multi-platform Support
Unify current can target both Windows and Linux. To support this, we make use of the CMake project generators.

To generate a project for Windows:
cmake -S . -B build -G "Visual Studio 17 2022"
