#include "utilities.hpp"

#include <algorithm>

//  Linux version NOT WORKING
#if defined(__LINUX__) || defined(__LINUX) || defined(LINUX)
    #include <math>
#endif

#include <cmath>


std::vector<Pixel> palettes =
{
    {255, 255, 255, 255},
    {255, 0, 0, 255},
    {0, 255, 0, 255},
    {100, 100, 255, 255}
};

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

Pixel inverse(const Pixel& in)
{
    Pixel res;
    res.r = 255 - in.r;
    res.g = 255 - in.g;
    res.b = 255 - in.b;
    return res;
}

std::vector<Pixel> state_to_palette(int states, int palette)
{
    std::vector<Pixel> rgb(states);
    for(int i = 0; i < states; i++)
    {
        rgb[i].r = ((palettes[palette].r / (states - 1)) * i);
        rgb[i].g = ((palettes[palette].g / (states - 1)) * i);
        rgb[i].b = ((palettes[palette].b / (states - 1)) * i);
        rgb[i].a = 255;
    }

    return rgb;
}
