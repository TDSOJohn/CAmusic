#include "utilities.hpp"

#include <algorithm>

//  Linux version NOT WORKING
#if defined(__LINUX__) || defined(__LINUX) || defined(LINUX)
    #include <math>
#endif

#include <cmath>


//===================== NEEDS NCURSES =====================//
#if __has_include(<curses.h>)
    void printstr(const std::string &str)
    {
        for(char ch : str)
            addch(ch);
    }


    void mvprintstr(const int y, const int x, const std::string &str)
    {
        unsigned int temp_x = x;
        for(char ch : str)
        {
            mvaddch(y, temp_x, ch);
            temp_x++;
        }
    }


    void printvec(std::vector<int> const& v_in)
    {
        for(int i : v_in)
            printw("%d|", i);
    }


    void mvprintvec(const int y, const int x, std::vector<int> const& v_in)
    {
        unsigned int temp_x = x;
        mvprintw(y, x, "");
        for(int i : v_in)
        {
            mvprintw(y, temp_x, "|%d", i);
            temp_x += 4;
        }
    }
#endif
//===================== END =====================//



//===================== NEEDS GMP =====================//
#if __has_include(<gmp.h>)
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
#endif
//===================== END =====================//



unsigned modulo(int value, int m)
{
    int mod = value % m;
    if(mod < 0)
        mod += m;
    return mod;
}


std::vector<int> decimalToBaseN(const long long int n, const int base)
{
    long long int temp_n(n);
    int mod = 0;
    std::vector<int> result;

    while(temp_n >= base)
    {
        mod = modulo(temp_n, base);
        result.push_back(mod);
        temp_n -= mod;
        temp_n /= base;
    }
    result.push_back(temp_n);
    std::reverse(result.begin(), result.end());
    return result;
}


long long int baseNtoDecimal(std::vector<int> const& n, const int base)
{
    long long int result = 0;
    for(int i = 0; i < n.size(); i++)
        result += pow(base, n.size() - (i+1)) * n[i];
    return result;
}


std::vector<int> ca_to_midi_note(std::vector<int> data_in, int octave)
{
    std::vector<int> result;
    std::vector<int> map = {0, 24, 26, 28, 29, 31, 33, 35};

    for(auto& i : map)
    {
        if(i != 0)
            i += (12 * octave);
    }

    for(int i = 0; i < data_in.size(); i++)
        result.push_back(map[data_in[i]]);

    return result;
}


std::vector<int> ca_to_velocity(std::vector<int> ca_in)
{
    std::vector<int> result;

    for(int i = 0; i < ca_in.size(); i++)
        result.push_back(ca_in[i] * 25);

    return result;
}
