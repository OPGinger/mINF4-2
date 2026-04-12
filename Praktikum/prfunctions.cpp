#include "prfunctions.h"
#include <iostream>

/*
 * Adds one to a number represented in a given base.
 */
std::vector<unsigned int> addOneBaseB(std::vector<unsigned int> digits, unsigned int base) {
	
	// check valid input
	if (digits.empty() || base < 2) {
		return digits; // return unchanged
	}
	
	// Add one from the right
	for (int i = digits.size()-1; i >= 0; --i) {

		digits[i] ++; // add one

		if (digits[i] < base) {
			return digits; // return if no carry is needed
		}

		digits[i] = 0; // set digit to zero and carry to next digit
	}

	digits.insert(digits.begin(), 1); // add new most significant digit if overflow occurs

	return digits;
}

/*
 * Adds one to a number represented in a given base.
 */
std::vector<int> addOneGrayBaseB(std::vector<int> digits, unsigned int base) {
	{ // check valid inputs

		// check base > 2
		if (base < 2) {
			return digits; // return unchanged
		}

		// if digits is empty, add a zero to start with
		if(digits.empty()) {
			digits.insert(digits.begin(), 0);
			return digits;
		}
	}
	
	// Add one from the right
	for (int i = digits.size()-1; i >= 0; i--) {

		if(i > 0 && digits[i-1] % 2)
		{ // previous digit is odd
			digits[i]--; // subtract one
		}else
		{ // previous digit is even or 0
			digits[i]++; // add one
		}

		if (digits[i] < base && digits[i] >= 0) {
			break; // return, no carry needed
		}
		
		if(digits[i] >= base){
			digits[i] = base-1;
		}

		if(digits[i] < 0){
			digits[i] = 0;
		}
	}

	return digits;
}

/*
std::vector<unsigned int> addOneGrayBaseB(std::vector<unsigned int> digits, unsigned int base) {
	
	// check valid input
	if (digits.empty() || base < 2) {
		return digits; // return unchanged
	}

	if(digits.back() == base - 1) {
		digits[digits.size() - 2]++;
	}

	if(digits.size() == 1 || digits[digits.size() - 2] % 2 == 0) {
		digits.back()++;
	}else{
		digits.back()--;
	}


	return digits; // return unchanged

}*/