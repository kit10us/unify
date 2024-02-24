**GNU GENERAL PUBLIC LICENSE** (Version 3, 29 June 2007)
# Unify
Unify is a library of 2D, 3D, and general data structures and functionality to support the creation of clearer, cleaner code, in a standard way.

[Source Code Documentation](https://htmlpreview.github.io/?https://github.com/kit10us/unify/blob/master/docs/html/annotated.html)

It attempts to accomplish this in several ways:
- Create common named data structure types specific to purpose and need. Such as *angles, vectors, data streams, etc*.
- Provide a place for common type functionality, reducing duplicate and possibly vague implementations.
- Support named functionality to provide clearer implementation intention. For example, instead of *float positionX, positionY* you have *V2 position*.
- Have a single place to support holistic functional improvements and fixes.
- Allow independence from 3rd party libraries which helps promote portable solutions.
- Reduce code complexity and verbosity by supporting function overloading. For example, instead of *MoveCarDirectionV2(float x, float y)* you have *MoveCar(V2 direction)*.

# The History
Initially, the Unify library was for educational purposes. It provided a place where you could learn implementation details of game data structure functionality, without just relying on 3rd party libraries. Additionally, it was a place for public example, as many examples of these implementations are isolated pieces of code, disconnected from the greater picture and related example functionality.

It continued to mature into a library of features that could be shared across multiple projects. 

# The Future
The library continues to gain support for multiple platforms. Presently, the library is only used with Windows projects (especially the Mercury Engine) that depend on Direct-X renderers (both Direct-X 9 and Direct-X 11). There is a partial OpenGL renderer, however, the development of the engine's features and optimizations has trumped the need for OpenGL, the only real viable method for supporting cross platform graphics rendering at the time. Now, Vulan is available and probably will supersede OpenGL and will likely gain priority over the current renderers.

There is also an ongoing effort to support additional rendering features, shared across all of the three most common graphics APIs, that have been introduced into Mercury, and required major changes to the engine's render modules.

# The Rub
All of this is to say that extreme optimization has not been a priority. It might become one in the future, however, at that point it could be necessary to reduce implementation clarity, in other words, it would become a poor example for learning.

# Code Formatting
The formatting of the code within Unify is the culmination of research in code readability. This was also an objective with Unify. It was not only a place to practice and learn functional implementation, it was also a place to practice and learn code formatting and naming conventions. To those ends, it might look a little *funky* to many developers. It's not following the general standard many in the C++ community use, or would prefer - trust me *I've heard this already*. This is also a feature that might change in the future.

# Source Code Requirements
The following section covers requirements when developing within Unify. These are not standards, as much as compatibility requirements.

## C++ Version Compatibility
**Consideration**
Ensure features beyond C++11 are guarded with __cplusplus defines, to ensure backwards compatibility with C++11.

_note: This can become tedious, especially with the growing number of C++ versions supported (14, 17, etc.). If, and then, how granular this is taken is under consideration. Consider this a **good to do** not a **must do** at the moment._

See https://www.stroustrup.com/C++11FAQ.html#11

## In-line Document Generation Comments
Code comments in Unify are in the xml doc format, see: https://learn.microsoft.com/en-us/cpp/build/reference/xml-documentation-visual-cpp?view=msvc-170

Inline code comments should only be within headers (whatever the extension is), and not within the c/cpp files.

The following should be commented before pushing code into the repo:
- class and struct types with summaries
- enum types with summaries
- All functions, except for constructors, operators, functions only within c/cpp files

Additional, non-duplicate, comments should be added at the developers discretion where clarity requires.

_Note: xml docs, such as vs doxygen, comment formatting is the current method for in-code commenting due to legacy Visual Studio support. Changing format is a consideration, however, doxygen supports this format, so this is not a priority._
