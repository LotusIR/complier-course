#include <fstream>
#include "Defination.h"
#include <string>
#include <vector>
namespace utils
{
    void err_unex_symbol(std::ofstream & ofs,std::string &text,std::string &s,int line,int & it)
    {
        ofs << "\n";
        for (int i = 0; i < s.length() + 50; ++i)
            ofs << (i == 0 || i == s.length() + 49 ? "+" : "-");
        ofs << "\n\n";
        ofs << "Fatal error in:\n\t"
            << "line " << line << ": \"" << s << "\"\n";
        ofs << "Error type:\n\t";
        ofs << "Undefined symbol -> " << text << " ("
            << "line:" << line << ":" << it - text.length() << ") \n";
        ofs << "\n";
        for (int i = 0; i < s.length() + 50; ++i)
            ofs << (i == 0 || i == s.length() + 49 ? "+" : "-");
        ofs << "\n\n";
    }

    void err_unex_token(std::ofstream &ofs, std::vector<token> &tokens, int i, Defination &def)
    {
        ofs << "\n";
        for (int j = 0; j < tokens[i].text.length() + 100; ++j)
            ofs << (j == 0 || j == tokens[i].text.length() + 100 ? "+" : "-");
        ofs << "\n\n";
        ofs << "Fatal error in:\n\t";
        ofs << "Error type:\n\t";
        ofs << "Unexpected token -> " << tokens[i].text << " (token_type: " << def.ty[tokens[i].type] << ") ";
        if (i == 0)
            ofs << "at the beginning";
        else
            ofs << "after token: " << tokens[i - 1].text << " (token_type: " << def.ty[tokens[i - 1].type] << ") ";
        ofs << "\n\n";
        for (int j = 0; j < tokens[i].text.length() + 100; ++j)
            ofs << (j == 0 || j == tokens[i].text.length() + 100 ? "+" : "-");
        ofs << "\n\n";
    }

    void err_unex_end()
    {
    }
}
