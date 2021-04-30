#include <bits/stdc++.h>
#include "Lexer.h"
using namespace std;

Lexer lexer;
vector<token> tokens;

int main()
{
    ifstream ifs("in.txt");
    ofstream ofs("out.txt");
    lexer.init();
    string str;
    bool ok = true;
    while (getline(ifs, str))
        ok &= lexer.getTokens(str, tokens);
    if (ok) {
        for (auto &t : tokens)
        {
            ofs << "(" << ty[t.type] << ", " << t.text << ")" << endl;
        }
    }
    else {
        cout << "Analyze failed\n";
    }
    cout << "Cleared\n";
}

/*
do {

}while (next_permutation());
*/

/*
begin、 call、 const、 do、end、
if、 odd、procedure、 read、
then、 var、 while、 write

beginsym, callsym, constsym
dosym, endsym, ifsym, oddsym
proceduresym, readsym, thensym
varsym, whilesym, writesym
    ident,
    number,
    plus,
    minus,
    times,
    slash,
    eql,
    neq,
    lss,
    leq,
    gtr,
    geq,
    becomes,
    lparen,
    rparen,
    comma,
    semicolon,
    period
*/