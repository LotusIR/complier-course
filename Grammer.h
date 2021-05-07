#include <memory>
#include <vector>
#include <fstream>
#include "Lexer.h"

class Grammer {
private:
    static std::shared_ptr<Grammer> grammer;
    std::vector<token> &tokens;
    Defination &def;
    grammer_status curStatus;
    Grammer():tokens(Lexer::getTokens()),def(Lexer::getDefination()) {}  

    bool _work(std::ofstream & ofs) {
        curStatus = grammer_status::expr;
        for (int i = 0; i < tokens.size(); ++i) {
            if (def.predict[expr].count(tokens[i].type)) {
                curStatus = def.predict[expr][tokens[i].type];
            }
            else {
                ofs << "\n";
                for (int j = 0; j < tokens[i].text.length()+100; ++j) ofs << (j==0||j==tokens[i].text.length()+49?"+":"-");
                ofs << "\n\n";
                ofs << "Fatal error in:\n\t";
                ofs << "Error type:\n\t";
                ofs << "Unexpected token -> " << tokens[i].text << " (token_type: " << def.ty[tokens[i].type] << ") ";
                if (i == 0) ofs << "at the beginning";
                else ofs << "after token: " << tokens[i-1].text << " (token_type: " << def.ty[tokens[i-1].type] << ") "; 
                ofs << "\n";
                for (int j = 0; j < tokens[i].text.length()+100; ++j) ofs << (j==0||j==tokens[i].text.length()+49?"+":"-");
                ofs << "\n\n";
                return false;
            }
        }
        return true;
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