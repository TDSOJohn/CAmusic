#include <iostream>

#include "utilities.hpp"

#include <algorithm>

//  Linux version NOT WORKING
#if defined(__LINUX__) || defined(__LINUX) || defined(LINUX)
    #include <math>
#endif

#include "Utility.hpp"
#include <cmath>


std::vector<eng::Pixel> palettes =
{
    {255, 255, 255, 255},
    {91, 182, 193, 255},
    {206, 153, 105},
    {40, 230, 30, 255},
    {100, 100, 255, 255},
};


std::vector<int> decimalToBaseN(const long long int n, const int base)
{
    long long int temp_n(n);
    int mod = 0;
    std::vector<int> result;

    while(temp_n >= base)
    {
        mod = eng::modulo(temp_n, base);
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

std::vector<int> ca_to_velocity(std::vector<int> ca_in, int max_val)
{
    std::vector<int> result;
    int step = 127 / max_val;

    for(auto& i: ca_in)
        result.push_back(i * step);

    return result;
}

std::vector<eng::Pixel> state_to_rgb(int states, eng::Pixel target)
{
    std::vector<eng::Pixel> rgb(states);
    for(int i = 0; i < states; i++)
    {
        rgb[i].r = ((target.r / (states - 1)) * i);
        rgb[i].g = ((target.g / (states - 1)) * i);
        rgb[i].b = ((target.b / (states - 1)) * i);
    }

    return rgb;
}

CA1d::Start rotateStart(CA1d::Start s)
{
    switch(s)
    {
        case CA1d::Random:
            return CA1d::Middle;
        case CA1d::Middle:
            return CA1d::Left;
        case CA1d::Left:
            return CA1d::Other;
        case CA1d::Other:
            return CA1d::Random;
    }
}
