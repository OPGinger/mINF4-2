
#include <stdio.h>
#include <bitset>
#include <iostream>
#include <iomanip>

/* own implementation */
unsigned long long find_next_fib(unsigned long long n) {
    
    unsigned long long a = n | n >> 1;

    unsigned long long b = a + 1;

    unsigned long long f = n & ~(a ^ b) | ((a ^ ~0ULL) & b);

    return f;
}

/* given solution */
unsigned long long find_next_fib_fast(unsigned long long x) {
    unsigned long long y = ~(x>>1);
    x -= y;
    x &= y;
    return x;
}

int main(int argc, char* argv[]) {

    unsigned long long start_word = 0b1000001UL;
    unsigned long long word = start_word;

    for(unsigned int i = 0; i < 10; i++) {
        std::cout << std::setw(4) << i << std::setw(15) << "binary word: " << std::bitset<64>(word) << std::endl;
        word = find_next_fib_fast(word);
    }
    return 0;
}