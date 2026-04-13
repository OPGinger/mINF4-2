#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>

// Composition & Partition

#define LOGGGING false

int n = 0;
unsigned int count = 0;

void composition(unsigned int *arr, unsigned int pos, unsigned int rest){
    
    if(rest == 0){// last element reached

        #if LOGGGING
            // print out array
            for (unsigned int i = 0; i < pos; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << "\n";
        #endif

        count++;

        return;
    }else{

        for (unsigned coin = 1; coin <= rest; coin++)
        {
            // fill array with remaining values
            arr[pos] = coin;

            // go to next position
            composition(arr, pos+1, rest-coin);
        }

        return;
    }
}

void partition(unsigned int *arr, unsigned int pos, unsigned int rest, unsigned int last){
    
    if(rest == 0){// last element reached

        #if LOGGGING
            // print out array
            for (unsigned int i = 0; i < pos; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << "\n";
        #endif

        count++;

        return;
    }else{

        for (unsigned coin = 1; coin <= rest && coin <= last; coin++)
        {
            // fill array with remaining values
            arr[pos] = coin;

            // go to next position
            partition(arr, pos+1, rest-coin, coin);
        }

        return;
    }
}

int main(int argc, char** argv){

    // check input parameters
    // n has to be bigger than 0
    while (n <= 0)
    {
        if(argc < 2){
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

    // execute recursive variant
    if(argc <= 2 || strcmp(argv[2], "composition") == 0){
        composition(v_input,0,(unsigned int)n);
    }else if(strcmp(argv[2], "partition") == 0){
        partition(v_input,0,(unsigned int)n,(unsigned int)n);
    }  
    
    // get end time
    auto t_end = clock();

    // print out time delta
    std::cout << "Dauer: " << (double)(t_end - t_start) * 1000.0 / (double)CLOCKS_PER_SEC << " ms\n";
    std::cout << "Anzahl der Kombinationen: " << count << "\n";

    return 0;    
}