#include "..\prfunctions.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <istream>
#include <string>

int main(int argc, char** argv){

    std::vector<unsigned int> digits = {};
    std::vector<unsigned int> bases = {};
    unsigned int add = 0;

    // check valid command line arguments input
    {
        if(argc != 4){
            std::cout << "Usage: <digit>:<digit>:... <add> <base>[:<base>:...]\n";
            std::cout << "  <digit> positive integers\n";
            std::cout << "  <add> positive integer\n";
            std::cout << "  <base> positive integers >= 2\n";

            return 1;
        }

        // Parse digits from command line
        {
            std::string digits_str = argv[1];
            std::string token;

            size_t pos = 0;
            while ((pos = digits_str.find(':')) != std::string::npos) {
                // get token from string
                token = digits_str.substr(0, pos);
                std::istringstream iss_token(token);

                // read in digit
                unsigned int digit;
                if (!(iss_token >> digit)) {
                    std::cout << "Invalid input: digits must be positive integers.\n";
                    return 1;
                }

                // add digit to vector
                digits.push_back(digit);

                // remove last token from string
                digits_str.erase(0, pos + 1);
            }

            // Last token (last digit)
            std::istringstream iss_last(digits_str);
            unsigned int digit;
            if (!(iss_last >> digit)) {
                std::cout << "Invalid input: digits must be positive integers.\n";
                return 1;
            }
            digits.push_back(digit);
    }

        // Parse number to add from command line
        std::istringstream iss_add(argv[2]);
        if (!(iss_add >> add)) {
            std::cout << "Invalid input: add must be a positive integer.\n";
            return 1;
        }

        // Parse bases from command line
        {
            std::string bases_str = argv[3];
            std::string token;

            size_t pos = 0;
            while ((pos = bases_str.find(':')) != std::string::npos) {
                // get token from string
                token = bases_str.substr(0, pos);
                std::istringstream iss_base(token);

                unsigned int base;
                if (!(iss_base >> base) || base < 2) {
                    std::cout << "Invalid input: bases must be integers >= 2.\n";
                    return 1;
                }

                bases.push_back(base);

                bases_str.erase(0, pos + 1);
            }

            // Last token
            std::istringstream iss_base_last(bases_str);
            unsigned int base;
            if (!(iss_base_last >> base) || base < 2) {
                std::cout << "Invalid input: bases must be integers >= 2.\n";
                return 1;
            }
            bases.push_back(base);

            // Validate bases count
            if (bases.size() != 1 && bases.size() != digits.size()) {
                std::cout << "Invalid input: number of bases must be either 1 or equal to the number of digits.\n";
                return 1;
            }
        }

        // Validate digits against bases
        for (size_t i = 0; i < digits.size(); ++i) {
            unsigned int currentBase = (bases.size() == 1) ? bases[0] : bases[i];
            if (digits[i] >= currentBase) {
                std::cout << "Invalid input: digit " << digits[i] << " is not valid for base " << currentBase << ".\n";
                return 1;
            }
        }
    }

    std::cout << "Input: ";
    for (unsigned int digit : digits) {
        std::cout << digit << " ";
    }
    std::cout << std::endl;

    // add numbers one by one
    for (int i = 0; i < add; i++)
    {
        bool carry = false;
        int digit_index = digits.size() - 1;
        // add with carry
        do{
            unsigned int currentBase = (bases.size() == 1) ? bases[0] : bases[digit_index];
            unsigned int currentDigit = digits[digit_index];

            auto result = addOneBaseB(currentDigit, currentBase);
            digits[digit_index] = result.first;
            carry = result.second;

            digit_index--;
        }while(carry && digit_index >= 0);

        // output result afer adding
        std::cout << "+1 --> ";
        for (unsigned int digit : digits) {
            std::cout << digit << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}