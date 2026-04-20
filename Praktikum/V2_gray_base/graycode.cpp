#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>

#include "../prfunctions.h"

int main(int argc, char** argv){
    int steps = 0;
    int base = 0;

    while (steps <= 0 || base < 2)
    {
        if(argc != 3){ // no command line arguments

            std::cout << "Usage: <steps> <base>:";
            
            // read in steps and base from user input
            if (!(std::cin >> steps >> base)) {
                steps = 0;
                base = 0;
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

    std::cout << "Steps: " << steps << ", Base: " << base << std::endl;

    // create vector with the right number of digits
    std::vector<int> grayCode(ceil(log(steps) / log(base)),0);

    for(int i = 0; i <= steps; i++) {

        std::cout << "Step " << std::setw(ceil(log(steps) / log(10))) << i << ": ";

        // print out digits
        for (unsigned int i = 0; i < grayCode.size(); i++) {
            std::cout << grayCode[i] << " ";
        }

        // add one to the gray code
        grayCode = addOneGrayBaseB(grayCode, base);

        std::cout << std::endl;
    }

    return 0;
}
