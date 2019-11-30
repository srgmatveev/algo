#include <iostream>
#include <memory>
#include "sieve.h"
int main() {
    std::unique_ptr<Sieve> shieve = std::make_unique<Sieve>(1000);
    shieve->erathosthen();
    std::cout << *shieve << std::endl;
    return 0;
}
