#ifndef TEX_H
#define TEX_H

#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <tuple>
#include <format>

template<class T>
class TEX{
public:
    TEX(const std::string& filename): filename_(filename){

    }

    void MakeTable(const std::vector<std::tuple<std::vector<T>, std::vector<size_t>, std::vector<int>>>& table){
        std::string s;
        size_t a = 0;
        while (a < table.size()){
            s += "|c ";
            ++a;
        }
        result_ = std::string("\\begin{center}\n") + std::string("\\begin{tabular} {| c| ") + s + std::string("| }\n") + std::string("\\hline\n");
        result_ += "$ $ \\rowcolor{Gray} ";
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

    std::string GetResult(){
        return result_;
    }

    void WriteResult(){
        std::ostream os;
    }

private:
    const std::string filename_;
    std::string result_;
};

#endif // TEX_H
