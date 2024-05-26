#ifndef LIS_H
#define LIS_H

#include <vector>
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <string>

template<class T>
class LIS{
public:
    LIS(std::vector<T> a): aSize_(a.size()), a_(std::move(a)){
        p_.resize(aSize_);
        d_.resize(aSize_);
        resultTable_.resize(aSize_);
        std::vector<size_t> j_i;
        size_t indMaxValue = 0;
        T minValue = *std::min_element(begin(a_), end(a_));
        T forIndMaxValue = minValue;
        size_t maxValue = 0;
        for (size_t i = 0; i < aSize_; ++i){
            for (size_t j = 0; j < i; ++j){
                if (a_[j] < a_[i]){
                    j_i.push_back(j);
                    if (a_[j] >= forIndMaxValue){
                        indMaxValue = j;
                        forIndMaxValue = a_[j];
                    }
                    maxValue = std::max(maxValue, d_[j]);
                }
            }
            if (j_i.empty()){   
                d_[i] = 1;
                p_[i] = -1;
            } else {   
                d_[i] = maxValue + 1;
                p_[i] = indMaxValue;
            }
            j_i.clear();
            indMaxValue = 0;
            maxValue = 0;
            forIndMaxValue = minValue;
            resultTable_[i] = {a_, d_, p_};
        }
        int MLIS = *std::max_element(begin(d_), end(d_));
        
        std::vector<int> o;
        solutionTable_.resize(MLIS);
        for (int i = d_.size() - 1; i >= 0; --i){
            if (d_[i] == MLIS){
                o.push_back(i);
                solutionTable_[0] = {i, a_[i], p_[i]};
                break;
            }
        }
        int u;
        
        for (int i = 0; i < MLIS - 1; ++i){
            u = p_[o.back()];
            o.push_back(u);
            solutionTable_[i+1] = {o.back(), a_[o.back()], u};
        }
        std::reverse(o.begin(), o.end());
        for (auto& o_i: o){
            std::cout << o_i << '\n';
        }
        std::cout << '\n';
        for (auto& i: resultTable_){
            for (auto& k: std::get<(0)>(i)){
                std::cout << k << ' ';
            }
            std::cout << '\n';
            for (auto& k: std::get<(1)>(i)){
                std::cout << k << ' ';
            }
            std::cout << '\n';
            for (auto& k: std::get<(2)>(i)){
                std::cout << k << ' ';
            }
            std::cout << '\n';
        }
    }

    void LCS(const std::vector<T>& input){

    }

    void LCIS(){

    }

    std::vector<std::tuple<std::vector<T>, std::vector<size_t>, std::vector<int>>> GetTableIR(){
        return resultTable_;
    }

    std::vector<std::tuple<size_t, T, int>> GetTableCR(){
        return solutionTable_;
    }

private:
    size_t aSize_;
    size_t dSize_;
    size_t pSize_;
    std::vector<T> a_;
    std::vector<size_t> d_;
    std::vector<int> p_;
    std::vector<std::tuple<std::vector<T>, std::vector<size_t>, std::vector<int>>> resultTable_;
    std::vector<std::tuple<size_t, T, int>> solutionTable_;
};

#endif // LIS_H
