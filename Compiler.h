#include <memory>
#include <string>
#include "ParserAst.cpp"
#include <iostream>

class Compiler{
public:
    static AstNode * compile(std::string input_file) {
        if (!Lexer::analyze(input_file)) {
            std::cout << "Lexer analyze failed\n";
            return nullptr;
        }
        else std::cout << "Lexer analyze success\n";
        RecursiveDecsentParser parser;
        AstNode *root = parser.parse(Lexer::getTokens());
        if (!root) {
            std::cout << "Parser analyze failed\n";
            return nullptr;
        }
        else std::cout << "Parser analyze success\n";
        return root;
    }
};