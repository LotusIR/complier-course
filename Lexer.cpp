#include <bits/stdc++.h>
#include "Lexer.h"
using namespace std;

Lexer lexer;
vector<token> tokens;

int main()
{
    ifstream ifs("in.txt");
    ofstream ofs("out.txt");
    if (lexer.run(ifs,ofs)) cout << "Cleared!\n";
    else cout << "Error!\n";
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