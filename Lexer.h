#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

const std::string ty[] = {"beginsym",
                   "callsym",
                   "constsym",
                   "dosym",
                   "endsym",
                   "ifsym",
                   "oddsym",
                   "proceduresym",
                   "readsym",
                   "thensym",
                   "varsym",
                   "whilesym",
                   "writesym",
                   "ident",
                   "number",
                   "plus",
                   "minus",
                   "times",
                   "slash",
                   "eql",
                   "neq",
                   "lss",
                   "leq",
                   "gtr",
                   "geq",
                   "becomes",
                   "lparen",
                   "rparen",
                   "comma",
                   "semicolon",
                   "period"};

enum token_type
{
    beginsym,
    callsym,
    constsym,
    dosym,
    endsym,
    ifsym,
    oddsym,
    proceduresym,
    readsym,
    thensym,
    varsym,
    whilesym,
    writesym,
    ident,
    number,
    plus,
    minus,
    times,
    slash,
    eql,
    neq,
    lss,
    leq,
    gtr,
    geq,
    becomes,
    lparen,
    rparen,
    comma,
    semicolon,
    period
};

struct token
{
    std::string text;
    token_type type;
    token(std::string _text,token_type _type) : text(_text),type(_type) {}
    token() {}
};

struct Lexer
{
    std::unordered_map<std::string, token_type> type;

    void init()
    {
        type["begin"] = beginsym;
        type["call"] = callsym;
        type["const"] = constsym;
        type["do"] = dosym;
        type["end"] = endsym;
        type["if"] = ifsym;
        type["odd"] = oddsym;
        type["procedure"] = proceduresym;
        type["read"] = readsym;
        type["then"] = thensym;
        type["var"] = varsym;
        type["while"] = whilesym;
        type["write"] = writesym;
        type["+"] = token_type::plus;
        type["-"] = token_type::minus;
        type["*"] = times;
        type["/"] = slash;
        type["="] = eql;
        type["#"] = neq;
        type["<"] = lss;
        type["<="] = leq;
        type[">"] = gtr;
        type[">="] = geq;
        type[":="] = becomes;
        type["("] = lparen;
        type[")"] = rparen;
        type[","] = comma;
        type[";"] = semicolon;
        type["."] = period;
    }

    std::vector<token> tokens;

    void getTokens(std::string &s, std::vector<token> &tokens, int it = 0)
    {
        while (it < s.length() && (s[it] == ' ' || s[it] == '\t') )
            ++it;
        if (it == s.length())
            return;
        std::string text;
        if (isalpha(s[it]))
        {
            while (it < s.length() && (isalpha(s[it]) || isdigit(s[it])))
            {
                text += s[it++];
            }
            for (auto &ch : text)
                ch = tolower(ch);
        }
        else if (isdigit(s[it]))
        {
            while (it < s.length() && isdigit(s[it]))
            {
                text += s[it++];
            }
        }
        else
        {
            text += s[it++];
            switch (text[0])
            {
            case '<':
            case '>':
            case ':':
                if (it < s.length() && s[it] == '=')
                {
                    text += s[it++];
                }
                break;
            default:
                break;
            }
        }
        if (type.count(text)) {
            tokens.push_back(token(text,type[text]));
        }
        else if (isdigit(text[0])){
            tokens.push_back(token(text,token_type::number));
        }
        else {
            bool isIdent = true;
            for (auto& ch:text) {
                if (ch != '_' && !isalpha(ch)) isIdent = false;
            }
            if (isIdent) tokens.push_back(token(text,token_type::ident));
            else {
                std::cout << "Undefined symbol -> " << text << '\n';
                return;
            }
        }
        if (it != s.length())
            getTokens(s, tokens, it);
    }
};