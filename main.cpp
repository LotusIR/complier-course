#include <bits/stdc++.h>
#include "Compiler.h"

int main() {
    freopen("in_AST_result.txt","w",stdout);
    AstNode * root = Compiler::compile("in.txt");
    if (root) {
        root->print();
        std::cout << root->calc() << '\n';
    }
    root->print();
    std::vector<std::string> res;
    int tot = 0;
    root->gen(res,tot);
    for (auto& str:res) {
        std::cout << str << std::endl;
    }
}