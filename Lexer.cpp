#include <bits/stdc++.h>
#include "Lexer.h"
using namespace std;
int main()
{
    if (Lexer::analyze("in.txt")) cout << "Cleared!\n";
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