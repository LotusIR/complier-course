#include <bits/stdc++.h>
#include "Compiler.h"

int main() {
    AstNode * root = Compiler::compile("in.txt");
    if (root) {
        std::cout << root->calc() << '\n';
    }
}