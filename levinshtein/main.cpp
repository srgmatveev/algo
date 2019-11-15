#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>

int get_levenshtein_distance(const std::string &str1, const std::string &str2) {
    std::size_t m = str1.size() + 1;
    std::size_t n = str2.size() + 1;
    int d[m+1][n+1];
    for (auto i = 0; i < m; ++i)
        for (auto j = 0; j < n; ++j)
            d[i][j] = 0;

    for (auto i = 1; i <= m; ++i)
        d[i][0] = i;


    for (auto j = 1; j <= n; ++j)
        d[0][j] = j;
    auto substitutionCost = 0;
    for (auto j = 1; j <= n; ++j) {
        for (auto i = 1; i <= m; ++i) {

            if (str1[i-1] == str2[j-1])
                substitutionCost = 0;
            else
                substitutionCost = 1;
            d[i][j] = std::min({d[i - 1][j] + 1,                   // deletion
                                d[i][j - 1] + 1,                   // insertion
                                d[i - 1][j - 1] + substitutionCost}); // substitution
        }
    }
    return d[m][n];
}

int main(void) {
    std::string str1;
    std::string str2;

    //std::cin >> str1 >> str2;
    str1 = " short";
    str2 = " ports";
    std::cout << get_levenshtein_distance(str1, str2) << std::endl;
}