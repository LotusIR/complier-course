#include <string>
#include <map>
#include <vector>
#include <set>

enum parser_status
{
    expr,
    expr_,
    item,
    item_,
    factor,
    st_plus,
    st_times,
    tk_plus,
    tk_minus,
    tk_times,
    tk_slash,
    tk_ident,
    tk_number,
    tk_lparen,
    tk_rparen,
    tk_eof,
    epsilon
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
    period,
    end_of_file
};

struct token
{
    std::string text;
    token_type type;
    token(std::string _text, token_type _type) : text(_text), type(_type) {}
    token() {}
    friend std::ostream & operator << (std::ostream & os,const token & tk) {
        os << tk.type << " " << tk.text;
        return os;
    }
};

class Defination
{
    friend class Parser;
    friend class Lexer;
public:
    std::vector<std::string> ty;
    std::map<std::string, token_type> type_enum;
    std::map<std::string, token_type> type;
    std::map<parser_status, std::map<token_type, std::vector<parser_status> >> predict;
private:
    Defination()
    {
        //token defination
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
              "period",
              "end of file"};
        type_enum = {{"beginsym", beginsym},
                     {"callsym", callsym},
                     {"constsym", constsym},
                     {"dosym", dosym},
                     {"endsym", endsym},
                     {"ifsym", ifsym},
                     {"oddsym", oddsym},
                     {"proceduresym", proceduresym},
                     {"readsym", readsym},
                     {"thensym", thensym},
                     {"varsym", varsym},
                     {"whilesym", whilesym},
                     {"writesym", writesym},
                     {"ident", ident},
                     {"number", number},
                     {"plus", token_type::plus},
                     {"minus", token_type::minus},
                     {"times", times},
                     {"slash", slash},
                     {"eql", eql},
                     {"neq", neq},
                     {"lss", lss},
                     {"leq", leq},
                     {"gtr", gtr},
                     {"geq", geq},
                     {"becomes", becomes},
                     {"lparen", lparen},
                     {"rparen", rparen},
                     {"comma", comma},
                     {"semicolon", semicolon},
                     {"period", period},
                     {"end_of_file",end_of_file}};
        //predict defination

        // predict expr
        predict[expr][token_type::plus] = {expr_,item,tk_plus};
        predict[expr][token_type::minus] = {expr_,item,tk_minus};
        predict[expr][token_type::ident] = {expr_,item};
        predict[expr][token_type::number] = {expr_,item};
        predict[expr][token_type::lparen] = {expr_,item};

        //predict expr_
        predict[expr_][token_type::end_of_file] = {epsilon};
        predict[expr_][token_type::plus] = {expr_,item,st_plus};
        predict[expr_][token_type::minus] = {expr_,item,st_plus};
        predict[expr_][token_type::rparen] = {epsilon};

        //predict item
        predict[item][token_type::ident] = {item_,factor};
        predict[item][token_type::number] = {item_,factor};
        predict[item][token_type::lparen] = {item_,factor};

        //predict item_
        predict[item_][token_type::end_of_file] = {epsilon};
        predict[item_][token_type::plus] = {epsilon};
        predict[item_][token_type::minus] = {epsilon};
        predict[item_][token_type::rparen] = {epsilon};
        predict[item_][token_type::times] = {item_,factor,st_times};
        predict[item_][token_type::slash] = {item_,factor,st_times};

        //predict factor
        predict[factor][token_type::ident] = {tk_ident};
        predict[factor][token_type::number] = {tk_number};
        predict[factor][token_type::lparen] = {tk_rparen,expr,tk_lparen};

        //predict st_plus
        predict[st_plus][token_type::plus] = {tk_plus};
        predict[st_plus][token_type::minus] = {tk_minus};

        //predict st_times
        predict[st_times][token_type::times] = {tk_times};
        predict[st_times][token_type::slash] = {tk_slash};

        // predict[expr][] = {};
    }
};
