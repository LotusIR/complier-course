#include <memory>
#include <vector>
#include <fstream>
#include "Lexer.h"

class Grammer {
private:
    friend class Compiler;
    static std::shared_ptr<Grammer> grammer;
    std::vector<token> &tokens;
    Defination &def;
    grammer_status curStatus;
    Grammer():tokens(Lexer::getTokens()),def(Lexer::getDefination()) {}  

    bool _grammer_ok(std::ofstream & ofs) {
        curStatus = grammer_status::expr;
        for (int i = 0; i < tokens.size(); ++i) {
            if (def.predict[expr].count(tokens[i].type)) {
                curStatus = def.predict[expr][tokens[i].type];
            }
            else {
                utils::err_unex_token(ofs,tokens,i,def);
                return false;
            }
        }
        if (def.received_end.count(curStatus)) return true;
        return true;
    }

    bool _work(std::ofstream & ofs) {
        if (_grammer_ok(ofs)) {
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
        return analyze(input_file,output_file+"_grammer_result.txt");
    }

    static bool analyze(std::string input_file,std::string output_file) {
        if (grammer == nullptr) grammer = std::shared_ptr<Grammer>(new Grammer);
        std::ofstream ofs(output_file);
        return grammer->_work(ofs);
    }
};

std::shared_ptr<Grammer> Grammer::grammer = nullptr;