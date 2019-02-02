#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>


namespace data
{
    const std::string calling_convention_macro = "GLFL_API";

    const std::vector<std::pair<std::string, std::string>> type_replacements
    {
        {"signed char"   , "std::int8_t"  }, // Sic!
        {"unsigned char" , "std::uint8_t" },
        {"short"         , "std::int16_t" },
        {"unsigned short", "std::uint16_t"},
        {"int"           , "std::int32_t" },
        {"unsigned int"  , "std::uint32_t"},
    };

    const std::string header = 1+R"(
// This file is a part of GLFL - OpenGL function (and extension) loader.

// Copyright (c) 2018-2019 Egor Mikhailov
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

)";
    const std::string pragma_once = "#pragma once\n\n";
}

template <typename ...P> std::string Str(const P &... params)
{
    std::ostringstream stream;
    (stream << ... << params);
    return stream.str();
}

[[noreturn]] void Error(std::string message)
{
    std::cout << "Error: " << message << '\n';
    std::exit(1);
}

std::string GetContext(const char *ptr)
{
    std::string ret;
    int n = 30;
    while (*ptr && n-- > 0)
        ret += *ptr++;
    return ret;
}


std::string LoadFile(std::string file_name)
{
    std::string source;

    FILE *file = std::fopen(file_name.c_str(), "rb");

    if (!file)
        Error(Str("Unable to open `", file_name, "`."));

    std::fseek(file, 0, SEEK_END);
    auto size = std::ftell(file);
    std::fseek(file, 0, SEEK_SET);

    if (std::ferror(file) || size == EOF)
        Error(Str("Unable to get size of file `", file_name, "`."));

    source.resize(size);
    if (!std::fread(source.data(), size, 1, file))
        Error(Str("Unable to read from file `", file_name, "`."));

    return source;
}


struct Token
{
    enum Type
    {
        text, tag_begin, tag_end, tag_terse,
    };

    Type type;
    std::string value;
    std::map<std::string, std::string> attributes;
};

std::vector<Token> LexSource(const std::string &source)
{
    std::vector<Token> tokens;

    const std::string
        header_begin  = "<?",
        header_end    = "?>",
        comment_begin = "<!--",
        comment_end   = "-->";

    struct EscapePair
    {
        std::string from;
        char to;
    };
    const std::vector<EscapePair> escape_pairs
    {
        { "lt;"  , '<' },
        { "gt;"  , '>' },
        { "amp;" , '&' },
        { "apos;", '\''},
        { "quot;", '"' },
    };

    const char *ptr = source.c_str();

    while (*ptr)
    {
        // Skip whitespace
        while (*ptr > '\0' && *ptr <= ' ')
            ptr++;

        // Skip header
        if (!std::strncmp(ptr, header_begin.c_str(), header_begin.size()))
        {
            ptr += header_begin.size();

            while (std::strncmp(ptr, header_end.c_str(), header_end.size()))
            {
                if (!*ptr)
                    Error(Str("Expected `", header_end, "` at the end of input."));
                ptr++;
            }

            ptr += header_end.size();
            continue;
        }

        // Skip comment
        if (!std::strncmp(ptr, comment_begin.c_str(), comment_begin.size()))
        {
            ptr += comment_begin.size();

            while (std::strncmp(ptr, comment_end.c_str(), comment_end.size()))
            {
                if (!*ptr)
                    Error(Str("Expected `", comment_end, "` at the end of input."));
                ptr++;
            }

            ptr += comment_end.size();
            continue;
        }

        // Parse tag
        if (*ptr == '<')
        {
            ptr++;

            // Skip whitespace after `<`.
            while (*ptr > '\0' && *ptr <= ' ')
                ptr++;

            bool closing_tag = 0;

            if (*ptr == '/')
            {
                closing_tag = 1;
                ptr++;

                // Skip whitespace after `/`.
                while (*ptr > '\0' && *ptr <= ' ')
                    ptr++;
            }

            Token new_token;

            // Read tag name.
            while ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z') || *ptr == '_')
                new_token.value += *ptr++;

            // Stop if no name.
            if (new_token.value.empty())
                Error(Str("Missing tag name. Context:\n", GetContext(ptr)));

            // Skip whitespace after tag name.
            while (*ptr > '\0' && *ptr <= ' ')
                ptr++;

            // Get tag type, parse attributes if needed.
            if (closing_tag)
            {
                new_token.type = Token::tag_end;
            }
            else
            {
                // Parse attributes
                while (*ptr != '>' && *ptr != '/')
                {
                    std::string name;

                    // Read attribute name.
                    while ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z') || *ptr == '_')
                        name += *ptr++;

                    // Stop if no name.
                    if (name.empty())
                        Error(Str("Missing attribute name. Context:\n", GetContext(ptr)));

                    // Skip whitespace after attribute name.
                    while (*ptr > '\0' && *ptr <= ' ')
                        ptr++;

                    // Stop if no `=` sign.
                    if (*ptr != '=')
                        Error(Str("Missing `=` after attribute name. Context:\n", GetContext(ptr)));
                    ptr++;

                    // Skip whitespace after `=`.
                    while (*ptr > '\0' && *ptr <= ' ')
                        ptr++;

                    // Stop if no opening `"`.
                    if (*ptr != '"')
                        Error(Str("Missing opening `\"` in attribute. Context:\n", GetContext(ptr)));
                    ptr++;

                    std::string value;

                    // Read attribute value.
                    while (*ptr && *ptr != '"')
                        value += *ptr++;

                    // Stop if no terminating `"`.
                    if (!*ptr)
                        Error(Str("Expected closing `\"` at the end of input."));
                    else
                        ptr++;

                    // Skip whitespace after attribute value.
                    while (*ptr > '\0' && *ptr <= ' ')
                        ptr++;

                    // Add attribute to the map.
                    new_token.attributes.insert({name, value});
                }

                // Check if it's a terse tag.
                if (*ptr != '/')
                {
                    new_token.type = Token::tag_begin;
                }
                else
                {
                    ptr++;
                    new_token.type = Token::tag_terse;

                    // Skip whitespace after `/`.
                    while (*ptr > '\0' && *ptr <= ' ')
                        ptr++;
                }
            }

            // Stop if no '>'.
            if (*ptr != '>')
                Error(Str("Missing `>` in a tag. Context:\n", GetContext(ptr)));
            ptr++;

            tokens.push_back(new_token);
            continue;
        }

        { // Read plain text
            std::string new_text;
            while (*ptr && *ptr != '<')
            {
                if (*ptr > '\0' && *ptr <= ' ')
                {
                    if (new_text.size() > 0 && new_text.back() != ' ' && new_text.back() != '\n')
                        new_text.push_back(*ptr == '\n' || *ptr == '\r' ? '\n' : ' ');
                    else if (new_text.size() > 0 && new_text.back() == ' ' && *ptr == '\n')
                        new_text.back() = '\n';
                    ptr++;
                }
                else
                {
                    if (*ptr == '&')
                    {
                        ptr++;

                        bool found = 0;
                        for (const auto &pair : escape_pairs)
                        {
                            if (!std::strncmp(ptr, pair.from.c_str(), pair.from.size()))
                            {
                                found = 1;
                                new_text += pair.to;
                                ptr += pair.from.size();
                                break;
                            }
                        }

                        if (!found)
                            Error(Str("Unknown escape sequence. Context:\n", GetContext(ptr-1)));
                    }
                    else
                    {
                        new_text += *ptr++;
                    }
                }
            }

            if (new_text.empty())
                continue;

            if (new_text.back() == ' ' || new_text.back() == '\n')
                new_text.resize(new_text.size()-1);

            Token new_token;
            new_token.type = Token::text;
            new_token.value = std::move(new_text);
            tokens.push_back(new_token);
        }
    }

    return tokens;
}


struct Element
{
    bool is_tag = 1;
    std::string value; // Text or tag name.
    std::string location; // Essentially a list of parents.

    // Tag only:
    std::map<std::string, std::string> attributes;
    std::vector<Element> elements;

    void PrettyPrint(std::ostream &stream, int indent = 0) const
    {
        std::string ind(indent * 4, ' ');
        stream << ind;
        for (char ch : value)
        {
            stream << ch;
            if (ch == '\n')
                stream << ind;
        }
        if (is_tag)
        {
            for (const auto &attr : attributes)
                stream << " [" << attr.first << '=' << attr.second << ']';
            if (value.size() > 0)
                stream << ' ';
            stream << '{';
            if (elements.size() > 0)
            {
                stream << '\n';
                for (const auto &child : elements)
                    child.PrettyPrint(stream, indent+1);
                stream << ind;
            }
            stream << '}';
        }
        stream << '\n';
    }

    std::string FullName() const
    {
        return location + (is_tag ? value : "<text>");
    }

    bool IsTagNamed(std::string name) const
    {
        return is_tag && value == name;
    }

    const Element &GetChild(std::string name) const
    {
        const Element *ret = 0;
        if (is_tag)
        {
            for (const auto &child : elements)
            {
                if (child.IsTagNamed(name))
                {
                    if (ret)
                        Error(Str("Several elements named `", name, "` in `", FullName(), "`, but expected only one."));
                    ret = &child;
                }
            }
        }
        if (!ret)
            Error(Str("No element named `", name, "` in `", FullName(), "`."));
        return *ret;
    }

    void ForEachChildNamed(std::string name, std::function<void(const Element &)> func) const // Generates a error if it's a text node.
    {
        if (!is_tag)
            Error(Str("Expected `", FullName(), "` to be a tag rather than a text."));

        for (const auto &elem : elements)
            if (elem.IsTagNamed(name))
                func(elem);
    }

    std::string GetTextNodeText() const // If it's a text node, returns the contents. Otherwise generates a error.
    {
        if (is_tag)
            Error(Str("Expected `", FullName(), "` to be a text node."));
        return value;
    }

    std::string GetContainedText() const // If it's a text node, returns the contents. If it's a tag, it has to have a single text node in it, which contents will be returned. Otherwise generates a error.
    {
        if (!is_tag)
            return value;
        if (elements.size() != 1 || elements.front().is_tag)
            Error(Str("Expected `", FullName(), "` to be a text node or a tag with a single text node in it."));
        return elements.front().value;
    }

    bool HasAttribute(std::string name) const // If it's a text node, returns 0.
    {
        auto it = attributes.find(name);
        return it != attributes.end();
    }

    std::string GetAttribute(std::string name) const // If no such attribute, generates a error.
    {
        if (auto it = attributes.find(name); it != attributes.end())
            return it->second;
        else
            Error(Str("Expected an attribute named `", name, "` in `", FullName(), "`."));
    }

    bool HasAttributeEqualTo(std::string name, std::string value) const // If the node has no such attribute (possibly because it's a text node), returns 0.
    {
        if (auto it = attributes.find(name); it != attributes.end())
            return it->second == value;
        else
            return 0;
    }
};

Element ParseTokens(const std::vector<Token> &tokens)
{
    Element root_element;

    std::vector<Element *> stack = {&root_element}; // There is no danger of ending the root tag, since empty tag names are catched earlier.
    std::vector<int> index_stack = {0};

    for (const auto &token : tokens)
    {
        switch (token.type)
        {
          case Token::tag_begin:
          case Token::tag_terse:
            {
                auto &parent = *stack.back();
                parent.elements.push_back({});

                auto &obj = parent.elements.back();
                obj.is_tag = 1;
                obj.value = token.value;
                obj.attributes = token.attributes;
                for (std::size_t i = 0; i < stack.size(); i++)
                {
                    if (stack[i]->value.empty())
                        continue;
                    obj.location += Str(stack[i]->value, "(", index_stack[i], ")/");
                }

                if (token.type != Token::tag_terse)
                {
                    stack.push_back(&obj);
                    index_stack.push_back(parent.elements.size()-1);
                }
            }
            break;
          case Token::tag_end:
            {
                if (token.value != stack.back()->value)
                    Error(Str("Closing tag `</", token.value, ">` has no matching opening tag."));
                stack.pop_back();
                index_stack.pop_back();
            }
            break;
          case Token::text:
            {
                auto &parent = *stack.back();
                parent.elements.push_back({});

                auto &obj = parent.elements.back();
                obj.is_tag = 0;
                obj.value = token.value;
                for (std::size_t i = 0; i < stack.size(); i++)
                {
                    if (stack[i]->value.empty())
                        continue;
                    obj.location += Str(stack[i]->value, "(", index_stack[i], ")/");
                }
            }
            break;
          default:
            Error("Invalid token type. (Internal error.)");
            break;
        }
    }

    if (stack.size() > 1) // Note the 1. The stack shouldn't be empty, because it always has the root element in it.
        Error(Str("Missing closing tag </", stack.back()->value, "> for ", stack.back()->FullName(), "."));

    return root_element;
}


std::string ExtractTypes(const Element &root_element)
{
    std::string ret;

    // Get the types.
    const auto &loc = root_element.GetChild("registry").GetChild("types");
    for (const auto &elem : loc.elements)
    {
        if (!elem.IsTagNamed("type"))
            Error(Str("Expected `", loc.FullName(), "` to consist only of `type` tags."));

        // Discard silly includes.
        if (elem.HasAttributeEqualTo("name", "stddef") || elem.HasAttributeEqualTo("name", "khrplatform"))
            continue;

        // Discard ugly preprocessor tricks determining a correct underlying type for 64-bit integers.
        if (elem.HasAttributeEqualTo("name", "inttypes"))
            continue;

        // Discard silly typedefs depending on khrplatform.h.
        if (elem.HasAttributeEqualTo("requires", "khrplatform"))
            continue;

        // Add the type.
        for (const auto &elem : elem.elements)
        {
            if (elem.IsTagNamed("apientry"))
            {
                ret += data::calling_convention_macro;
                continue;
            }

            std::string text = elem.GetContainedText();

            if (ret.size() > 0 && ret.back() != '*' && ret.back() != '\n' && text.front() != ';' && text.front() != ')') // We don't need to check text emptiness, it always has a positive size.
                ret += ' ';

            ret += text;
        }
        ret += '\n';
    }

    { // Tweak the types.
        { // Add spaces after commas for better looks.
            std::string new_ret;
            for (std::size_t i = 0; i < ret.size(); i++)
            {
                if (ret[i] == ',' && ret[i+1] != ' ')
                    new_ret += ", ";
                else
                    new_ret += ret[i];
            }
            ret = std::move(new_ret);
        }

        { // Replace builtin types with standard fixed-size aliases.
            std::string new_ret;
            const char *ptr = ret.c_str();

            while (*ptr)
            {
                bool found = 0;
                bool dont_replace = ptr == ret.c_str() || (ptr[-1] >= 'A' && ptr[-1] <= 'Z') || (ptr[-1] >= 'a' && ptr[-1] <= 'z') || (ptr[-1] >= '0' && ptr[-1] <= '9') || ptr[-1] == '_';
                if (!dont_replace)
                {
                    for (const auto &pair : data::type_replacements)
                    {
                        if (!std::strncmp(ptr, pair.first.c_str(), pair.first.size()))
                        {
                            found = 1;
                            ptr += pair.first.size();
                            new_ret += pair.second;
                            break;
                        }
                    }
                }
                if (!found)
                    new_ret += *ptr++;
            }

            ret = std::move(new_ret);
        }
    }

    return ret;
}


struct EnumConstant
{
    std::string name;
    std::string value;
    std::string suffix; // Number literal suffix, optional.
    uint64_t value_number; // Some of the constants are 64-bit, for special purposes.
    bool negative;
};

struct EnumGroup
{
    std::string name; // Can be empty.
    std::vector<EnumConstant> elements;
};

struct EnumData
{
    std::vector<EnumGroup> groups;
    std::map<std::string, std::set<std::string>> categories;
    int max_name_len;

    int enum_count;

    void PrettyPrint(std::ostream &stream) const
    {
        std::string ret;

        { // Max name length.
            stream << "max_name_len = " << max_name_len << '\n';
        }

        { // Categories.
            stream << "categories {\n";
            for (const auto &category : categories)
            {
                stream << "    " << category.first << " {\n";
                for (const auto &elem : category.second)
                    stream << "        " << elem << '\n';
                stream << "    }\n";
            }
            stream << "}\n";
        }

        { // Groups.
            stream << "groups {\n";
            for (const auto &group : groups)
            {
                stream << "    " << (group.name.empty() ? "<nameless group>" : group.name) << " {\n";
                for (const auto &elem : group.elements)
                {
                    std::string name = elem.name, type = elem.suffix;
                    name.resize(max_name_len, ' ');
                    type.resize(6, ' ');
                    stream << "        [ type = " << type << ", neg = " << elem.negative << ", name = " << name << ", value = " << elem.value << ", parsed_value = " << elem.value_number << " ]\n";
                }
                stream << "    }\n";
            }

            stream << "}\n";
        }
    }
};

EnumData ExtractEnums(const Element &root_element)
{
    EnumData enum_data;
    enum_data.max_name_len = 0;

    // Extract categories.
    root_element.GetChild("registry").GetChild("groups").ForEachChildNamed("group", [&](const Element &elem)
    {
        std::string name = elem.GetAttribute("name");

        std::set<std::string> contents;
        elem.ForEachChildNamed("enum", [&](const Element &elem)
        {
            contents.insert(elem.GetAttribute("name"));
        });

        if (contents.empty())
            return;

        enum_data.categories.insert({std::move(name), std::move(contents)});
    });

    std::set<std::string> name_set;

    // Extract groups.
    root_element.GetChild("registry").ForEachChildNamed("enums", [&](const Element &elem)
    {
        // Construct the group.
        enum_data.groups.push_back({});
        auto &this_group = enum_data.groups.back();

        // Get this group name
        this_group.name = (elem.HasAttribute("group") ? elem.GetAttribute("group") : "");

        // Get the constants.
        elem.ForEachChildNamed("enum", [&](const Element &elem)
        {
            // Skip if it's not a real enum.
            if (elem.HasAttribute("comment") && elem.GetAttribute("comment").find("Not an API enum.") != std::string::npos)
                return;

            // Construct the element.
            this_group.elements.push_back({});
            auto &this_element = this_group.elements.back();

            // Get name.
            this_element.name = elem.GetAttribute("name");

            // Delete this element if it's a duplicate
            if (!name_set.insert(this_element.name).second)
            {
                this_group.elements.pop_back();
                return;
            }

            // Get value.
            this_element.value = elem.GetAttribute("value");
            this_element.negative = this_element.value.front() == '-';

            // Get type.
            if (elem.HasAttribute("type"))
                this_element.suffix = elem.GetAttribute("type");

            // Parse value.
            char *end;
            if (this_element.negative)
                this_element.value_number = std::strtoll(this_element.value.c_str(), &end, 0);
            else
                this_element.value_number = std::strtoull(this_element.value.c_str(), &end, 0);

            // Stop on parse failure.
            if (end == this_element.value.c_str())
                Error(Str("Enum constant `", this_element.name, "` has a value that can't be parsed."));

            // Update max name length.
            if (int(this_element.name.size()) > enum_data.max_name_len)
                enum_data.max_name_len = this_element.name.size();
        });

        // Delete the group if it turned out to be empty.
        if (this_group.elements.empty())
            enum_data.groups.pop_back();
    });

    enum_data.enum_count = 0;
    for (const EnumGroup &group : enum_data.groups)
        enum_data.enum_count += group.elements.size();

    return enum_data;
}


struct FunctionParam
{
    std::string type;
    std::string name;
    std::string category; // Can be empty.
};

struct Function
{
    std::string name;
    std::string return_type;
    std::vector<FunctionParam> params;
};

struct FunctionData
{
    std::vector<Function> functions;

    void PrettyPrint(std::ostream &stream) const
    {
        stream << "functions {\n";

        for (const auto &func : functions)
        {
            stream << "    " << func.name << " : " << func.return_type << " (\n";

            for (const auto &param : func.params)
            {
                stream << "        " << param.name << " : " << param.type;
                if (param.category.size() > 0)
                    stream << " (" << param.category << ')';
                stream << '\n';
            }

            stream << "    }\n";
        }

        stream << "}\n";
    }
};

FunctionData ExtractFunctions(const Element &root_element)
{
    const auto &loc = root_element.GetChild("registry").GetChild("commands");

    FunctionData func_data;

    loc.ForEachChildNamed("command", [&](const Element &elem)
    {
        // Construct the function.
        func_data.functions.push_back({});
        auto &this_func = func_data.functions.back();

        // Make sure the format is correct.
        const auto &proto = elem.GetChild("proto");

        // Get name.
        this_func.name = proto.GetChild("name").GetContainedText();

        // Get return type.
        for (const auto &return_type_part : proto.elements)
        {
            if (!return_type_part.IsTagNamed("name") && !return_type_part.value.empty())
            {
                if (this_func.return_type.size() > 0)
                    this_func.return_type += ' ';
                this_func.return_type += return_type_part.GetContainedText();
            }
        }

        // Get parameters.
        elem.ForEachChildNamed("param", [&](const Element &elem)
        {
            // Construct the parameter.
            this_func.params.push_back({});
            auto &this_param = this_func.params.back();

            // Get type.
            for (const auto &param_type_part : elem.elements)
            {
                if (!param_type_part.IsTagNamed("name") && !param_type_part.value.empty())
                {
                    if (this_param.type.size() > 0)
                        this_param.type += ' ';
                    this_param.type += param_type_part.GetContainedText();
                }
            }

            // Get name.
            this_param.name = elem.GetChild("name").GetContainedText();

            // Get category this parameter has one.
            if (elem.HasAttribute("group"))
                this_param.category = elem.GetAttribute("group");
        });
    });

    return func_data;
}


struct Version
{
    // This is set to the variant name, plus some optional suffix. Functions and enums are not inherited when it changes.
    std::string sub_variant;

    std::set<std::string> functions, functions_deprecated;
    std::set<std::string> enums, enums_deprecated;
};

struct Variant
{
    std::string name;
    std::map<std::pair<int,int>, Version> versions;
};

struct VersionData
{
    std::vector<Variant> variants;
    int version_count;

    void PrettyPrint(std::ostream &stream) const
    {
        stream << "variants {\n";

        for (const auto &variant : variants)
        {
            stream << "    " << variant.name << " {\n";

            for (const auto &version : variant.versions)
            {
                stream << "        [ " << version.first.first << '.' << version.first.second << " , " << version.second.sub_variant << " ] {\n";

                stream << "            funcs_deprecated(" << version.second.functions_deprecated.size() << ") {";
                for (const auto &it : version.second.functions_deprecated)
                    stream << ' ' << it;
                stream << " }\n";

                stream << "            enums_deprecated(" << version.second.enums_deprecated.size() << ") {";
                for (const auto &it : version.second.enums_deprecated)
                    stream << ' ' << it;
                stream << " }\n";

                stream << "            funcs(" << version.second.functions.size() << ") {";
                for (const auto &it : version.second.functions)
                    stream << ' ' << it;
                stream << " }\n";

                stream << "            enums(" << version.second.enums.size() << ") {";
                for (const auto &it : version.second.enums)
                    stream << ' ' << it;
                stream << " }\n";

                stream << "        }\n";
            }

            stream << "    }\n";
        }

        stream << "}\n";
    }
};

VersionData ExtractVersions(const Element &root_element)
{
    VersionData version_data;

    root_element.GetChild("registry").ForEachChildNamed("feature", [&](const Element &elem)
    {
        // Get version string.
        std::string version_string = elem.GetAttribute("number");

        // Parse version string.
        int version_major = 0, version_minor = 0;
        {
            bool major = 1;
            for (const auto &ch : version_string)
            {
                if (ch == '.' && major)
                {
                    major = 0;
                    continue;
                }

                if (ch < '0' || ch > '9')
                    Error(Str("Unable to parse version string in `", elem.FullName(), "`."));

                auto &ver = major ? version_major : version_minor;
                ver = ver * 10 + (ch - '0');
            }
        }

        // Get sub-variant name.
        std::string sub_variant_name = elem.GetAttribute("api");

        // Get variant name by stripping numbers off the sub-variant name.
        std::string variant_name = sub_variant_name;
        while (variant_name.size() > 0 && variant_name.back() >= '0' && variant_name.back() <= '9')
            variant_name.resize(variant_name.size()-1);

        // Try finding an existing variant with this name.
        auto variant_iter = std::find_if(version_data.variants.begin(), version_data.variants.end(), [&](const Variant &v){return v.name == variant_name;});

        // If not found, construct it.
        if (variant_iter == version_data.variants.end())
        {
            version_data.variants.push_back({});
            variant_iter = version_data.variants.end()-1;
            variant_iter->name = variant_name;
        }

        auto &this_variant = *variant_iter;

        // Construct a new version.
        auto &this_version = this_variant.versions.insert({{version_major, version_minor}, {}}).first->second;
        this_version.sub_variant = sub_variant_name;

        // Inherit from another this_version if necessary.
        if (this_variant.versions.size() > 1)
        {
            auto parent_iter = std::prev(this_variant.versions.end(), 2); // We move 2 positions, because we have already inserted the new version at the end.
            if (parent_iter->second.sub_variant == sub_variant_name)
                this_version = parent_iter->second;
        }

        // Get deprecated functions and enums.
        elem.ForEachChildNamed("remove", [&](const Element &elem)
        {
            // Deprecated functions.
            elem.ForEachChildNamed("command", [&](const Element &elem)
            {
                std::string name = elem.GetAttribute("name");
                this_version.functions_deprecated.insert(name);
                this_version.functions.erase(name);
            });

            // Deprecated enums.
            elem.ForEachChildNamed("enum", [&](const Element &elem)
            {
                std::string name = elem.GetAttribute("name");
                this_version.enums_deprecated.insert(name);
                this_version.enums.erase(name);
            });
        });

        // Get added functions and enums.
        elem.ForEachChildNamed("require", [&](const Element &elem)
        {
            // Deprecated functions.
            elem.ForEachChildNamed("command", [&](const Element &elem)
            {
                std::string name = elem.GetAttribute("name");
                this_version.functions_deprecated.erase(name);
                this_version.functions.insert(name);
            });

            // Deprecated enums.
            elem.ForEachChildNamed("enum", [&](const Element &elem)
            {
                std::string name = elem.GetAttribute("name");
                this_version.enums_deprecated.erase(name);
                this_version.enums.insert(name);
            });
        });
    });

    version_data.version_count = 0;
    for (const Variant &variant : version_data.variants)
        version_data.version_count += variant.versions.size();

    return version_data;
}


struct Extension
{
    std::set<std::string> functions;
    std::set<std::string> enums;
};

struct ExtensionData
{
    std::map<std::string, Extension> extensions;

    void PrettyPrint(std::ostream &stream) const
    {
        stream << "extensions {\n";

        for (const auto &extension : extensions)
        {
            stream << "    " << extension.first << " {\n";

            stream << "        funcs(" << extension.second.functions.size() << ") {";
            for (const auto &it : extension.second.functions)
                stream << ' ' << it;
            stream << " }\n";

            stream << "        enums(" << extension.second.enums.size() << ") {";
            for (const auto &it : extension.second.enums)
                stream << ' ' << it;
            stream << " }\n";

            stream << "    }\n";
        }

        stream << "}\n";
    }
};

ExtensionData ExtractExtensions(const Element &root_element)
{
    ExtensionData extension_data;

    root_element.GetChild("registry").GetChild("extensions").ForEachChildNamed("extension", [&](const Element &elem)
    {
        // Get name.
        std::string name = elem.GetAttribute("name");

        // Construct the extension.
        auto &this_extension = extension_data.extensions.insert({name, {}}).first->second;

        // Get functions and enums.
        elem.ForEachChildNamed("require", [&](const Element &elem)
        {
            // Deprecated functions.
            elem.ForEachChildNamed("command", [&](const Element &elem)
            {
                std::string name = elem.GetAttribute("name");
                this_extension.functions.insert(name);
            });

            // Deprecated enums.
            elem.ForEachChildNamed("enum", [&](const Element &elem)
            {
                std::string name = elem.GetAttribute("name");
                this_extension.enums.insert(name);
            });
        });
    });

    return extension_data;
}


struct Component
{
    std::string name;

    bool is_extension = 0;

    std::set<std::string> functions, enums;
};

struct ComponentData
{
    std::vector<Component> components; // The list is sorted so that extensions come after regular versions.
    std::map<std::string, int> name_to_index;

    void PrettyPrint(std::ostream &stream) const
    {
        for (const Component &component : components)
            stream << component.name << '\n';
    }
};

ComponentData GetComponents(const VersionData &version_data, const ExtensionData &extension_data)
{
    ComponentData component_data;

    for (const Variant &variant : version_data.variants)
    for (const auto &version_pair : variant.versions)
    {
        int major = version_pair.first.first;
        int minor = version_pair.first.second;
        const Version &version = version_pair.second;

        bool has_separate_profiles = version.functions_deprecated.size() > 0 || version.enums_deprecated.size() > 0;

        std::string name = Str(variant.name, "_", major, ".", minor);

        Component new_component;
        new_component.name = name + (has_separate_profiles ? "_core" : "");
        new_component.functions = version.functions;
        new_component.enums = version.enums;
        component_data.components.push_back(new_component);

        if (has_separate_profiles)
        {
            new_component.name = name + "_compat";
            new_component.functions.insert(version.functions_deprecated.begin(), version.functions_deprecated.end());
            new_component.enums.insert(version.enums_deprecated.begin(), version.enums_deprecated.end());
            component_data.components.push_back(new_component);
        }
    }

    for (const auto &extension_pair : extension_data.extensions)
    {
        std::string name = extension_pair.first;
        const Extension &extension = extension_pair.second;

        Component new_component;
        new_component.name = name;
        new_component.functions = extension.functions;
        new_component.enums = extension.enums;
        new_component.is_extension = 1;
        component_data.components.push_back(new_component);
    }

    for (std::size_t i = 0; i < component_data.components.size(); i++)
        component_data.name_to_index.insert({component_data.components[i].name, i});

    return component_data;
}


namespace Codegen
{
    std::ofstream output_file;

    bool at_line_start = 1;
    int indentation = 0;
    int section_depth = 0;

    const std::string indentation_string = "    ";

    void OpenFile(std::string name)
    {
        output_file = std::ofstream(name);
        if (!output_file)
            Error(Str("Unable to open `", name, "` for writing."));
        at_line_start = 1;
        indentation = 0;
        section_depth = 0;
        std::cout << "Generating " << name << '\n';
    }

    int Indent()
    {
        return indentation * indentation_string.size();
    }
}

void Output(const std::string &str)
{
    for (const char *ptr = str.c_str(); *ptr; ptr++)
    {
        char ch = *ptr;

        if (ch == '}' && Codegen::indentation > 0)
            Codegen::indentation--;

        if (Codegen::at_line_start)
        {
            if (std::strchr(" \t\r", ch))
                continue;

            for (int i = (ch == '@'); i < Codegen::indentation; i++)
                Codegen::output_file << Codegen::indentation_string;
            Codegen::at_line_start = 0;
        }

        Codegen::output_file.put(ch == '$' || ch == '@' ? ' ' : ch);

        if (ch == '{')
            Codegen::indentation++;

        if (ch == '\n')
            Codegen::at_line_start = 1;
    }
}

template <typename ...P> void Output(const P &... params)
{
    Output(Str(params...));
}

void Section(std::string header, std::function<void()> func)
{
    Output(header, "\n{\n");
    func();
    Output("}\n");
}
void SectionSC(std::string header, std::function<void()> func) // 'sc' stands for 'end with semicolon'
{
    Output(header, "\n{\n");
    func();
    Output("};\n");
}

void DecorativeSection(std::string name, std::function<void()> func)
{
    Output("//{", std::string(Codegen::section_depth+1, ' '), name, "\n");
    Codegen::indentation--;
    Codegen::section_depth++;
    func();
    Codegen::section_depth--;
    Output("//}", std::string(Codegen::section_depth+1, ' '), name, "\n");
    Codegen::indentation++;
}

void NextLine()
{
    Output("\n");
}


int main()
{
    #ifdef _WIN32
    #  define D "\\"
    #else
    #  define D "/"
    #endif

    #ifdef _WIN32
    std::system("rmdir /S /Q out >NUL");
    #else
    std::system("rm -rf out >/dev/null");
    #endif

    std::system("mkdir out && "
                "mkdir out" D "include &&"
                "mkdir out" D "src");

    std::cout << "Loading `gl.xml`\n";
    std::string source = LoadFile("gl.xml");

    std::cout << "Lexing XML\n";
    std::vector<Token> tokens = LexSource(source);

    std::cout << "Parsing XML\n";
    Element root_element = ParseTokens(tokens);

    #if 1
    { // Dump XML tree
        std::cout << "Dumping XML tree\n";
        std::ofstream xml_tree_dump("out/xml_tree_dump.txt");
        if (!xml_tree_dump) Error("Unable to open `out/xml_tree_dump.txt` for writing.");
        root_element.PrettyPrint(xml_tree_dump);
        xml_tree_dump.close();
    }
    #endif

    std::cout << "Extracting types\n";
    std::string types = ExtractTypes(root_element);

    std::cout << "Extracting enums     ";
    EnumData enum_data = ExtractEnums(root_element);
    std::cout << " - " << enum_data.enum_count << " found\n";

    std::cout << "Extracting functions ";
    FunctionData func_data = ExtractFunctions(root_element);
    std::cout << " - " << func_data.functions.size() << " found\n";

    std::cout << "Extracting versions  ";
    VersionData version_data = ExtractVersions(root_element);
    std::cout << " - " << version_data.version_count << " found\n";

    std::cout << "Extracting extensions";
    ExtensionData extension_data = ExtractExtensions(root_element);
    std::cout << " - " << extension_data.extensions.size() << " found\n";

    ComponentData component_data = GetComponents(version_data, extension_data);

    std::cout << "Dumping data\n";
    { // Dump components
        std::ofstream components("out/components.txt");
        if (!components) Error("Unable to open `out/components.txt` for writing.");
        component_data.PrettyPrint(components);
        components.close();
    }
    #if 1
    { // Dump more data
        std::ofstream types_dump("out/types_dump.txt");
        if (!types_dump) Error("Unable to open `out/types_dump.txt` for writing.");
        types_dump << types;
        types_dump.close();

        std::ofstream enums_dump("out/enums_dump.txt");
        if (!enums_dump) Error("Unable to open `out/enums_dump.txt` for writing.");
        enum_data.PrettyPrint(enums_dump);
        enums_dump.close();

        std::ofstream functions_dump("out/functions_dump.txt");
        if (!functions_dump) Error("Unable to open `out/functions_dump.txt` for writing.");
        func_data.PrettyPrint(functions_dump);
        functions_dump.close();

        std::ofstream versions_dump("out/versions_dump.txt");
        if (!versions_dump) Error("Unable to open `out/versions_dump.txt` for writing.");
        version_data.PrettyPrint(versions_dump);
        versions_dump.close();

        std::ofstream extensions_dump("out/extensions_dump.txt");
        if (!extensions_dump) Error("Unable to open `out/extensions_dump.txt` for writing.");
        extension_data.PrettyPrint(extensions_dump);
        extensions_dump.close();
    }
    #endif

    std::set<std::string> needed_funcitons, needed_enums;

    { // Get input
        std::cout << "\n"
                     "What components (versions and extensions) do you want?\n"
                     "  Consult `out/components.txt` for the list of known components.\n"
                     "  Enter desired components as a space-separated list.\n";

        while (![&]{
            std::cout << '\n';

            std::string input_line;
            if (!std::getline(std::cin, input_line))
                Error("Invalid input.");

            std::istringstream input_line_ss(input_line);

            std::vector<std::string> desired_components(std::istream_iterator<std::string>(input_line_ss), std::istream_iterator<std::string>{});

            { // Check for duplicates
                std::set<std::string> component_set;
                for (const std::string &name : desired_components)
                {
                    if (!component_set.insert(name).second)
                    {
                        std::cout << "Duplicate component `" << name << "`.\n";
                        return 0;
                    }
                }
            }

            { // Check component names and make sure there is at least one version specified
                needed_funcitons.clear();
                needed_enums.clear();

                bool got_version = 0;

                for (const std::string &name : desired_components)
                {
                    if (auto it = component_data.name_to_index.find(name); it != component_data.name_to_index.end())
                    {
                        if (!component_data.components[it->second].is_extension)
                            got_version = 1;
                    }
                    else
                    {
                        std::cout << "Unknown component `" << name << "`.\n";
                        return 0;
                    }
                }

                if (!got_version)
                {
                    std::cout << "Expected at least one version.\n";
                    return 0;
                }
            }

            return 1;
        }()) {}


    }

    { // Generate code

    }

    return 0;
}
