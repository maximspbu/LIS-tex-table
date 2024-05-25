#include "../include/lis.h"
#include "../include/tex.h"

int main() {
    LIS<int> lis({2, 1, 0, 4, 5, 1, 2, 3});
    TEX<int> tex("../result/output.txt");
    tex.MakeTable(lis.GetTable());
    tex.WriteResult();
    std::cout << tex.GetResult() << '\n';
    return 0;
}
