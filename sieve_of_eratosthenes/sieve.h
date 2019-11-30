//
// Created by sergio on 30.11.2019.
//

#pragma once

#include <vector>

class Sieve {

private:
    int n;
    std::vector<bool> prime;

public:
    Sieve(const int &n) : n(n) {
        this->prime.resize(n + 1, true);
    }

    void erathosthen() {
        prime[0] = prime[1] = false;
        if (n < 2) return;
        for (auto i = 2; i * 1ll * i <= n; ++i)
            if (prime[i] and prime[i] % 2 != 0)
                if (i * 1ll * i <= n)
                    for (auto j = i * i; j <= n; j += i)
                        prime[j] = false;
    }

    friend std::ostream &operator<<(std::ostream &out, const Sieve &sieve) {

        for (auto i = 0; i <= sieve.n; ++i)
            if (sieve.prime[i]) {
                (i == 2) ? out << "" : out << ", ";
                out << i;
            }
        return out;
    }
};
