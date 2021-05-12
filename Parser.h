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

    bool _parser_ok(std::ofstream & ofs) {
        std::stack< parser_status > stac;
        for (int i = 0; i < tokens.size(); ++i) {
            if (stac.empty()) {
                utils::err_unex_token(ofs,tokens,i,def);
                return false;
            }
            auto curStatus = stac.top();
            token tk = tokens[i];
            if (!def.predict[curStatus].count(tk.type)) {
                utils::err_unex_token(ofs,tokens,i,def);
                return false;
            }
            else {
                if (def.predict[curStatus][tk.type][0] == parser_status::ok) {
                    stac.pop();
                }
                else {
                    stac.pop();
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