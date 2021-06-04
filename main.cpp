#include <bits/stdc++.h>
#include "Compiler.h"

int main() {
    freopen("in_AST_result.txt","w",stdout);
    AstNode * root = Compiler::compile("in.txt");
    if (root) {
        utils::print_sepline(std::cout,80);
        std::cout << "AstTree:\n";
        root->print();
        utils::print_sepline(std::cout,80);
        std::cout << "Calculation result:\n";
        std::cout << root->calc() << '\n';
        std::vector<std::string> res;
        res = qgen(root);
        utils::print_sepline(std::cout,80);
        std::cout << "Quards:\n";
        for (auto &str:res) {
            cout << str << '\n';
        }
        utils::print_sepline(std::cout,80);
    }
}