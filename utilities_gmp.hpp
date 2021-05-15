#ifndef utilities_gmp_hpp
#define utilities_gmp_hpp

#include <vector>
#include <string>

#include <gmp.h>



/// Simple base n vector to decimal int string converter
std::string baseNtoDecimalGMP(std::vector<int> n, const int base);


#endif //utilities_gmp_hpp
