#include <memory>
#include <vector>
#include <fstream>
#include <stack>
#include "Lexer.h"

class Parser {
private:
    friend class Compiler;
    static std::shared_ptr<Parser> parser;
    std::vector<token> &tokens;
    Defination &def;
    parser_status curStatus;
    Parser():tokens(Lexer::getTokens()),def(Lexer::getDefination()) {}  
    
    bool match(token_type &tk_type,parser_status &status) {
        return (tk_type == token_type::plus && status == tk_plus)
            || (tk_type == token_type::minus && status == tk_minus)
            || (tk_type == token_type::times && status == tk_times)
            || (tk_type == token_type::slash && status == tk_slash)
            || (tk_type == token_type::lparen && status == tk_lparen)
            || (tk_type == token_type::rparen && status == tk_rparen)
            || (tk_type == token_type::ident && status == tk_ident)
            || (tk_type == token_type::number && status == tk_number)
            || (tk_type == token_type::end_of_file && status == tk_eof);
    }

    bool _parser_ok(std::ofstream & ofs) {
        std::stack< parser_status > stac;
        stac.push(tk_eof);
        stac.push(expr);
        int it = 0;
        while (it < tokens.size()) {
            if (stac.empty()) {
                utils::err_unex_token(ofs,tokens,it,def);
                return false;
            }
            auto curStatus = stac.top();
            stac.pop();
            token tk = tokens[it];
            if (match(tk.type,curStatus)) ++it;
            else if (!def.predict[curStatus].count(tk.type)) {
                utils::err_unex_token(ofs,tokens,it,def);
                return false;
            }
            else {
                if (def.predict[curStatus][tk.type][0] == epsilon) continue;
                else {
                    for (auto &status :def.predict[curStatus][tk.type]) {
                        stac.push(status);
                    }
                }
            }
        }
        if (stac.empty()) return true;
        else {
            utils::err_unex_end(ofs,tokens,def);
            return false;
        }
    }

    bool _work(std::ofstream & ofs) {
        if (_parser_ok(ofs)) {
            ofs << "Analyze success\n";
            return true;
        }
        else {
            ofs << "Analyze failed\n";
            return false;
        }
    }

public:
    static bool analyze(std::string input_file) {
        std::string output_file;
        for (auto& ch:input_file) {
            if (ch != '.') output_file += ch;
            else break;
        }
        return analyze(input_file,output_file+"_parser_result.txt");
    }

    static bool analyze(std::string input_file,std::string output_file) {
        if (parser == nullptr) parser = std::shared_ptr<Parser>(new Parser);
        std::ofstream ofs(output_file);
        return parser->_work(ofs);
    }
};

std::shared_ptr<Parser> Parser::parser = nullptr;