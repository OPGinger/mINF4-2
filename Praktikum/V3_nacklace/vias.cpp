#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>

void printPartition(const std::vector<int>& blockIds, int n) {

    // define colors for blocks
    static const char* colors[] = {
        "\033[1;31m", // red
        "\033[1;32m", // green
        "\033[1;33m", // yellow
        "\033[1;34m", // blue
        "\033[1;35m", // magenta
        "\033[1;36m", // cyan
        "\033[1;37m", // white
        "\033[1;95m", // bright magenta
        "\033[1;96m", // bright cyan
        "\033[1;93m"  // bright yellow
    };
    const char* resetColor = "\033[0m";

    // determine the number of blocks
    int blockCount = 0;
    for (int i = 0; i < n; ++i) {
        blockCount = std::max(blockCount, blockIds[i] + 1);
    }
 
    // print block IDs with colors
    for (int i = 0; i < n; ++i) {
        int blockId = blockIds[i];

        const char* color = colors[blockId % (sizeof(colors)/sizeof(colors[0]))];
        std::cout << color << "O" << resetColor;

        if (i + 1 < n) std::cout << " ";
    }

    // group contacts by block
    std::vector<std::vector<int>> blocks(blockCount);
    for (int i = 0; i < n; ++i) {
        blocks[blockIds[i]].push_back(i + 1);
    }

    // print block contents
    std::cout << "  ";
    for (int b = 0; b < blockCount; ++b) {
        if (b > 0)
            std::cout << " ";

        std::cout << "[";

        for (size_t j = 0; j < blocks[b].size(); ++j) {
            if (j > 0) std::cout << ",";
            std::cout << blocks[b][j];
        }
        
        std::cout << "]";
    }
    std::cout << "\n";
}

unsigned int generatePartitions(unsigned int n, int elementIndex, int partitionCount) {
    
    //counter for the number of variants
    static unsigned int variantsCount = 0;

    // block ID of contacts
    static std::vector<int> blockIds(n, 0);

    // all contacts have been assigned to blocks
    if (elementIndex == (int)blockIds.size()) {
        std::cout << std::setw(4) << ++variantsCount << " (partitions: "<< partitionCount << "): ";
        printPartition(blockIds, blockIds.size());

        return 0;
    }

    // try to put the current contact in one of the existing blocks
    for (int block = 0; block < partitionCount; block++) {
        blockIds[elementIndex] = block;

        // move on to the next contact
        generatePartitions(n, elementIndex + 1, partitionCount);
    }

    // try to put the current contact in a new block
    blockIds[elementIndex] = partitionCount; // assign to new block 

    // move on to the next contact and increase partition count
    generatePartitions(n, elementIndex + 1, partitionCount + 1);

    return variantsCount;
}

int main(int argc, char* argv[]) {
    int n = 0;

    { // validate command line arguments
        // if no command line arguments, exit
        if (argc != 2) {
            std::cout << "Usage: kontakt_varianten <number_of_contacts>\n";
            return 1;
        }

        // try to parse the number of contacts
        try {
            n = std::stoi(argv[1]);
        } catch (...) {
            std::cout << "Bitte eine ganze Zahl als Anzahl Kontakte angeben.\n";
            return 1;
        }

        // validate the number of contacts
        if (n < 1) {
            std::cout << "Die Anzahl der Kontakte muss mindestens 1 sein.\n";
            return 1;
        }

        // warn if the number of contacts is large
        if (n > 10) {
            std::cout << "Warnung: Bei mehr als 10 Kontakten steigt die Anzahl der Verbindungsvarianten sehr schnell.\n";
        }
    }

    std::cout << generatePartitions(n, 0, 0);
    std::cout << " Verbindungsvarianten bei " << n << " Kontakten:\n";

    return 0;
}
