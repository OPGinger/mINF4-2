#include "prfunctions.h"

/*
 * Adds one to a number represented in a given base.
 */
std::vector<unsigned int> addOneBaseB(std::vector<unsigned int> digits, unsigned int base) {
	
	// check valid input
	if (digits.empty() || base < 2) {
		return digits; // return unchanged
	}
	
	// Add one from the right
	for (std::size_t i = digits.size()-1; i >= 0; --i) {

		digits[i] ++; // add one

		if (digits[i] < base) {
			return digits; // return if no carry is needed
		}

		digits[i] = 0; // set digit to zero and carry to next digit
	}

	digits.insert(digits.begin(), 1); // add new most significant digit if overflow occurs

	return digits;
}


std::vector<unsigned int> addOneGrayBaseN(std::vector<unsigned int> digits, unsigned int base) {
	
	// check valid input
	if (digits.empty() || base < 2) {
		return digits; // return unchanged
	}

	return digits; // return unchanged

}
/*
bool addOneGrayBaseN(unsigned int grayDigits[], std::size_t size, unsigned int base) {
	if (size == 0 || base < 2 || size > MAX_DIGITS) {
		return false;
	}

	unsigned int valueDigits[MAX_DIGITS];

	// Decode reflected n-ary Gray digits to standard base-n digits.
	valueDigits[0] = grayDigits[0];
	unsigned int prefixSum = valueDigits[0];
	for (std::size_t i = 1; i < size; ++i) {
		if ((prefixSum % 2U) == 0U) {
			valueDigits[i] = grayDigits[i];
		} else {
			valueDigits[i] = (base - 1U) - grayDigits[i];
		}
		prefixSum += valueDigits[i];
	}

	// Increment the decoded value in base n.
	bool overflow = true;
	for (std::size_t i = size; i > 0; --i) {
		std::size_t idx = i - 1;
		++valueDigits[idx];

		if (valueDigits[idx] < base) {
			overflow = false;
			break;
		}

		valueDigits[idx] = 0;
	}

	// Encode the incremented value back to reflected n-ary Gray digits.
	grayDigits[0] = valueDigits[0];
	prefixSum = valueDigits[0];
	for (std::size_t i = 1; i < size; ++i) {
		if ((prefixSum % 2U) == 0U) {
			grayDigits[i] = valueDigits[i];
		} else {
			grayDigits[i] = (base - 1U) - valueDigits[i];
		}
		prefixSum += valueDigits[i];
	}

	return overflow;
}
*/