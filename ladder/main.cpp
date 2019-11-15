#include <iostream>
#include <vector>
#include <algorithm>

int ladder(const std::vector<int> &w) {
    std::size_t n = w.size();
    if (n == 0) return 0;
    if (n == 1) return w[0];
    if (n == 2) return std::max(w[0] + w[1], w[1]);
    std::vector<int> result;
    result.emplace_back(w[0]);
    result.emplace_back(std::max(w[0] + w[1], w[1]));
    for (auto i = 2; i < n; ++i)
        result.emplace_back(std::max({result[i - 1] + w[i], result[i - 2] + w[i]}));
    return result[n-1];
}

int main() {
    std::size_t n;
    std::vector<int> w;
   // std::cin >> n;
    /*int val;
    for(auto i=0; i<n; ++i) {
        std::cin >> val;
        w.emplace_back(val);
    }*/
    n = 8;
    w = {3, 4, 10,10, 0, -6, -10, 0};
    std::cout << ladder(w) << std::endl;
    return 0;
}