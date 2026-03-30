#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>


int n = 0;

std::vector<int> *recursive_vector(std::vector<int> *last_in){
    
    if((*last_in).size() == 1){
        // return last vector when only one element is left
        return last_in;
    }else{
        // calculate next vector
        (*last_in)[(*last_in).size() - 2] = (*last_in).at((*last_in).size() - 2) +1; // increment second to last element
        int last = (*last_in).back(); // get last element value
        (*last_in).pop_back(); // remove last element
        (*last_in).insert((*last_in).end(), last-1, 1); // add last-1 ones to end of vector

        // print out vector
        for (int m : (*last_in)) {
            std::cout << m << " ";
        }
        std::cout << "\n";

        // get next vector
        return recursive_vector(last_in);
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
    std::vector<int> v_input(n, 1);
    // execute recursive variants
    std::vector<int> *v_result = recursive_vector(&v_input);
    
    // get end time
    auto t_end = clock();

    int count = (*v_result).size();

    /* for variant with matrix
    for (std::vector<int> m : v_result) {
        static int pos = 0;
        std::cout << std::setw(std::to_string(count - 1).size()) << pos++ << ": "; // print right aligned index

        for (int x : m) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Es gibt " << v_result.size() << " Möglichkeiten für n=" << n << "!\n";*/
    std::cout << "Dauer: " << (double)(t_end - t_start) * 1000.0 / (double)CLOCKS_PER_SEC << " ms\n";

    return 0;    
}