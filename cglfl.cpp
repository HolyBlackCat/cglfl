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

#define VERSION "1.0.0 rc 1"

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

std::string ReadString()
{
    std::string ret;
    bool ok = bool(std::getline(std::cin, ret));
    if (!ok)
        Error("Unable to read from the standard input.");
    return ret;
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
    std::map<std::string, std::pair<int, int>> name_to_indices;

    int enum_count;

    const EnumConstant &Find(const std::string &name)
    {
        auto it = name_to_indices.find(name);
        if (it == name_to_indices.end())
            Error(Str("Internal: Enum constant `", name, "` not found."));
        auto [group_index, elem_index] = it->second;
        return groups[group_index].elements[elem_index];
    }

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

    for (std::size_t i = 0; i < enum_data.groups.size(); i++)
    for (std::size_t j = 0; j < enum_data.groups[i].elements.size(); j++)
    {
        const EnumConstant &enum_const = enum_data.groups[i].elements[j];
        if (!enum_data.name_to_indices.insert({enum_const.name, {i, j}}).second)
            Error(Str("The spec has two enum constants named `", enum_const.name, "`."));
    }

    return enum_data;
}


struct FunctionParam
{
    std::string type_l;
    std::string type_r;
    std::string name;
    std::string category; // Can be empty.
};

struct Function
{
    std::string name;
    std::string return_type;
    std::vector<FunctionParam> params;

    bool NeedSpaceAfterReturnType() const
    {
        return return_type.size() > 0 && return_type.back() != '*';
    }

    enum class ParamMode {full, types_only, names_only};

    std::string ParameterList(ParamMode mode, bool spaces_after_commas = 0) const
    {
        std::string ret;

        bool first = 1;
        for (const FunctionParam &param : params)
        {
            if (first)
            {
                first = 0;
            }
            else
            {
                ret += ',';
                if (spaces_after_commas)
                    ret += ' ';
            }

            if (mode != ParamMode::names_only)
                ret += param.type_l;
            if (mode != ParamMode::types_only)
            {
                if (mode != ParamMode::names_only && ret.size() > 0 && ret.back() != '*')
                    ret += ' ';
                ret += param.name;
            }
            if (mode != ParamMode::names_only)
                ret += param.type_r;
        }

        return ret;
    }

    operator std::string() const
    {
        return name;
    }

    friend bool operator<(const std::string &a, const std::string &b)
    {
        return a < b;
    }
};

struct FunctionData
{
    std::set<Function, std::less<>> functions;

    const Function &Find(const std::string &name)
    {
        auto it = functions.find(name);
        if (it == functions.end())
            Error(Str("Internal: Function `", name, "` not found."));
        return *it;
    }

    void PrettyPrint(std::ostream &stream) const
    {
        stream << "functions {\n";

        for (const auto &func : functions)
        {
            stream << "    " << func.name << " : " << func.return_type << " (\n";

            for (const auto &param : func.params)
            {
                stream << "        " << param.name << " : " << param.type_l;
                if (param.type_r.size())
                    stream << "|" << param.type_r;
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
        Function this_func;

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
            bool seen_name = 0;
            for (const auto &param_type_part : elem.elements)
            {
                if (param_type_part.IsTagNamed("name"))
                    seen_name = 1;

                if (!param_type_part.IsTagNamed("name") && !param_type_part.value.empty())
                {
                    std::string &type = (seen_name ? this_param.type_r : this_param.type_l);

                    if (type.size() > 0)
                        type += ' ';
                    type += param_type_part.GetContainedText();
                }
            }

            // Get name.
            this_param.name = elem.GetChild("name").GetContainedText();

            // Get category if this parameter has one.
            if (elem.HasAttribute("group"))
                this_param.category = elem.GetAttribute("group");
        });

        // Insert function into the set.
        if (!func_data.functions.insert(std::move(this_func)).second)
            Error(Str("The spec contains more than one function named `", this_func.name, "`."));
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
        auto [this_version_iter, this_version_is_unique] = this_variant.versions.insert({{version_major, version_minor}, {}});
        if (!this_version_is_unique)
            Error(Str("Duplicate internal version name `", this_variant.name, ":", version_major, ".", version_minor, "`. (A spec defect or an internal error.)."));

        auto &this_version = this_version_iter->second;
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

    const Extension &Find(const std::string &name)
    {
        auto it = extensions.find(name);
        if (it == extensions.end())
            Error(Str("Internal: Extension `", name, "` not found."));
        return it->second;
    }

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
        auto [this_extension_it, was_inserted] = extension_data.extensions.insert({name, {}});
        if (!was_inserted)
            Error(Str("The spec contains a duplicate extension: `", name, "`."));

        auto &this_extension = this_extension_it->second;

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

namespace Codegen
{
    namespace impl
    {
        std::string output_file_name;
        std::ofstream output_file;

        std::stringstream ss;
        const std::stringstream::fmtflags stdfmt = ss.flags();

        bool at_line_start = 1;
        int indentation = 0;
        int section_depth = 0;

        constexpr const char *indentation_string = "    ", *indentation_string_labels = "  ";
    }

    void OpenFile(std::string file_name)
    {
        impl::output_file_name = file_name;

        impl::output_file.open(file_name);
        if (!impl::output_file)
            Error(Str("Unable to open `", file_name, "` for writing."));

        std::cout << "Generating `" << file_name << "`\n";
    }

    void CloseFile()
    {
        if (!impl::output_file.is_open())
            return;

        if (!impl::output_file)
            Error(Str("Unable to write to `", impl::output_file_name, "`."));

        impl::output_file.close();
    }

    void OutputStr(const std::string &str)
    {
        for (const char *ptr = str.c_str(); *ptr; ptr++)
        {
            char ch = *ptr;

            if (ch == '}' && impl::indentation > 0)
                impl::indentation--;

            if (impl::at_line_start)
            {
                if (std::strchr(" \t\r", ch))
                    continue;

                for (int i = 0; i < impl::indentation; i++)
                    impl::output_file << (i == impl::indentation-1 && ch == '@' ? impl::indentation_string_labels : impl::indentation_string);
                impl::at_line_start = 0;
            }

            if (ch != '@')
                impl::output_file.put(ch == '$' ? ' ' : ch);

            if (ch == '{')
                impl::indentation++;

            if (ch == '\n')
                impl::at_line_start = 1;
        }
    }

    template <typename ...P> void Output(const P &... params)
    {
        OutputStr(Str(params...));
    }

    void Section(std::string header, std::function<void()> func)
    {
        Output(header, "\n{\n");
        func();
        Output("}\n");
    }
    void SectionSemi(std::string header, std::function<void()> func) // 'sc' stands for 'end with semicolon'
    {
        Output(header, "\n{\n");
        func();
        Output("};\n");
    }

    void SectionDecorative(std::string name, std::function<void()> func)
    {
        Output("//{", std::string(impl::section_depth+1, ' '), name, "\n");
        impl::indentation--;
        impl::section_depth++;
        func();
        impl::section_depth--;
        Output("//}", std::string(impl::section_depth+1, ' '), name, "\n");
        impl::indentation++;
    }

    void NextLine()
    {
        Output("\n");
    }
}


int main()
{
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

    std::cout << "Extracting enum constants";
    EnumData enum_data = ExtractEnums(root_element);
    std::cout << " - " << enum_data.enum_count << " found\n";

    std::cout << "Extracting functions     ";
    FunctionData func_data = ExtractFunctions(root_element);
    std::cout << " - " << func_data.functions.size() << " found\n";

    std::cout << "Extracting versions      ";
    VersionData version_data = ExtractVersions(root_element);
    std::cout << " - " << version_data.version_count << " found\n";

    std::cout << "Extracting extensions    ";
    ExtensionData extension_data = ExtractExtensions(root_element);
    std::cout << " - " << extension_data.extensions.size() << " found\n";

    std::cout << "Dumping data\n";
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

    const Version *selected_version = 0;
    const Variant *selected_version_variant = 0;
    std::pair<int, int> selected_version_number;

    bool core_profile = 0, compat_profile = 0; // At most one of those will be set.

    std::vector<const Function *> primary_functions, all_functions;
    std::vector<const EnumConstant *> all_enums;

    std::map<std::string, std::vector<const Function *>> extensions; // Note that a single function can belong to several extensions, and maybe also to some versions.


    { // Get user input
        { // Ask for api version
            auto VersionName = [](const Variant &variant, const std::pair<int, int> &version_number) -> std::string
            {
                return Str(variant.name, version_number.first, ".", version_number.second);
            };

            std::cout << "\nFound following versions:\n ";
            for (const Variant &variant : version_data.variants)
            for (const auto &[number, version] : variant.versions)
                std::cout << ' ' << VersionName(variant, number);
            std::cout << "\n";

            while (1)
            {
                std::cout << "Select a version: ";
                std::string version_name = ReadString();

                bool found = 0;
                for (const Variant &variant : version_data.variants)
                {
                    for (const auto &[number, version] : variant.versions)
                    {
                        if (version_name == VersionName(variant, number))
                        {
                            found = 1;
                            selected_version = &version;
                            selected_version_variant = &variant;
                            selected_version_number = number;
                            break;
                        }
                    }

                    if (found)
                        break;
                }

                if (!found)
                {
                    std::cout << "No such version.\n";
                    continue;
                }

                break;
            }
        }

        { // Ask for api profile (core or compat) if necessary
            if (selected_version->enums_deprecated.size() > 0 || selected_version->functions_deprecated.size() > 0)
            {
                std::cout << "Available profiles:\n  core compat\n";
                while (1)
                {
                    std::cout << "Select a profile: ";
                    std::string profile = ReadString();
                    bool is_core = profile == "core";
                    bool is_compat = profile == "compat";
                    if (!is_core && !is_compat)
                    {
                        std::cout << "No such profile.\n";
                        continue;
                    }

                    core_profile = is_core;
                    compat_profile = is_compat;
                    break;
                }
            }
        }

        std::set<std::string> selected_enums;

        { // Make function and enum lists
            // Function list
            for (const std::string &func : selected_version->functions)
                primary_functions.push_back(&func_data.Find(func));

            if (compat_profile)
            {
                for (const std::string &func : selected_version->functions_deprecated)
                    primary_functions.push_back(&func_data.Find(func));
            }

            std::sort(primary_functions.begin(), primary_functions.end(), [](const Function *a, const Function *b)
            {
                // Sorting shouldn't be necessary if `compat_profile == false`, but I'll do it unconditionally for a good measure.
                return a->name < b->name;
            });

            // Enum list
            selected_enums.insert(selected_version->enums.begin(), selected_version->enums.end());
            if (compat_profile)
                selected_enums.insert(selected_version->enums_deprecated.begin(), selected_version->enums_deprecated.end());
        }

        std::set<std::string> selected_extensions;

        { // Ask for extension lists
            std::cout << "Found following extensions:\n ";
            for (const auto &[name, ext] : extension_data.extensions)
                std::cout << ' ' << name;
            std::cout << "\n";

            while (1)
            {
                if (selected_extensions.size() > 0)
                    std::cout << "Any more extensions? ";
                else
                    std::cout << "What extensions do you want, if any? ";

                std::string input_str = ReadString();
                if (input_str.empty())
                    break;

                std::istringstream ss(input_str);
                std::string ext_name;
                while (ss >> ext_name)
                {
                    bool found = extension_data.extensions.count(ext_name);
                    if (found)
                    {
                        bool inserted = selected_extensions.insert(ext_name).second;
                        if (inserted)
                            std::cout << "Added `" << ext_name << "`.\n";
                        else
                            std::cout << "Skipping `" << ext_name << "` (already added).\n";
                    }
                    else
                    {
                        std::cout << "Skipping `" << ext_name << "` (not found).\n";
                    }
                }
            }
        }

        { // Make function and enum lists for extensions
            for (const std::string &ext : selected_extensions)
            {
                const auto &ext_info = extension_data.Find(ext);
                auto &funcs = extensions[ext];

                // Function list
                for (const std::string &func : ext_info.functions)
                    funcs.push_back(&func_data.Find(func));

                std::sort(funcs.begin(), funcs.end(), [](const Function *a, const Function *b)
                {
                    // Sorting shouldn't be necessary, but I'll leave it for a good measure.
                    return a->name < b->name;
                });

                // Enum list
                selected_enums.insert(ext_info.enums.begin(), ext_info.enums.end());
            }
        }

        { // Finalize function and enum lists
            // Make combined function list
            all_functions = primary_functions;
            for (const auto &[ext_name, ext] : extensions)
                all_functions.insert(all_functions.end(), ext.begin(), ext.end());
            std::sort(all_functions.begin(), all_functions.end(), [](const Function *a, const Function *b)
            {
                return a->name < b->name;
            });
            all_functions.erase(std::unique(all_functions.begin(), all_functions.end(), [](const Function *a, const Function *b)
            {
                return a->name == b->name;
            }), all_functions.end());

            // Make enum list
            for (const std::string &en : selected_enums)
                all_enums.push_back(&enum_data.Find(en));
        }
    }

    { // Generate code
        std::string disclaimer_generated =
            "// This file is a part of CGLFL (configurable OpenGL function loader).\n"
            "// Generated, do no edit!\n"
            "//\n"
            "// Version: " VERSION "\n"
            "// API: " + Str(selected_version_variant->name, " ", selected_version_number.first, ".", selected_version_number.second,
                core_profile ? " (core profile)" : compat_profile ? " (compatibility profile)" : "") + "\n"
            "// Extensions:";
        for (const auto &[ext_name, ext] : extensions)
            disclaimer_generated += " " + ext_name;
        disclaimer_generated += "\n";

        using namespace Codegen;

        { // `macros_internal.hpp`
            OpenFile("out/include/cglfl/macros_internal.hpp");

            Output("#pragma once\n\n");
            Output(disclaimer_generated);

            NextLine();

            Output("#define CGLFL_FUNCS");
            for (const std::string &func : selected_version->functions)
                Output(" \\\n$   ", func);
            if (compat_profile)
            {
                for (const std::string &func : selected_version->functions_deprecated)
                    Output(" \\\n$   ", func);
            }
            Output("\n");

            NextLine();

            Output("#define CGLFL_EXTS(X)");
            for (const auto &[ext_name, ext] : extensions)
                Output(" \\\n$   X(", ext_name, ")");
            Output("\n");

            NextLine();

            for (const auto &[ext_name, ext] : extensions)
            {
                Output("#define CGLFL_EXT_FUNCS_", ext_name);
                for (const auto *func : ext)
                    Output(" \\\n$   ", func->name);
                Output("\n");
            }

            CloseFile();
        }

        { // `macros_public.hpp`
            OpenFile("out/include/cglfl/macros_public.hpp");

            Output("#pragma once\n\n");
            Output(disclaimer_generated);

            NextLine();

            Output("#define CGLFL_GL_MAJOR ", selected_version_number.first, "\n");
            Output("#define CGLFL_GL_MINOR ", selected_version_number.second, "\n");
            Output("#define CGLFL_GL_API_", selected_version_variant->name, "\n");
            Output("#define CGLFL_GL_PROFILE_", core_profile ? "core" : compat_profile ? "_compat" : "_none", "\n");

            NextLine();

            int max_func_name_len = 0;
            for (const auto *func : all_functions)
                if (int len = func->name.size(); len > max_func_name_len)
                    max_func_name_len = len;

            int index = 0;
            for (const auto *func_ptr : all_functions)
            {
                const auto &func = *func_ptr;
                Output("#define ", func.name, std::string(max_func_name_len - func.name.size(), ' '), " CGLFL_CALL(",
                    index++, ",",
                    func.name, ",",
                    func.return_type, ",",
                    func.params.size(), ","
                    "(", func.ParameterList(Function::ParamMode::names_only), "),"
                    "(", func.ParameterList(Function::ParamMode::full), "))\n");
            }

            NextLine();

            int max_enum_name_len = 0;
            for (const auto *en : all_enums)
                if (int len = en->name.size(); len > max_enum_name_len)
                    max_enum_name_len = len;

            for (const auto *enum_ptr : all_enums)
            {
                const auto &en = *enum_ptr;
                Output("#define ", en.name, std::string(max_enum_name_len - en.name.size(), ' '), " ", en.value, "\n");
            }

            CloseFile();
        }
    }

    std::cout << "Done!\n";

    return 0;
}
