#include "..\prfunctions.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <istream>

int main(int argc, char** argv){

    std::vector<unsigned int> digits = {};
    std::vector<unsigned int> bases = {};
    unsigned int add = 0;

    // check for valid input
    while (1)
    {
        if(argc < 4){ // not enough command line arguments

            std::cout << "Usage: <start> <add> <base>:";
            
            unsigned int number = 0;

            // read in steps and base from user input
            if (!(std::cin >> number >> add)) {
                number = 0;
                add = 0;
            }

            // read in bases
            unsigned int base = 0;
            while(std::cin >> base) {
                bases.push_back(base);
            }

            // write digits into vector
            digits.clear();
            if (bases.empty()) {
                std::cout << "Invalid input: at least one base is required." << std::endl;
                return 1;
            }

            // count digits of input number
            unsigned int totalDigits = 0;
            unsigned int counter = number;
            do {
                totalDigits++;
                counter /= 10;
            } while (counter > 0);

            // check number of basis and digits match
            if (bases.size() != 1 && bases.size() != totalDigits) {
                std::cout << "Invalid input: number of bases must be either 1 or equal to the number of digits." << std::endl;
                return 1;
            }

            // for start number equal 0
            if (number == 0) {
                if (bases[0] <= 0) {
                    std::cout << "Invalid input: digit 0 is not valid for base " << bases[0] << std::endl;
                    return 1;
                }
                digits.push_back(0);
            } else { // for start numbers > 0
                unsigned int temp = number;
                unsigned int posFromRight = 0;

                while (temp > 0) {
                    unsigned int digit = temp % 10;
                    unsigned int digitIndex = totalDigits - 1 - posFromRight;
                    unsigned int currentBase = (bases.size() == 1) ? bases[0] : bases[digitIndex];

                    if (digit >= currentBase) {
                        std::cout << "Invalid input: digit " << digit << " is not valid for base " << currentBase << std::endl;
                        return 1;
                    }

                    digits.insert(digits.begin(), digit);
                    temp /= 10;
                    posFromRight++;
                }
            }

            

        }else{ // read in from command line arguments
            std::istringstream input_steps(argv[1]);
            std::istringstream input_base(argv[2]);

            if (!(input_steps >> steps) || !input_steps.eof()) {
                steps = 0;
            }

            if (!(input_base >> base) || !input_base.eof()) {
                base = 0;
            }
        }
    }

    if(argc < 3)
    {
        std::cout << "Usage: <base> <add> [numbers...]\n";
        return 1;
    }else{ // read in from command line arguments
            std::istringstream input_steps(argv[1]);
            std::istringstream input_base(argv[2]);

            if (!(input_steps >> steps) || !input_steps.eof()) {
                steps = 0;
            }

            if (!(input_base >> base) || !input_base.eof()) {
                base = 0;
            }
        }

    if(bases.size() != 1 && bases.size() != digits.size()) {
        std::cout << "Invalid input: number of bases must be either 1 or equal to the number of digits." << std::endl;
        return 1;
    }

    for (std::size_t i = 0; i < digits.size(); i++) {
        unsigned int currentBase = (bases.size() == 1) ? bases[0] : bases[i];
        if (digits[i] >= currentBase) {
            std::cout << "Invalid input: digit " << digits[i] << " is not valid for base " << currentBase << std::endl;
            return 1;
        }
    }

    std::cout << "Input: ";
    for (unsigned int digit : digits) {
        std::cout << digit << " ";
    }
    std::cout << std::endl;

    bool carry = false;
    for (int i = 0; i < add; i++)
    {
        auto result = addOneBaseB(digits, bases[i % bases.size()]);
        digits = result.first;
        carry = result.second;

        if(carry){
            result = addOneBaseB(digits, bases[(i + 1) % bases.size()]);
            digits = result.first;
            carry = result.second;
        }

        std::cout << "+1 --> ";
        for (unsigned int digit : digits) {
            std::cout << digit << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}