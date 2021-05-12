#include <memory>
#include <string>
#include "Parser.h"
#include <iostream>

class Compiler{
public:
    static bool compile(std::string input_file) {
        if (!Lexer::analyze(input_file)) {
            std::cout << "Lexer analyze failed\n";
            return false;
        }
        else std::cout << "Lexer analyze success\n";
        if (!Parser::analyze(input_file)) {
            std::cout << "Parser analyze failed\n";
            return false;
        }
        else std::cout << "Parser analyze success\n";
        return true;
    }
};