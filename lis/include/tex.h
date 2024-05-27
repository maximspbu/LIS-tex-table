#ifndef TEX_H
#define TEX_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <tuple>
#include <format>

template<class T>
class TEX{
public:
    TEX(){

    }

    void MakeIntermediateTable(const std::vector<std::tuple<std::vector<T>, std::vector<size_t>, std::vector<int>>>& table){
        /**
         * @brief       create tex code string
         * 
         * @param table     table of intermediate results
         * 
         * @return 
        */
        std::string s;
        size_t a = 0;
        while (a < table.size()){
            s += "|c ";
            ++a;
        }
        result_ = std::string("\\begin{center}\n") + std::string("\\begin{tabular} {|>{\\columncolor{pink}}c ") + s + std::string("| }\n");
        result_ += std::string("\\cline{2-") + std::format("{}", table.size() + 1) + std::string("}\n");
        result_ += "\\rowcolor{gray!50} \\multicolumn{ 0}{ c|}{\\cellcolor{white}{}} ";
        for (size_t i = 0; i < table.size(); ++i){
            result_ += std::format("& {}", i);
        }
        result_ += "\\\\\\hline\n";
        size_t count = 0;
        for (auto& i: table){
            result_ += std::format("$ a[{}] $", count);
            for (auto& k: std::get<(0)>(i)){
                result_ += std::format(" & ${}$", k);
            }
            result_ += "\\\\\\hline\n";
            result_ += std::format("$ d[{}] $", count);
            for (auto& k: std::get<(1)>(i)){
                result_ += std::format(" & ${}$", k);
            }
            result_ += "\\\\\\hline\n";
            result_ += std::format("$ p[{}] $", count);
            for (auto& k: std::get<(2)>(i)){
                result_ += std::format(" & ${}$", k);
            }
            result_ += "\\\\\\hline\n";
            ++count;
        }
        result_ += "\\end{tabular}\n\\end{center}\n";
    }

    void MakeSolutionTable(const std::vector<std::tuple<size_t, T, int>>& table){
        /**
         * @brief       create tex code string
         * 
         * @param table     table of result
         * 
         * @return 
        */
        std::string s;
        size_t a = 0;
        while (a < 3){
            if (a == 1){
                s+= ">{\\columncolor{pink}}c| ";
            } else {
                s += "c |";
            }
            ++a;
        }
        result_ = std::string("\\begin{center}\n") + std::string("\\begin{tabular} {| ") + s + std::string("}\n") + std::string("\\hline\n");
        result_ += "\\rowcolor{gray!50} ";
        result_ += "$j$ & $a[j]$ & $p[j]$";
        result_ += "\\\\\\hline\n";
        std::string st;
        for (auto& i: table){
            std::apply([this, &st](auto&&... args){((st += std::format("${}$ & ", args)), ...);}, i);
            st = st.substr(0, st.size() - 3);
            result_ += st;
            result_ += "\\\\\\hline\n";
            st.clear();
        }
        result_ += "\\end{tabular}\n\\end{center}\n";
    }

    std::string GetResult(){
        /**
         * @brief returns tex code string
         * 
        */
        return result_;
    }

    void WriteResult(const std::string filename_){
        /**
         * @brief write string to the file
         * 
         * @param filename_
         *
        */
        std::ofstream os{filename_};
        if (!os.is_open()){
            std::cout << "Cannot to write!\n";
            return;
        }
        os << result_;
    }

private:
    const std::string filename_;
    std::string result_;
};

#endif // TEX_H
