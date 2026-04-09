#include "prfunctions.h"

namespace {
constexpr std::size_t MAX_DIGITS = 128;
}

bool addOneBaseB(unsigned int digits[], std::size_t size, unsigned int base) {
	if (size == 0 || base < 2) {
		return false;
	}

	// Add one from right to left and propagate carry.
	for (std::size_t i = size; i > 0; --i) {
		std::size_t idx = i - 1;
		++digits[idx];

		if (digits[idx] < base) {
			return false;
		}

		digits[idx] = 0;
	}

	// Carry left the most significant digit, so the number wrapped around.
	return true;
}

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
