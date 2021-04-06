#include "utilities.hpp"

//  Simple modulo operator function that only returns positive values
unsigned modulo(int value, int m)
{
    int mod = value % m;
    if(mod < 0)
        mod += m;
    return mod;
}

//  Simple function that maps 0-8 ints to (note off) and C major scale
//  Octave is calculated from C0 (int octave = 3 ==> map[1] = C3)
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

//  Simple function that maps 0-5 ints to 0-125 velocity
std::vector<int> ca_to_velocity(std::vector<int> ca_in)
{
    std::vector<int> result;

    for(int i = 0; i < ca_in.size(); i++)
        result.push_back(ca_in[i] * 25);

    return result;
}
