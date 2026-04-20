#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

void generateSchemes(int n, int position, int usedLetters, string& current, vector<string>& result) {
	
    // all positions filled
    if (position == n) {
		result.push_back(current);
		return;
	}

    // try assign an existing or new letter
	for (int letterIndex = 0; letterIndex <= usedLetters; letterIndex++) {
		current[position] = (char)('A' + letterIndex);
		int newUsedLetters = usedLetters;

        // using a new letter, increase count of used letters
		if (letterIndex == usedLetters) {
            newUsedLetters++;
        }

		generateSchemes(n, position + 1, newUsedLetters, current, result);
	}
}

int main(int argc, char* argv[]) {

    int n = 0;
    {// validate command line input
        // check command line arguments
        if (argc != 2) {
            std::cout << "Verwendung: " << argv[0] << " <N>\n";
            return 1;
        }

        n = atoi(argv[1]);

        if (n <= 0) {
            std::cout << "Bitte eine positive ganze Zahl als Argument angeben.\n";
            return 1;
        }

        if (n > 26) {
            std::cout << "Maximal 26 Satze werden unterstutzt (A-Z).\n";
            return 1;
        }
    }

	vector<string> schemes;
	string current(n, 'A');

    auto start = clock();

	generateSchemes(n, 0, 0, current, schemes);

    auto end = clock();

    // print results
    /*
	std::cout << "\nReimschemata, N = " << n << ":\n";
	for (int i = 0; i < (int)schemes.size(); ++i) {
		std::cout << std::setw(4) << i + 1 << ": " << schemes[i] << '\n';
	}
        */
    
    // calculate and print elapsed time
    double elapsedSeconds = double(end - start);
    std::cout << "Dauer: " << elapsedSeconds << " Millisekunden.\n";

	std::cout << "Anzahl: " << schemes.size() << '\n';
	return 0;
}
