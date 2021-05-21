#include <fstream>
#include "Defination.h"
#include <string>
#include <vector>
namespace utils
{

    void print_sepline(std::ofstream &ofs, int len) {
        ofs << "\n";
        for (int i = 0; i < len; ++i)
            ofs << (i == 0 || i == len-1 ? "+" : "-");
        ofs << "\n\n";
    }

    void err_unex_symbol(std::ofstream & ofs,std::string &text,std::string &s,int line,int & it)
    {
        print_sepline(ofs,s.length() + 50);
        ofs << "Fatal error in:\n\t"
            << "line " << line << ": \"" << s << "\"\n";
        ofs << "Error type:\n\t";
        ofs << "Undefined symbol -> " << text << " ("
            << "line:" << line << ":" << it - text.length() << ") \n";
        print_sepline(ofs,s.length()+50);
    }

    void err_unex_token(std::ofstream &ofs, std::vector<token> &tokens, int i, Defination &def,const std::string & expt = "")
    {
        print_sepline(ofs,tokens[i].text.length() + 100);
        ofs << "Fatal error:\n\t";
        ofs << "Error type:\n\t";
        ofs << "Unexpected token -> " << tokens[i].text << " (token_type: " << def.ty[tokens[i].type] << ") ";
        if (i == 0)
            ofs << "at the beginning";
        else
            ofs << "after token: " << tokens[i - 1].text << " (token_type: " << def.ty[tokens[i - 1].type] << ") \n";
        if (expt != "") ofs << "\tExpected token -> " << expt << '\n';
        print_sepline(ofs,tokens[i].text.length() + 100);
    }

    void err_unex_end(std::ofstream &ofs, std::vector<token> &tokens, Defination &def) {
        print_sepline(ofs,tokens.back().text.length()+100);
        ofs << "Fatal error:\n\t";
        ofs << "Error type:\n\t";
        ofs << "Unexpected endding -> " << tokens.back().text << " (token_type: " << def.ty[tokens.back().type] << ") \n";
        print_sepline(ofs,tokens.back().text.length()+100);

    } 
}
