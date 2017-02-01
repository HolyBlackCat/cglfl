# What is GLFL

GLFL is an OpenGL function loader, much like GLEW.

When working with more or less modern OpenGL (at least 3.0+) on some platforms (at least on Windows), you have to use a 3rd party library to get pointers to all needed functions from the API. Libraries like GLEW and GLFL serve exactly this purpose.

It fully supports OpenGL up to 4.5, OpenGL ES up to 3.2 and OpenGL SC up to 2.0, as well as all official extensions.

# GLFL vs GLEW

GLFL supports loading different pointers for different contexts.

GLFL seems to compile faster (on my MinGW-w64(GCC 6.2.0) it's faster by 33%, which is 0.1s, with `-Wall -Wextra -O3`).

GLFL supports logging of all OpenGL calls, including their arguments and return values. Optionally it can do `glGetError()` after every call.

GLFL does NOT support GLX or WGL for now.

GLFL can't check if a specific extension or version is available. (also for now)

# How GLFL is generated

GLFL is generated using a simple shell script from OpenGL XML Registry: https://raw.githubusercontent.com/KhronosGroup/OpenGL-Registry/master/xml/gl.xml