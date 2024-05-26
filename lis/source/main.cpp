#include "../include/lis.h"
#include "../include/tex.h"

int main() {
    LIS<int> lis({2, 1, 0, 4, 5, 1, 2, 3});
    TEX<int> tex;
    tex.MakeTableIR(lis.GetTableIR());
    tex.WriteResult("../result/output_i.txt");
    std::cout << tex.GetResult() << '\n';
    tex.MakeTableCR(lis.GetTableCR());
    tex.WriteResult("../result/output_s.txt");
    std::cout << tex.GetResult() << '\n';
    return 0;
}
