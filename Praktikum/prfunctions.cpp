#include "prfunctions.h"
#include <iostream>
#include <cstdint>

/*
 * Returns a mask for a given width.
 */
unsigned maskForWidth(unsigned width) {
    return width >= 32 ? 0xFFFFFFFFu : ((1u << width) - 1u);
}

/*
 * Rotates a value to the left by a given shift amount within a specified width.
 */
unsigned rotateLeft(unsigned value, unsigned shift, unsigned width) {
    width &= 31;

    if (width == 0)
		return value;

    shift %= width;

    unsigned mask = maskForWidth(width);

    value &= mask;

    return ((value << shift) | (value >> (width - shift))) & mask;
}

/*
 * Rotates a value to the right by a given shift amount within a specified width.
 */
unsigned rotateRight(unsigned value, unsigned shift, unsigned width) {
    width &= 31;

    if (width == 0)
		return value;

    shift %= width;

    unsigned mask = maskForWidth(width);

    value &= mask;
	
    return ((value >> shift) | (value << (width - shift))) & mask;
}

/*
 * Adds one to a number represented in a given base.
 */
std::pair<unsigned int, bool> addOneBaseB( unsigned int number, unsigned int base) {
	
	// check valid input
	if (base < 2) {
		return {number, false}; // return unchanged
	}
	
		number ++; // add one

		if (number < base) {
			return {number, false}; // return if no carry is needed
		}

		number = 0; // set digit to zero and carry to next digit

	return {number, true};
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