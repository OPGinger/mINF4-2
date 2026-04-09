#include <iostream>
#include <cstddef>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include <climits>

#include "../prfunctions.h"

constexpr std::size_t MAX_DIGITS = 128;

bool hasValidDigits(const unsigned int digits[], std::size_t size, unsigned int base) {
	if (base < 2) {
		return false;
	}

	for (std::size_t i = 0; i < size; ++i) {
		unsigned int digit = digits[i];
		if (digit >= base) {
			return false;
		}
	}

	return true;
}

void printDigits(const unsigned int digits[], std::size_t size) {
	std::cout << "[ ";
	for (std::size_t i = 0; i < size; ++i) {
		std::cout << digits[i] << " ";
	}
	std::cout << "]";
}

bool parseUnsignedArg(const char* text, unsigned int& value) {
	if (text == nullptr || *text == '\0') {
		return false;
	}

	errno = 0;
	char* endPtr = nullptr;
	unsigned long parsed = std::strtoul(text, &endPtr, 10);

	if (errno == ERANGE || endPtr == text || *endPtr != '\0' || parsed > UINT_MAX) {
		return false;
	}

	value = static_cast<unsigned int>(parsed);
	return true;
}

int main(int argc, char* argv[]) {
	unsigned int base = 0;
	unsigned int iterations = 0;
	unsigned int digits[MAX_DIGITS];
	std::size_t digitCount = 0;

	if (argc < 4) {
		std::cerr << "Verwendung: " << argv[0] << " <Basis> <Iterationen> <Ziffer0> [Ziffer1] ... [ZifferN]\n";
		return 1;
	}

	if (!parseUnsignedArg(argv[1], base) || !parseUnsignedArg(argv[2], iterations)) {
		std::cerr << "Fehler: Basis und Iterationen muessen gueltige nicht-negative Ganzzahlen sein.\n";
		return 1;
	}

	for (int i = 3; i < argc; ++i) {
		unsigned int value = 0;
		if (!parseUnsignedArg(argv[i], value)) {
			std::cerr << "Fehler: Ungueltige Ziffer an Position " << (i - 3) << ".\n";
			return 1;
		}

		if (digitCount >= MAX_DIGITS) {
			std::cerr << "Fehler: Zu viele Ziffern. Maximal " << MAX_DIGITS << " erlaubt.\n";
			return 1;
		}

		digits[digitCount] = value;
		++digitCount;
	}

	if (digitCount == 0) {
		std::cerr << "Fehler: Das Ziffernarray darf nicht leer sein.\n";
		return 1;
	}

	if (!hasValidDigits(digits, digitCount, base)) {
		std::cerr << "Fehler: Ungueltige Eingabe. Basis muss >= 2 sein und alle Ziffern < Basis.\n";
		return 1;
	}

	std::cout << "Basis B = " << base << "\n";
	std::cout << "Startwert: ";
	printDigits(digits, digitCount);
	std::cout << "\n\n";

	for (unsigned int step = 1; step <= iterations; ++step) {

		bool overflow = addOneBaseB(digits, digitCount, base);
		

		std::cout << "Schritt " << std::setw(4) << step << ": ";
		printDigits(digits, digitCount);
		if (overflow) {
			std::cout << "  (Wrap-around)";
		}
		std::cout << "\n";
	}

	return 0;
}
