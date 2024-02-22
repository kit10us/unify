**GNU GENERAL PUBLIC LICENSE** (Version 3, 29 June 2007)
# Unify
Unify is a library of 2D, 3D, and general data structures and functionality to support the creation of clearer, cleaner code, in a standard way.

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
