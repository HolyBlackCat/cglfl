#  OpenGL Function Loader (GLFL) v1.1.1 (generator script)
#  Copyright (C) 2017 Egor Mikhailov <blckcat@inbox.ru>
#
#  This software is provided '"'"'as-is'"'"', without any express or implied
#  warranty.  In no event will the authors be held liable for any damages
#  arising from the use of this software.
#
#  Permission is granted to anyone to use this software for any purpose,
#  including commercial applications, and to alter it and redistribute it
#  freely, subject to the following restrictions:
#
#  1. The origin of this software must not be misrepresented; you must not
#     claim that you wrote the original software. If you use this software
#     in a product, an acknowledgment in the product documentation would be
#     appreciated but is not required.
#  2. Altered source versions must be plainly marked as such, and must not be
#     misrepresented as being the original software.
#  3. This notice may not be removed or altered from any source distribution.

rm -rf out
mkdir out
mkdir out/GLFL

#    F I L E S
echo 'Preparing files'

# Replace new lines with ~
sed -e ':a' -e 'N' -e '$!ba' -e 's/\n/~/g' gl.xml >out/glxml_
# Remove comments
perl -pi -e 's|<!--.*?-->||g' out/glxml_
perl -pi -e 's|/\*.*?\*/||g' out/glxml_
perl -pi -e 's|<comment>.*?</comment>||g' out/glxml_
# Remove extra spaces and new lines
perl -pi -e 's|>[ \t]*(~?)[ ~\t]*<|>\1<|g' out/glxml_
# Restore new lines
perl -p -e 's|~|\n|g' out/glxml_ >out/glxml


#    T Y P E S
echo 'Parsing types'

# Grep types and remove useless ones
grep -P -o '<type([^s][^>]*)?>.*?</type>' out/glxml_ | grep -P 'name="inttypes"' -v - | grep -P 'khronos_' -v - | grep -P '#include' -v - >out/types
perl -pi -e 's|~|\n|g' out/types
# Remove tags
perl -pi -e 's|<[^>]*>||g' out/types
# Fix formatting
perl -pi -e 's|\( \*|\(\*|g' out/types
perl -pi -e 's|,([A-Za-z])|, \1|g' out/types


#    E N U M E R A T O R S
echo 'Parsing enumerators'

# Grep enumerators and remove duped ones (We are assuming that enumerators with `api=".."` are always dupes (usually from extensions). We remove all such enumerators except ones with `api="gl"`.)
grep -P '<enum .*value' out/glxml | perl -p -e 's|api="gl"||g' - | grep -Pv 'api="' - >out/enumerators
# Convert to defines
perl -pi -e 's/<enum .*?(name|value)="(.*?)".*?(name|value)="(.*?)".*?>/#define \2                                                                                                                      \4/g' out/enumerators
perl -pi -e 's|(-?[0-9][0-9A-Za-z_]*)( +)([A-Za-z_][0-9A-Za-z_]*)|\3\2\1|g' out/enumerators
perl -pi -e 's|(#[0-9A-Za-z_ ]{0,64})([0-9A-Za-z_]*) *(-?[0-9][0-9A-Za-z_]*)|\1\2 \3|g' out/enumerators


#    F U N C T I O N S
echo 'Parsing functions'

# Grep functions
grep -P -o '<command( [^/>]*?|)>.*?</command>' out/glxml_ >out/functions
# Remove disguised new lines
perl -pi -e 's|~||g' out/functions
# Workaround for the spec bug: Sometimes there is `<proto><ptype>BLAH</ptype>` instead of `<proto>BLAH`
perl -pi -e 's|(<proto[^>]*?>[A-Za-z0-9_ *&]*)<ptype[^>]*?>([A-Za-z0-9_ *&]*)</ptype>([A-Za-z0-9_ *&]*<name)|\1\2\3 |g' out/functions
# Workaround for the spec bug: Sometimes there is `<param>BLAH<name>BLAH</name></param>` instead of `<param><ptype>BLAH</ptype><name>BLAH</name></param>`
perl -pi -e 's|(<param[^>]*?>) *([^<]*) *<name|\1<ptype>\2</ptype><name|g' out/functions
# Find function return types and names
perl -pi -e 's|<command[^>]*?> *<proto[^>]*?>([A-Za-z0-9_ *&]*)<name[^>]*?> *([A-Za-z0-9_]*) *</name> *</proto> *|<#\1;\2#><@|g' out/functions
perl -pi -e 's|</command>|@>|g' out/functions
# Find argument types and names
perl -pi -e 's|<param[^>]*?>([A-Za-z0-9_ *&]*)<ptype[^>]*?>([A-Za-z0-9_ *&]*)</ptype>([A-Za-z0-9_ *&]*)<name[^>]*?> *([A-Za-z0-9_]*) *</name>([A-Za-z0-9_ *&[\]]*)</param>|<<\1\2\3;\4;\5>>|g' out/functions
# Remove extra spaces
perl -pi -e 's| *; *|;|g' out/functions
perl -pi -e 's|<([#@<]) *|<\1|g' out/functions
perl -pi -e 's| *([#@>])>|\1>|g' out/functions
# Remove useless tags
perl -pi -e 's|</?vecequiv[^>]*?>||g' out/functions
perl -pi -e 's|</?alias[^>]*?>||g' out/functions
perl -pi -e 's|</?glx[^>]*?>||g' out/functions
# Insert commas
perl -pi -e 's|>><<|>>,<<|g' out/functions


#    V E R S I O N S
echo 'Parsing versions'

# Grep versions
grep -Po '<feature( [^/>]*?|)>.*?</feature>' out/glxml_ | \
# Remove disguised new lines
perl -pe 's|~||g' | \
# Find names
perl -pe 's|<feature[^>]*api *= *"(.*?)([0-9]*)"[^>]*number *= *"([0-9]*?\.[0-9]*?)"[^>]*>|<#\1;\1\2;\3#><@|g' | \
perl -pe 's|</?feature[^>]*?>|@>|g' | \
# Remove useless tags
perl -pe 's|<remove[^>]*?>.*?</remove>||g' | \
perl -pe 's|</?enum[^>]*?>||g' | \
perl -pe 's|</?type[^>]*?>||g' | \
perl -pe 's|</?require[^>]*?>||g' | \
# Find function names
perl -pe 's|<command [^>]*?name *= *"([^"]*)"[^>]*?>|<<\1>>,|g' | \
perl -pe 's|,@>|@>|g' | \
# Sort
sort - >out/versions


#    E X T E N S I O N S
echo 'Parsing extensions'

# Grep extensions
grep -P -o '<extension [^>]*?([^/]>.*?</extension>|/>)' out/glxml_ >out/extensions
# Remove disguised new lines
perl -pi -e 's|~||g' out/extensions
# Find names
perl -pi -e 's|<extension[^>]*?name *= *"([^"]*)"[^>]*?supported *= *"([^"]*)"[^>]*?/>|<#\1;\2#><@@>|g' out/extensions
perl -pi -e 's|<extension[^>]*?name *= *"([^"]*)"[^>]*?supported *= *"([^"]*)"[^>]*>|<#\1;\2#><@|g' out/extensions
perl -pi -e 's|</extension>|@>|g' out/extensions
# Remove useless tags
perl -pi -e 's|</?enum[^>]*?>||g' out/extensions
perl -pi -e 's|</?type[^>]*?>||g' out/extensions
perl -pi -e 's|</?require[^>]*?>||g' out/extensions
# Find function names
perl -pi -e 's|<command [^>]*?name *= *"([^"]*)"[^>]*?>|<<\1>>,|g' out/extensions
perl -pi -e 's|,@>|@>|g' out/extensions




#    G L F L . H
echo 'Generating glfl.h'

echo >out/GLFL/glfl.h \
"___LICENSE_TEXT_HERE___

#ifndef GLFL_H_INCLUDED
#define GLFL_H_INCLUDED

#include <cstdint>

#ifdef GLFL_ENABLE_PROXY
#include <iostream>
#include <string>
#include <type_traits>
#include <cstdlib>
#endif

/* -- HOW TO USE --
 *
 * Create your window and context. Then do:
 *
 *     glfl::set_function_loader(..);
 *     glfl::load_*(..);
 *
 * After that you can call OpenGL functions.
 *
 * If you have multiple GL windows, you should first do following:
 *
 *     glfl::context my_context;
 *     glfl::set_context(my_context);
 *
 * \`glfl::set_context(..)\` determines which context is affected by \`glfl::load_*()\` and other functions.
 * When you call \`gl*()\` functions, pointers from the active context are used.
 *
 * There is a special \`0\` context which is active by default (you should use it if you have only one window).
 *
 *
 * To enable function hooking (intercepting calls), define GLFL_ENABLE_PROXY prior to inclusion of this header.
 * This macro is checked only at first inclusion.
 *
 * By default call hook will log all OpenGL calls.
 * It has some settings which are described below.
 *
 * You can provide a custom hook by defining GLFL_PROXY_NAME as a name of a proxy class.
 * The interface such class must provide is not documented. Default proxy implementation is located in glfl_proxy_proto__.h.
 *
 */

/* -- CALLING CONVENTIONS --
 *
 * All GL function pointers must be labeled as GLFL_API to enforce a proper calling convention.
 *
 *     void GLFL_API func(int x) {...}
 *
 *     void (GLFL_API *ptr)(int) = func;
 *
 * \`GLFL_API\` is defined as \`APIENTRY\` or \`__stdcall\` or \`\` (nothing) if it was not already defined by user prior to inclusion of this header.
 * Pointers from glfl::context, as well as optional fake (proxy) functions are labeled as GLFL_API.
 *
 */

#ifndef GLFL_API
#  ifdef APIENTRY
#    define GLFL_API APIENTRY
#  else
// This logic was copied from GLEW.
#    if defined(__MINGW32__) || defined(__CYGWIN__) || (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
#      define GLFL_API __stdcall
#    else
#      define GLFL_API
#    endif
#  endif
#endif
"
cat out/types >>out/GLFL/glfl.h
echo >>out/GLFL/glfl.h \
'
class glfl
{
    ~glfl() = delete;
  public:
    /* Holds loaded function pointers. */
    struct context;
    /* Returns a pointer to the current context.
     * If the default context is active, but was not used (or explicitly activated) yet, 0 will be returned. */
    static const context *active_context() {return current_context;}
    /* Makes a context active.
     * set_active_context(0) activates the default context (which is active by default). */
    static void set_active_context(context *c);
    /* A special function for getting OpenGL function addresses should be provided by your window creating library. */
    using function_loader_t = void *(*)(const char *);
    static void set_function_loader(function_loader_t ptr);
    /* Load all standard functions. */
    static void load_all_versions();
    /* Load all standard functions and all extensions. */
    static void load_everything();

    /* Load OpenGL versions. */'
grep -Po '<#[^;]*;' out/versions | uniq | perl -p -e 's|<#([^;]*);|    static void load_\1(int major, int minor);\n    static void load_\1() {load_\1(-1,-1);}|g' - >>out/GLFL/glfl.h
echo >>out/GLFL/glfl.h \
"
    /* This variable is incremented each time a GL function is called (if default proxy is enabled).
     * Before the first call it's equal to 0. Feel free to reset it if you need. */
    static unsigned long long draw_calls;
    /* Callback for logging.
     * Has no effect when proxy functions are disabled. */
    using logging_function_t = void (*)(const char *);
    static logging_function_t logging_function; // [](const char *p){std::cout << p << '\n';} by default.
    /* Makes default proxy call glGetError() after every function call.
     * Has no effect when proxy functions are disabled. */
    static bool check_errors; // 0 by default.
    /* Terminates the program after the first error (if check_errors == 1) or when used function wasn't loaded.
     * Has no effect when proxy functions are disabled. */
    static bool terminate_on_error; // 0 by default.
    /* Enables printing of \`const char *\` parameters as strings instead of pointers. May result in a crash if bad or unterminated pointers are used.
     * Has no effect when proxy functions are disabled. */
    static bool print_strings; // 0 by default.
    /* Temporarily disable logging.
     * When proxy functions are disabled, logging can't be enabled and this variable has no effect. */
    static bool disable_logging; // 0 by deafult.

    /* Get information about a function. */
    struct func_info
    {
        const char *name;    // Function name.
        const char *const *pnames; // Parameter names. If no parameters, contains a single empty string.
        const char rtag;     // Return type tag: 'E' = enum, 'B' = bool, 'F' = bitfield, '.' = other.
        const char *ptags;   // Parameter type tags (same as above).
    };
    static const func_info &get_func_info(int index);

    /* This is the index of glGetError() in the internal array of pointers.
     * It's useful for performing error checks inside of a call hook without incuding heavy \`glfl_func_indices.h\`. */
    static constexpr int index_of_glGetError = ___INDEX_OF_GLGETERROR___;
    /* This is the type of the above pointer. */
    using type_of_glGetError = ___TYPE_OF_GLGETERROR___;
"
grep -Pn 'glGetError#' out/functions | perl -pe 's|^([^:]*).*$|perl -pi -e "s/___INDEX_OF_GLGETERROR___/\1/g" out/GLFL/glfl.h|g' | source /dev/stdin
grep -P 'glGetError#' out/functions | perl -pe 's|<#([^;]*);[^#]*#><@([^@]*)@>|perl -pi -e "s/___TYPE_OF_GLGETERROR___/\1 (GLFL_API *)(\2)/g" out/GLFL/glfl.h|g' | \
perl -pe 's|>>,<<|>>, <<|g' | perl -pe 's|<<([^;]*);[^;]*;([^>]*)>>|\1\2|g' | source /dev/stdin
echo >>out/GLFL/glfl.h '    /* Load extensions. */'
perl -p -e 's|<#([^;]*);([^#]*)#><@[^@]*@>|    static void load_extension_\1(); // \2|g' out/extensions >>out/GLFL/glfl.h
echo >>out/GLFL/glfl.h \
'
    struct context
    {
        function_loader_t function_loader = 0;'
echo >>out/GLFL/glfl.h -e "        void *ptrs["`echo '.' | cat out/functions - | grep -Pc '^.' -`"] {};"
echo >>out/GLFL/glfl.h \
'
        ~context()
        {
            if (this == active_context())
                set_active_context(0);
        }
    };

  private:
    static context *current_context, *default_context;
};
'
cat out/enumerators >>out/GLFL/glfl.h
echo >>out/GLFL/glfl.h \
'
#ifdef GLFL_ENABLE_PROXY
#  include "glfl_proxy_proto__.h"
#else
#  include "glfl_simple_proto__.h"
#endif

#endif'


#    G L F L _ _ S I M P L E _ P R O T O _ _ . H
echo 'Generating glfl_simple_proto__.h'

echo >out/GLFL/glfl_simple_proto__.h \
'___LICENSE_TEXT_HERE___
'
cat -n out/functions | \
perl -pe 's|[\t ]*([0-9]*)[\t ]*<#([^;]*);([^#]*)#><@([^@]*)@>|#define \3                                                                     =(void(0), (\2 (GLFL_API *)(\4))::glfl::active_context()->ptrs[\1])|g' | \
perl -pe 's|(#[0-9A-Za-z_(), ]{0,64})([0-9A-Za-z_(),]*) *=(.*)$|\1\2 \3|g' | perl -pe 's|<<([^;]*);[^;]*;([^>]*)>>|\1\2|g' >>out/GLFL/glfl_simple_proto__.h


#    G L F L _ P R O X Y _ P R O T O _ _ . H
echo 'Generating glfl_proxy_proto__.h'

echo >out/GLFL/glfl_proxy_proto__.h \
'___LICENSE_TEXT_HERE___

#ifndef GLFL_PROXY_NAME
#  define GLFL_PROXY_NAME ::glfl_proxy::default_proxy
#endif

namespace glfl_proxy
{
    // You shouldn'"'"'t touch these unless you'"'"'re trying to implement custom proxy functions.

    extern int line, prev_line;
    extern const char *file;
    extern std::string prev_file;

    extern bool prev_check_errors;
    extern bool prev_terminate_on_error;
    extern bool prev_print_strings;
    extern bool prev_disable_logging;

    template <typename T> std::enable_if_t<std::is_arithmetic<T>::value, std::string> to_string(T obj)
    {
        return std::to_string(obj);
    }
    template <typename T> std::enable_if_t<std::is_pointer<T>::value, std::string> to_string(T obj)
    {
        if (obj == 0)
            return "0x0 (0)";
        std::string ret;
        uintptr_t n = uintptr_t(obj);
        while (n)
        {
            ret = ("0123456789abcdef"[n % 16]) + ret;
            n /= 16;
        }
        return "0x" + ret + " (" + std::to_string(uintptr_t(obj)) + ")";
    }
    inline std::string to_string(const char *obj)
    {
        if (::glfl::print_strings)
            return std::string("\"") + obj + "\"";
        else
            return to_string<void *>((void *) obj);
    }

    template <typename T> std::string bool_to_string(T obj)
    {
        return (obj ? "true" : "false");
    }
    template <typename T> std::string enum_to_string(T obj)
    {
        if (obj == 0)
            return "0x0";
        std::string ret;
        uintptr_t n = uintptr_t(obj);
        while (n)
        {
            ret = ("0123456789abcdef"[n % 16]) + ret;
            n /= 16;
        }
        ret = "0x" + ret;
        if (int(obj) < 0)
            ret += " (" + std::to_string(int(obj)) + ")";
        return ret;
    }
    template <typename T> std::string bitfield_to_string(T obj)
    {
        if (obj == 0)
            return "0x0";
        std::string ret;
        uintptr_t n = uintptr_t(obj);
        while (n)
        {
            ret = ("0123456789abcdef"[n % 16]) + ret;
            n /= 16;
        }
        return "0x" + ret;
    }

    template <typename T> std::string to_string(T obj, char tag)
    {
        switch (tag)
        {
            case '"'"'E'"'"': return enum_to_string(obj);
            case '"'"'B'"'"': return bool_to_string(obj);
            case '"'"'F'"'"': return bitfield_to_string(obj);
            default: return to_string(obj);
        }
    }

    template <int Index, typename ReturnType, typename ...ParamTypes>
    struct default_proxy
    {
        static ReturnType GLFL_API func(ParamTypes ... args)
        {
            ReturnType ret;

            default_proxy<Index, void, ParamTypes...>::call_start(args...);

            if (::glfl::active_context()->ptrs[Index] && ::glfl::active_context()->ptrs[Index] != ::glfl::active_context()->ptrs[0])
                ret = ((ReturnType (GLFL_API *)(ParamTypes...))::glfl::active_context()->ptrs[Index])(args...);
            else
            {
                if (::glfl::terminate_on_error)
                {
                    if (::glfl::disable_logging)
                    {
                        ::glfl::logging_function("");
                        ::glfl::logging_function((std::string("Function ") + ::glfl::get_func_info(Index).name + " not loaded.").c_str());
                    }
                    ::glfl::logging_function("");
                    ::glfl::logging_function("#### Stop");
                    std::exit(0);
                }
                ret = 0;
            }

            if (!::glfl::disable_logging)
                ::glfl::logging_function(("         -> " + (::glfl::active_context()->ptrs[Index] ? to_string(ret, ::glfl::get_func_info(Index).rtag) : "<?>")).c_str());

            default_proxy<Index, void, ParamTypes...>::call_end();

            return ret;
        }
    };
    template <int Index, typename ...ParamTypes>
    struct default_proxy<Index, void, ParamTypes...>
    {
        static void GLFL_API func(ParamTypes ... args)
        {
            default_proxy<Index, void, ParamTypes...>::call_start(args...);

            if (::glfl::active_context()->ptrs[Index] && ::glfl::active_context()->ptrs[Index] != ::glfl::active_context()->ptrs[0])
                ((void (GLFL_API *)(ParamTypes...))::glfl::active_context()->ptrs[Index])(args...);
            else if (::glfl::terminate_on_error)
            {
                if (::glfl::disable_logging)
                {
                    ::glfl::logging_function("");
                    ::glfl::logging_function((std::string("Function ") + ::glfl::get_func_info(Index).name + " not loaded.").c_str());
                }
                ::glfl::logging_function("");
                ::glfl::logging_function("#### Stop");
                std::exit(0);
            }

            default_proxy<Index, void, ParamTypes...>::call_end();
        }

        static void call_start(ParamTypes ... args)
        {
            bool blank_like_added = 0;
            if (prev_disable_logging != ::glfl::disable_logging)
            {
                if (::glfl::disable_logging)
                {
                    ::glfl::logging_function("");
                    ::glfl::logging_function("...");
                }
                else
                {
                    ::glfl::logging_function("");
                    ::glfl::logging_function(std::string(70, '"'"'-'"'"').c_str());
                    ::glfl::logging_function("");
                    blank_like_added = 1;
                    prev_line = 0;
                    prev_file = "";
                }
                prev_disable_logging = ::glfl::disable_logging;
            }
            if (::glfl::disable_logging)
                return;
            bool options_changed = 0;
            if (prev_check_errors != ::glfl::check_errors)
            {
                if (!blank_like_added)
                {
                    blank_like_added = 1;
                    ::glfl::logging_function("");
                }
                options_changed = 1;
                ::glfl::logging_function((std::string("#### check_errors = ") + (::glfl::check_errors ? "true" : "false")).c_str());
                prev_check_errors = ::glfl::check_errors;
            }
            if (prev_terminate_on_error != ::glfl::terminate_on_error)
            {
                if (!blank_like_added)
                {
                    blank_like_added = 1;
                    ::glfl::logging_function("");
                }
                options_changed = 1;
                ::glfl::logging_function((std::string("#### terminate_on_error = ") + (::glfl::terminate_on_error ? "true" : "false")).c_str());
                prev_terminate_on_error = ::glfl::terminate_on_error;
            }
            if (prev_print_strings != ::glfl::print_strings)
            {
                if (!blank_like_added)
                {
                    blank_like_added = 1;
                    ::glfl::logging_function("");
                }
                options_changed = 1;
                ::glfl::logging_function((std::string("#### print_strings = ") + (::glfl::print_strings ? "true" : "false")).c_str());
                prev_print_strings = ::glfl::print_strings;
            }
            if (options_changed)
                ::glfl::logging_function("");

            if (file != prev_file)
            {
                if (prev_file != "" && !options_changed)
                    ::glfl::logging_function("");
                ::glfl::logging_function(file);
                ::glfl::logging_function("");
                prev_file = file;
                prev_line = 0;
            }
            if (line != prev_line)
            {
                prev_line = line;
                ::glfl::logging_function(std::to_string(line).c_str());
            }
            else
                ::glfl::logging_function("");
            ::glfl::logging_function((std::string("    ") + (::glfl::active_context()->ptrs[Index] ? "" : "<< NOT LOADED >>  ") + ::glfl::get_func_info(Index).name + (::glfl::get_func_info(Index).pnames[0][0] ? " (...)" : " ()")).c_str());
            using dummy_array = int[];
            int index = 0;
            dummy_array{0, (::glfl::logging_function((std::string("        ") + ::glfl::get_func_info(Index).pnames[index] + " = " + to_string(args, ::glfl::get_func_info(Index).ptags[index])).c_str()), index++, 0)...};
        }

        static void call_end()
        {
            ::glfl::draw_calls++;

            if (::glfl::check_errors && Index != ::glfl::index_of_glGetError)
            {
                GLenum tmp;
                std::string str;
                while ((tmp = ::glfl::type_of_glGetError(::glfl::active_context()->ptrs[::glfl::index_of_glGetError])()))
                {
                    if (str.size())
                        str += '"'"'\n'"'"';
                    switch (tmp)
                    {
                        case GL_INVALID_ENUM:                  str += "INVALID ENUM";                  break;
                        case GL_INVALID_VALUE:                 str += "INVALID VALUE";                 break;
                        case GL_INVALID_OPERATION:             str += "INVALID OPERATION";             break;
                        case GL_INVALID_FRAMEBUFFER_OPERATION: str += "INVALID FRAMEBUFFER OPERATION"; break;
                        case GL_OUT_OF_MEMORY:                 str += "OUT OF MEMORY";                 break;
                        case GL_STACK_UNDERFLOW:               str += "STACK UNDERFLOW";               break;
                        case GL_STACK_OVERFLOW:                str += "STACK OVERFLOW";                break;
                        default:                               str += "UNKNOWN";                       break;
                    }
                }
                if (str.size())
                {
                    ::glfl::logging_function("");
                    ::glfl::logging_function("<< ERROR >>");
                    ::glfl::logging_function(str.c_str());
                    if (::glfl::terminate_on_error)
                    {
                        ::glfl::logging_function("");
                        ::glfl::logging_function("#### Stop");
                        std::exit(0);
                    }
                }
            }
        }
    };
}
'
cat -n out/functions | \
perl -pe 's|[\t ]*([0-9]*)[\t ]*<#([^;]*);gl([^#]*)#><@([^@]*)@>|#define gl\3                                                                     =(void(0), ::glfl_proxy::file = __FILE__, ::glfl_proxy::line = __LINE__, GLFL_PROXY_NAME<\1,\2,\4>::func)|g' | \
perl -pe 's|(#[0-9A-Za-z_(), ]{0,64})([0-9A-Za-z_(),]*) *=(.*)$|\1\2 \3|g' | perl -pe 's|<<([^;]*);[^;]*;([^>]*)>>|\1\2|g' | perl -pe 's|,>|>|g' >>out/GLFL/glfl_proxy_proto__.h



#    G L F L _ F U N C _ I N D I C E S . H
echo 'Generating glfl_func_indices.h'

echo >out/GLFL/glfl_func_indices.h \
'___LICENSE_TEXT_HERE___

#ifndef GLFL_FUNC_INDICES_H_INCLUDED
#define GLFL_FUNC_INDICES_H_INCLUDED

namespace glfl_func
{
    constexpr int invalid = 0;'
cat -n out/functions | perl -pe 's|[\t ]*([0-9]*)[\t ]*<#[^;]*;gl([^#]*)#><@[^@]*@>|    constexpr int \2 = \1;|g' >>out/GLFL/glfl_func_indices.h
echo >>out/GLFL/glfl_func_indices.h \
'}

#endif'


#    G L F L . C P P
echo 'Generating glfl.cpp'

echo >out/glfl.cpp \
'___LICENSE_TEXT_HERE___

#include "GLFL/glfl.h"
#include "GLFL/glfl_func_indices.h"

#include <iostream>

glfl::context *glfl::current_context = 0, *glfl::default_context = 0;

glfl::logging_function_t glfl::logging_function = [](const char *p){std::cout << p << '"'"'\n'"'"';};

unsigned long long glfl::draw_calls = 0;

bool glfl::check_errors = 0;
bool glfl::terminate_on_error = 0;
bool glfl::print_strings = 0;
bool glfl::disable_logging = 0;

namespace glfl_proxy
{
    int line = 0, prev_line = 0;
    const char *file = "";
    std::string prev_file = "";

    bool prev_check_errors = 0;
    bool prev_terminate_on_error = 0;
    bool prev_print_strings = 0;
    bool prev_disable_logging = 0;
}

void glfl::set_active_context(context *c)
{
    if (c == 0)
    {
        if (default_context == 0)
            default_context = new context;
        current_context = default_context;
    }
    else
        current_context = c;
}

void glfl::set_function_loader(function_loader_t ptr)
{
    if (current_context == 0)
        current_context = default_context = new context;
    current_context->function_loader = ptr;
    current_context->ptrs[0] = current_context->function_loader("meow");
}

void glfl::load_all_versions()
{'
grep -Po '<#[^;]*;' out/versions | uniq | perl -p -e 's|<#([^;]*);|    load_\1();|g' - >>out/glfl.cpp
echo >>out/glfl.cpp \
'}

void glfl::load_everything()
{
    load_all_versions();'
perl -p -e 's|<#([^;]*);[^#]*#><@[^@]*@>|    load_extension_\1();|g' out/extensions >>out/glfl.cpp
echo >>out/glfl.cpp \
'}

#define GLFL_LOAD_FUNCTION(name) ((glfl::context *)(glfl::active_context()))->ptrs[glfl_func::name] = glfl::active_context()->function_loader("gl" #name);
'
grep -Po '<#[^;]*;[^;]*;[^#]*#>' out/versions | \
perl -p -e 's|<#[^;]*;([^;]*);[^#]*#>|\1|g' | \
uniq | \
perl -p -e 's~^(.*)$~echo "static void load_version_\1(int major, int minor)
{
    major &= 0xffff;
    minor &= 0xffff;
    switch (0x10000 * major + minor)
    {
      default:" >>out/glfl.cpp
grep -P ";\1;" out/versions | tac >>out/glfl.cpp
echo "    }\n}" >>out/glfl.cpp
perl -pi -e "s/<#[^;]*;[^;]*;([^.]*)\.([^#]*)#><@/      [[fallthrough]];\n      case 0x10000 * \\1 + \\2:\n/g" out/glfl.cpp
perl -pi -e "s/<<gl([^>]*)>>,/        GLFL_LOAD_FUNCTION(\\1);\n/g" out/glfl.cpp
perl -pi -e "s/<<gl([^>]*)>>/        GLFL_LOAD_FUNCTION(\\1);/g" out/glfl.cpp
perl -pi -e "s/@>//g" out/glfl.cpp~g' | source /dev/stdin
echo >>out/glfl.cpp ''

grep -Po '#[^;]*;' out/versions | uniq | \
perl -pe 's~#([^;]*);~echo "void glfl::load_\1(int major, int minor)<##lf##>{<##lf##>" | xargs echo -n >>out/glfl.cpp
grep -Po "<#\1;[^;]*;" out/versions | uniq | perl -pe "s&<#([^;]*);([^;]*);&grep -Po -m1 \\"<#\\1;\\2;[^#]*#>\\" out/versions | perl -pe \\"s:<#[^;]*;[^;]*;([^.]*)\\.([^#]*)#>:<##tab##>if (0x10000 * major + minor >= 0x10000 * \\\\\\\\1 + \\\\\\\\2 \\&\\& :g\\" | xargs echo -n >>out/glfl.cpp
tac out/versions | grep -Po -m1 \\"<#\\1;\\2;[^#]*#>\\" - | perl -pe \\"s:<#[^;]*;[^;]*;([^.]*)\\.([^#]*)#>:\<##space##>0x10000 * major + minor <= 0x10000 * \\\\\\\\1 + \\\\\\\\2)<##lf##><##tab##>{<##lf##><##tab##><##tab##>load_version_\\\\2(major, minor);<##lf##><##tab##><##tab##>return;<##lf##><##tab##>}<##lf##>:g\\" | xargs echo -n >>out/glfl.cpp&g" | source /dev/stdin
tac out/versions | grep -Po -m1 \"<#\1;([^;]*);\" - | perl -pe \"s&<#[^;]*;([^;]*);&<##tab##>load_version_\\1(major, minor);<##lf##>&g\" | xargs echo -n >>out/glfl.cpp
echo "}" >>out/glfl.cpp~g' | source /dev/stdin
perl -pi -e 's|<##space##>| |g' out/glfl.cpp
perl -pi -e 's|if \([^)]*\)<##lf##><##tab##>\{[^}]*\}<##lf##><##tab##>(load_version_[^(]*\(major, minor\);)|\1|g' out/glfl.cpp
perl -pi -e 's|<##tab##>if \(0x10000 \* major \+ minor >= 0x10000 \* ([^ ]*) \+ ([^ ]*) && 0x10000 \* major \+ minor <= 0x10000 \* \1 \+ \2\)|<##tab##>if (major == \1 && minor == \2)|g' out/glfl.cpp
perl -pi -e 's|<##tab##>|    |g' out/glfl.cpp
perl -pi -e 's|<##lf##>|\n|g' out/glfl.cpp
echo >>out/glfl.cpp ''

perl -p -e 's|<#([^;]*);[^#]*#><@@>|void glfl::load_extension_\1() {}|g' out/extensions >>out/glfl.cpp
perl -pi -e 's|<#([^;]*);[^#]*#><@([^@]*)@>|void glfl::load_extension_\1()\n{\n\2}|g' out/glfl.cpp
perl -pi -e 's|>>,<<|>><<|g' out/glfl.cpp
perl -pi -e 's|<<gl([^>]*)>>|    GLFL_LOAD_FUNCTION(\1);\n|g' out/glfl.cpp

echo >>out/glfl.cpp '
const glfl::func_info &glfl::get_func_info(int index)
{
    static constexpr const char *pnames0[] {""};'
cat -n out/functions | perl -pe 's|[\t ]*([0-9]*)[\t ]*<#([^;]*);([^#]*)#><@([^@]*)@>|    static constexpr const char *pnames\1\[\] {\4};|g' | \
perl -pe 's|<<[^;]*;([^;]*);[^>]*>>|"\1"|g' | perl -pe 's|\[\] \{\};|[] {""};|g' | perl -pe 's|","|", "|g' >>out/glfl.cpp
echo >>out/glfl.cpp '    static constexpr glfl::func_info ret[]
    {
        {"<0>", pnames0, '"'"'.'"'"', ""},'
cat -n out/functions | perl -pe 's|[\t ]*([0-9]*)[\t ]*<#([^;]*);([^#]*)#><@([^@]*)@>|        {"\3", pnames\1, '"'"'<<\2;;>>'"'"', "\4"},|g' | perl -pe 's|>>,<<|>><<|g' | \
perl -pe 's|<<GLenum;[^;]*;>>|E|g' | perl -pe 's|<<GLbitfield;[^;]*;>>|F|g' | perl -pe 's|<<GLboolean;[^;]*;>>|B|g' | perl -pe 's|<<[^>]*>>|.|g' >>out/glfl.cpp
echo >>out/glfl.cpp '    };
    return ret[index];
}'


# License
cd out
find -regextype posix-extended -regex '.*\.(h|cpp)' -exec perl -pi -e 's|___LICENSE_TEXT_HERE___|/*
  OpenGL Function Loader (GLFL) v1.1.1
  Copyright (C) 2017 Egor Mikhailov <blckcat\@inbox.ru>

  This software is provided '"'"'as-is'"'"', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/|g' {} \;
cd ..


# Remove temporary files
rm -f out/*.bak
rm -f out/GLFL/*.bak
rm -f out/glxml
rm -f out/glxml_