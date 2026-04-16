#pragma once

#include <cstddef>
#include <vector>

std::pair<unsigned int, bool> addOneBaseB( unsigned int number, unsigned int base);
//bool addOneGrayBaseN(unsigned int grayDigits[], std::size_t size, unsigned int base);
std::vector<int> addOneGrayBaseB(std::vector<int> digits, int base);
