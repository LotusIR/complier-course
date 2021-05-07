#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include "Defination.h"



struct token
{
    std::string text;
    token_type type;
    token(std::string _text,token_type _type) : text(_text),type(_type) {}
    token() {}
};
class Lexer
{
private:
    static std::shared_ptr<Lexer> lexer;
    std::vector<token> tokens;
    Defination def;
    friend class Grammer;

    Lexer() {}

    bool _getTokens(std::string &s, std::vector<token> &tokens, std::ofstream &ofs,int line,int it = 0)
    {
        while (it < s.length() && (s[it] == ' ' || s[it] == '\t') )
            ++it;
        if (it == s.length())
            return true;
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
        else if (tokens.back().type != ident && tokens.back().type != number && s[it] == '-' && isdigit(s[it+1]) ) {
            text += s[it++];
            while (it < s.length() && isdigit(s[it]))
            {
                text += s[it++];
            }
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
        if (def.type.count(text)) {
            tokens.push_back(token(text,def.type[text]));
        }
        else if (isdigit(text[0]) || (text.length() > 1 && text[0] == '-' && isdigit(text[1]))) {
            tokens.push_back(token(text,token_type::number));
        }
        else {
            bool isIdent = true;
            if (!isalpha(text[0])) isIdent = false;
            for (int i = 1; i < text.length() && isIdent; ++i) { 
                if (!isalpha(text[i]) && !isdigit(text[i])) isIdent = false;
            }
            if (isIdent) tokens.push_back(token(text,token_type::ident));
            else {
                ofs << "\n";
                for (int i = 0; i < s.length()+50; ++i) ofs << (i==0||i==s.length()+49?"+":"-");
                ofs << "\n\n";
                ofs << "Fatal error in:\n\t" << "line " << line << ": \"" << s << "\"\n";
                ofs << "Error type:\n\t";
                ofs << "Undefined symbol -> " << text << " (" << "line:" << line << ":" << it-text.length() << ") \n";
                ofs << "\n";
                for (int i = 0; i < s.length()+50; ++i) ofs << (i==0||i==s.length()+49?"+":"-");
                ofs << "\n\n";
                return false;
            }
        }
        ofs << "(" << def.ty[tokens.back().type] << ", " << tokens.back().text << ")" << std::endl;
        if (it != s.length())
            return _getTokens(s, tokens, ofs, line, it);
        else return true;
    }

    bool _work(std::ifstream &ifs,std::ofstream &ofs) {
        std::string str;
        bool ok = true;
        int line = 0;
        while (ok && getline(ifs, str))
            ok &= _getTokens(str, tokens, ofs, ++line);
        if (ok) {
            ofs << "Analyze success\n";
        }
        else {
            ofs << "Analyze failed\n";
        }
        return ok;
    }

    static std::vector<token> & getTokens() {
        return lexer->tokens;
    }

    static Defination & getDefination() {
        return lexer->def;
    }

public:
    static bool analyze(std::string input_file) {
        std::string output_file;
        for (auto& ch:input_file) {
            if (ch != '.') output_file += ch;
            else break;
        }
        return analyze(input_file,output_file+"_lexer_result.txt");
    }

    static bool analyze(std::string input_file,std::string output_file) {
        if (lexer == nullptr) lexer = std::shared_ptr<Lexer>(new Lexer);
        std::ifstream ifs(input_file);
        std::ofstream ofs(output_file);
        return lexer->_work(ifs,ofs);
    }
};

std::shared_ptr<Lexer> Lexer::lexer = nullptr;