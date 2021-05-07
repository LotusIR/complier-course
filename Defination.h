#include <string>
#include <map>

enum grammer_status {
    expr,item,factor
};

enum token_type
{
    beginsym,
    callsym,
    constsym,
    dosym,
    endsym,
    ifsym,
    oddsym,
    proceduresym,
    readsym,
    thensym,
    varsym,
    whilesym,
    writesym,
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
};

class Defination
{
private:
    friend class Lexer;
    friend class Grammer;
    std::vector<std::string> ty;

    std::map<std::string, token_type> type_enum;
    std::map<std::string, token_type> type;
    std::map< grammer_status,std::map<token_type,grammer_status> > predict;

    Defination()
    {
        type["begin"] = beginsym;
        type["call"] = callsym;
        type["const"] = constsym;
        type["do"] = dosym;
        type["end"] = endsym;
        type["if"] = ifsym;
        type["odd"] = oddsym;
        type["procedure"] = proceduresym;
        type["read"] = readsym;
        type["then"] = thensym;
        type["var"] = varsym;
        type["while"] = whilesym;
        type["write"] = writesym;
        type["+"] = token_type::plus;
        type["-"] = token_type::minus;
        type["*"] = times;
        type["/"] = slash;
        type["="] = eql;
        type["#"] = neq;
        type["<"] = lss;
        type["<="] = leq;
        type[">"] = gtr;
        type[">="] = geq;
        type[":="] = becomes;
        type["("] = lparen;
        type[")"] = rparen;
        type[","] = comma;
        type[";"] = semicolon;
        type["."] = period;
        ty = {"beginsym",
              "callsym",
              "constsym",
              "dosym",
              "endsym",
              "ifsym",
              "oddsym",
              "proceduresym",
              "readsym",
              "thensym",
              "varsym",
              "whilesym",
              "writesym",
              "ident",
              "number",
              "plus",
              "minus",
              "times",
              "slash",
              "eql",
              "neq",
              "lss",
              "leq",
              "gtr",
              "geq",
              "becomes",
              "lparen",
              "rparen",
              "comma",
              "semicolon",
              "period"};
        type_enum = {{"beginsym",beginsym},
              {"callsym",callsym},
              {"constsym",constsym},
              {"dosym",dosym},
              {"endsym",endsym},
              {"ifsym",ifsym},
              {"oddsym",oddsym},
              {"proceduresym",proceduresym},
              {"readsym",readsym},
              {"thensym",thensym},
              {"varsym",varsym},
              {"whilesym",whilesym},
              {"writesym",writesym},
              {"ident",ident},
              {"number",number},
              {"plus",token_type::plus},
              {"minus",token_type::minus},
              {"times",times},
              {"slash",slash},
              {"eql",eql},
              {"neq",neq},
              {"lss",lss},
              {"leq",leq},
              {"gtr",gtr},
              {"geq",geq},
              {"becomes",becomes},
              {"lparen",lparen},
              {"rparen",rparen},
              {"comma",comma},
              {"semicolon",semicolon},
              {"period",period}};
    }
};
