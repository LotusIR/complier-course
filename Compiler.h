#include <memory>
#include <string>
#include "Grammer.h"
#include <iostream>

class Compiler{
public:
    static bool compile(std::string input_file) {
        if (!Lexer::analyze(input_file)) {
            std::cout << "Lexer analyze failed\n";
            return false;
        }
        else std::cout << "Lexer analyze success\n";
        if (!Grammer::analyze(input_file)) {
            std::cout << "Grammer analyze failed\n";
            return false;
        }
        else std::cout << "Grammer analyze success\n";
        return true;
    }
};