#include "..\prfunctions.h"
#include <iostream>

int main(int argc, char** argv){

    if(argc < 3)
    {
        std::cout << "Usage: <base> <add> [numbers...]\n";
        return 1;
    }

    std::vector<unsigned int> digits = {1, 2, 3};
    unsigned int base = 5;
    unsigned int add = 25;

    std::cout << "Input: ";
    for (unsigned int digit : digits) {
        std::cout << digit << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < add; i++)
    {
        digits = addOneBaseB(digits, base);

        std::cout << "+1 --> ";
        for (unsigned int digit : digits) {
            std::cout << digit << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}