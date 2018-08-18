#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
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
    std::map<std::string, std::vector<std::string>> categories;
    int max_name_len;

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

        std::vector<std::string> contents;
        elem.ForEachChildNamed("enum", [&](const Element &elem)
        {
            contents.push_back(elem.GetAttribute("name"));
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


int main()
{
    std::system("mkdir out");

    // Load gl.xml
    std::cout << "Loading `gl.xml`\n";
    std::string source = LoadFile("gl.xml");

    // Lex XML
    std::cout << "Lexing XML\n";
    std::vector<Token> tokens = LexSource(source);

    // Parse XML
    std::cout << "Parsing XML\n";
    Element root_element = ParseTokens(tokens);

    // Dump XML tree
    if (0)
    {
        std::cout << "Dumping XML tree\n";
        std::ofstream xml_tree_dump("out/xml_tree_dump.txt");
        if (!xml_tree_dump) Error("Unable to open `out/xml_tree_dump.txt` for writing.");
        root_element.PrettyPrint(xml_tree_dump);
    }

    // Extract types
    std::cout << "Extracting types\n";
    std::string types = ExtractTypes(root_element);

    // Extract enums
    std::cout << "Extracting enums\n";
    EnumData enum_data = ExtractEnums(root_element);

    // Extract functions
    std::cout << "Extracting functions\n";
    FunctionData func_data = ExtractFunctions(root_element);

    // Dump data
    if (1)
    {
        std::cout << "Dumping data\n";
        std::ofstream types_dump("out/types_dump.txt");
        if (!types_dump) Error("Unable to open `out/types_dump.txt` for writing.");
        types_dump << types;

        std::ofstream enums_dump("out/enums_dump.txt");
        if (!enums_dump) Error("Unable to open `out/enums_dump.txt` for writing.");
        enum_data.PrettyPrint(enums_dump);

        std::ofstream functions_dump("out/functions_dump.txt");
        if (!functions_dump) Error("Unable to open `out/functions_dump.txt` for writing.");
        func_data.PrettyPrint(functions_dump);
    }

    return 0;
}
