#include "prfunctions.h"
#include <iostream>

/*
 * Adds one to a number represented in a given base.
 */
std::pair<std::vector<unsigned int>, bool> addOneBaseB(std::vector<unsigned int> digits, unsigned int base) {
	
	// check valid input
	if (digits.empty() || base < 2) {
		return {digits, false}; // return unchanged
	}
	
	// Add one from the right
	for (int i = digits.size()-1; i >= 0; --i) {

		digits[i] ++; // add one

		if (digits[i] < base) {
			return {digits, false}; // return if no carry is needed
		}

		digits[i] = 0; // set digit to zero and carry to next digit
	}

	digits.insert(digits.begin(), 1); // add new most significant digit if overflow occurs

	return {digits, true};
}

/*
 * Adds one to a number represented in a given base.
 */
std::vector<int> addOneGrayBaseB(std::vector<int> digits, int base) {
	if (base < 2) {
		return {};
	}

	if (digits.empty()) {
		return {0};
	}

	// Move the last digit first.
	// Direction of position i depends on the parity of all digits left of i:
	// even sum -> up, odd sum -> down.
	std::vector<int> prefixParity(digits.size(), 0);
	int parity = 0;
	for (std::size_t i = 0; i < digits.size(); ++i) {
		prefixParity[i] = parity;
		parity = (parity + (digits[i] & 1)) & 1;
	}

	// If a digit hits a boundary, it stays there and the carry propagates left.
	for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
		const int direction = (prefixParity[static_cast<std::size_t>(i)] == 0) ? 1 : -1;
		const int next = digits[i] + direction;

		if (next >= 0 && next < base) {
			digits[i] = next;
			return digits;
		}

		// Boundary reached: keep current digit and continue with left neighbor.
		digits[i] = (direction > 0) ? (base - 1) : 0;
	}

	// Full overflow -> wrap around to 0...0 for fixed-length Gray code.
	for (std::size_t i = 0; i < digits.size(); ++i) {
		digits[i] = 0;
	}

	return digits;
}