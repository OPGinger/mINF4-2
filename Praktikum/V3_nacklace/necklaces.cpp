#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "..\prfunctions.h"
#include <bitset>

int main(int argc, char** argv) {

    unsigned int beed_count = 0;

    { // check valid command line arguments input
        if(argc != 2){
            std::cout << "Usage: <number_of_beads>\n";
            return 1;
        }

        std::istringstream input_beeds(argv[1]);
        if (!(input_beeds >> beed_count) || !input_beeds.eof() || beed_count <= 0) {
            std::cout << "Invalid input: number of beads must be an integer.\n";
            return 1;
        }
    }

    std::cout << "Number of beads: " << beed_count << std::endl;

    std::vector<unsigned int> necklaces{};
    for(unsigned int new_necklace = 0; new_necklace < (1U << beed_count); new_necklace++) {
        bool is_unique = true;

        // first necklace is always unique
        if(necklaces.size() == 0) {
            necklaces.push_back(new_necklace);
            continue;
        }

        // compare new necklace with all existing necklaces
        for(unsigned int existing_necklace : necklaces) {

            // check if pattern already exists
            unsigned int rotate_necklace = existing_necklace;
            for(unsigned int d = 1; d < beed_count; d++){

                // rotate existing necklace
                rotate_necklace = rotateLeft(existing_necklace, d, beed_count);

                // not unique if new necklace is a rotation of an existing one
                if(rotate_necklace == new_necklace){
                    is_unique = false;
                    break;
                }
            }
        }

        // add new necklace if it is unique
        if(is_unique) {
            necklaces.push_back(new_necklace);
        }
    }

    std::cout << "Unique necklaces: " << necklaces.size() << std::endl;
    
    // print out necklaces
    for(unsigned int necklace : necklaces) {
        std::string bits = std::bitset<16>(necklace).to_string().substr(16-beed_count);
        std::cout << "-";
        for(char c : bits) {
            if(c == '0') {
                std::cout << "\033[1;91mO\033[0m";
            } else {
                std::cout << "\033[1;32mO\033[0m";
            }
            std::cout << "-";
        }
        std::cout << std::endl;
    }

    return 0;
}