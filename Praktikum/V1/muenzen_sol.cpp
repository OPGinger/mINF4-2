#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>


int n = 0;
unsigned int count = 0;

void rec_arr(unsigned int *arr, unsigned int pos, unsigned int rest){
    
    if(rest == 0){// last element reached
        // print out array
        for (unsigned int i = 0; i < pos; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";

        count++;

        return;
    }else{

        for (unsigned coin = 1; coin <= rest; ++coin)
        {
            // fill array with remaining values
            arr[pos] = coin;

            // go to next position
            rec_arr(arr, pos+1, rest-coin);
        }

        return;
    }
}

int main(int argc, char** argv){

    // check input parameters
    // n has to be bigger than 0
    while (n <= 0 || n > 64)
    {
        if(argc != 2){
            std::cout << "n [1..64] eingeben: ";
            
            // read in n
            if (!(std::cin >> n)) {
                n = 0;
            }
        }else{
            std::istringstream input_n(argv[1]);

            if (!(input_n >> n) || !input_n.eof()) {
                n = 0;
            }
        }
    }
    
    std::cout << "n: " << n << "\n";

    // get start time
    auto t_start = clock();

    // init vector with ones
    unsigned int v_input[n] = {1};
    // execute recursive variants
    rec_arr(v_input,0,(unsigned int)n);
    
    // get end time
    auto t_end = clock();

    // print out time delta
    std::cout << "Dauer: " << (double)(t_end - t_start) * 1000.0 / (double)CLOCKS_PER_SEC << " ms\n";
    std::cout << "Anzahl der Kombinationen: " << count << "\n";

    return 0;    
}