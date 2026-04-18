#include <iostream>
#include <vector>
#include <sstream>
#include <string>

void printPartition(const std::vector<int>& blockIds, int n) {
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
    const char* reset = "\033[0m";

    int blockCount = 0;
    for (int i = 0; i < n; ++i) {
        blockCount = std::max(blockCount, blockIds[i] + 1);
    }

    for (int i = 0; i < n; ++i) {
        int blockId = blockIds[i];
        const char* color = colors[blockId % (sizeof(colors)/sizeof(colors[0]))];
        std::cout << color << "O" << reset;
        if (i + 1 < n) std::cout << " ";
    }

    std::vector<std::vector<int>> blocks(blockCount);
    for (int i = 0; i < n; ++i) {
        blocks[blockIds[i]].push_back(i + 1);
    }

    std::cout << "  ";
    for (int b = 0; b < blockCount; ++b) {
        if (b > 0) std::cout << " ";
        std::cout << "{";
        for (size_t j = 0; j < blocks[b].size(); ++j) {
            if (j > 0) std::cout << ",";
            std::cout << blocks[b][j];
        }
        std::cout << "}";
    }
    std::cout << "\n";
}

void generatePartitions(int index, int n, int usedBlocks, std::vector<int>& blockIds, unsigned long long& count) {
    if (index == n) {
        printPartition(blockIds, n);
        count ++;
        return;
    }

    for (int block = 0; block < usedBlocks; ++block) {
        blockIds[index] = block;
        generatePartitions(index + 1, n, usedBlocks, blockIds, count);
    }

    blockIds[index] = usedBlocks;
    generatePartitions(index + 1, n, usedBlocks + 1, blockIds, count);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: kontakt_varianten <number_of_contacts>\n";
        return 1;
    }

    int n = 0;
    try {
        n = std::stoi(argv[1]);
    } catch (...) {
        std::cout << "Bitte eine ganze Zahl als Anzahl Kontakte angeben.\n";
        return 1;
    }

    if (n < 1) {
        std::cout << "Die Anzahl der Kontakte muss mindestens 1 sein.\n";
        return 1;
    }

    if (n > 10) {
        std::cout << "Warnung: Bei mehr als 10 Kontakten steigt die Anzahl der Verbindungsvarianten sehr schnell.\n";
    }

    std::vector<int> blockIds(n, 0);
    unsigned long long count = 0;

    generatePartitions(0, n, 0, blockIds, count);

    std::cout << count << " Verbindungsvarianten bei " << n << " Kontakte:\n";

    return 0;
}
