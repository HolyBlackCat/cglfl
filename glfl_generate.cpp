#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

template <typename ...P> std::string Str(const P &... params)
{
    std::ostringstream stream;
    (stream << ... << params);
    return stream.str();
}

void Error(std::string message)
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

struct Element
{
    bool is_tag = 1;
    std::string value; // Text or tag name.

    // Tag only:
    std::map<std::string, std::string> attributes;
    std::vector<Element> elements;
};

void PrintElement(const Element &elem, int indent = 0)
{
    std::string ind(indent * 4, ' ');
    std::cout << ind;
    for (char ch : elem.value)
    {
        std::cout << ch;
        if (ch == '\n')
            std::cout << ind;
    }
    if (elem.is_tag)
    {
        for (const auto &attr : elem.attributes)
            std::cout << " [" << attr.first << '=' << attr.second << ']';
        if (elem.value.size() > 0)
            std::cout << ' ';
        std::cout << '{';
        if (elem.elements.size() > 0)
        {
            std::cout << '\n';
            for (const auto &child : elem.elements)
                PrintElement(child, indent+1);
            std::cout << ind;
        }
        std::cout << '}';
    }
    std::cout << '\n';
}

int main()
{
    std::string source;

    { // Load file
        std::cout << "Loading `gl.xml`\n";

        FILE *file = std::fopen("gl.xml", "rb");

        if (!file)
            Error("Unable to open `gl.xml`.");

        std::fseek(file, 0, SEEK_END);
        auto size = std::ftell(file);
        std::fseek(file, 0, SEEK_SET);

        if (std::ferror(file) || size == EOF)
            Error("Unable to get size of file `gl.xml`.");

        source.resize(size);
        if (!std::fread(source.data(), size, 1, file))
            Error("Unable to read from file `gl.xml`.");
    }

    std::deque<Token> tokens;

    { // Lexing XML
        std::cout << "Lexing XML\n";

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
    }

    Element root_element;

    { // Parsing XML
        std::cout << "Parsing XML\n";

        std::vector<Element *> stack = {&root_element}; // There is no danger of ending the root tag, since empty tag names are catched earlier.

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
                    if (token.type != Token::tag_terse)
                        stack.push_back(&obj);

                    obj.is_tag = 1;
                    obj.value = token.value;
                    obj.attributes = token.attributes;
                }
                break;
              case Token::tag_end:
                {
                    if (token.value != stack.back()->value)
                        Error(Str("Closing tag `</", token.value, ">` has no matching opening tag."));
                    stack.pop_back();
                }
                break;
              case Token::text:
                {
                    auto &parent = *stack.back();
                    parent.elements.push_back({});

                    auto &obj = parent.elements.back();

                    obj.is_tag = 0;
                    obj.value = token.value;
                }
                break;
              default:
                Error("Unknown token type. (Internal error.)");
                break;
            }
        }
    }

    PrintElement(root_element);

    return 0;
}
