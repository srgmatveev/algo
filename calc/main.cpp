#include <iostream>
#include <vector>
#include <cmath>

enum oper_enum {
    x, x_plus_1, x_mul_2, x_mul_3
};
struct cell {
    std::size_t prev;
    oper_enum op;
    std::size_t steps;
};

std::size_t oper(std::size_t i, u_short operat) {
    switch (operat) {
        case oper_enum::x:
            return i;
            break;
        case oper_enum::x_plus_1:
            return i + 1;
            break;
        case oper_enum::x_mul_2:
            return i * 2;
            break;
        case oper_enum::x_mul_3:
            return i * 3;
            break;
        default:
            return 0;
            break;
    }
}

void patch_cell(std::vector<cell> &cells, std::size_t k, std::size_t n, std::size_t i, oper_enum op) {
    if (k > n) return;
    if (cells.at(k).prev == 0) {
        cells.at(k).prev = i;
        cells.at(k).op = op;
        cells.at(k).steps = cells.at(i).steps +1;
    } else {
        if (cells.at(k).steps > cells.at(i).steps ) {
            cells.at(k).prev = i;
            cells.at(k).op = op;
            cells.at(k).steps = cells.at(i).steps +1;
        }

    }
}

void calc(std::size_t n) {
    std::vector<cell> cells(n + 1);
    std::size_t k;
    if (n==0){
        std::cout<<0<<std::endl;
        std::cout<<1<<std::endl;
        return;
    }
    for (auto i = 1; i <= n; ++i) {
        k = oper(i, oper_enum::x_mul_3);
        patch_cell(cells, k, n, i, oper_enum::x_mul_3);
        k = oper(i, oper_enum::x_mul_2);
        patch_cell(cells, k, n, i, oper_enum::x_mul_2);
        k = oper(i, oper_enum::x_plus_1);
        patch_cell(cells, k, n, i, oper_enum::x_plus_1);


    }

    std::vector<std::size_t> S{};

    if (n>0) S.emplace_back(n);
    for (auto i = n; i > 1;) {
        S.emplace_back(cells[i].prev);
        i = cells[i].prev;
    }

    std::cout<<S.size()-1<<std::endl;

    for(auto i=0; i<S.size();++i){
        std::cout<<S[S.size()-1-i]<<" ";
    }
    std::cout<<std::endl;
}



int main() {
    std::size_t n;
    n = 0;
    calc(n);
    return 0;
}