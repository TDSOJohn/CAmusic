#include "utilities_gmp.hpp"

#include <algorithm>

#include "utilities.hpp"



std::string baseNtoDecimalGMP(std::vector<int> n, const int base_in)
{
    //  New mpz integer
    mpz_t temp;
    mpz_init(temp);
    mpz_t decimal;
    mpz_init(decimal);

    for(int i = 0; i < n.size(); i++)
    {
        if(n[i] < base_in)
        {
            mpz_ui_pow_ui(temp, base_in, (n.size() - (i+1)));
            mpz_mul_si(temp, temp, n[i]);
            mpz_add(decimal, decimal, temp);
        } else
        {
            return "";
        }
    }
    //  create char* to convert from mpz integer
    char* bigInt = NULL;
    bigInt = mpz_get_str(bigInt, 10, decimal);
    std::string result(bigInt);
    return result;
}
