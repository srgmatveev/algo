#include <iostream>
#include <vector>

long knapsack(const std::vector<std::size_t> &p, const std::vector<std::size_t> &w, std::size_t W, std::size_t n) {
    long size = 0;
    std::size_t **D = new std::size_t *[n + 1];
    for (auto i = 0; i < n + 1; ++i)
        D[i] = new std::size_t[W + 1];

    for (auto i = 0; i <= n ; ++i)
        D[i][0] = 0;
    for (auto j = 0; j <= W; ++j)
        D[0][j] = 0;

    for(auto i=1;i<=n;++i)
        for (auto j = 1; j <= W; ++j) {
            if (w[i - 1] <= j) {
                D[i][j] = std::max(D[i - 1][j], p[i - 1] + D[i - 1][j - w[i - 1]]);
            } else {
                D[i][j] = D[i - 1][j];
            }
        }

    size=D[n][W];

    for (auto i = 0; i < n + 1; ++i)
        if (D[i]) delete[] D[i];
    if (D) delete[]D;

    return size;
}

int main() {
    std::size_t W, n;
    //W = 10;
    //n = 3;
    std::cin>>W>>n;

    std::vector<std::size_t> w(n);
   // w = {1, 4, 8};
    for(auto i=0;i<n;++i)
    {
        std::cin>>w[i];
    }
   std::cout << knapsack(w, w, W, n) << std::endl;

    return 0;
}