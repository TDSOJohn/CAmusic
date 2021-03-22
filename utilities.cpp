#include "utilities.hpp"

//  Simple modulo operator function that only returns positive values
unsigned modulo(int value, int m)
{
    int mod = value % m;
    if(mod < 0)
        mod += m;
    return mod;
}


std::vector<int> ca_to_midi_note(std::vector<int> ca_in)
{
    std::vector<int> result;
    std::vector<int> map = {0, 48, 50, 52, 53, 55, 57, 59};

    for(int i = 0; i < ca_in.size(); i++)
        result.push_back(map[ca_in[i]]);

    return result;
}


std::vector<int> ca_to_velocity(std::vector<int> ca_in)
{
    std::vector<int> result;

    for(int i = 0; i < ca_in.size(); i++)
        result.push_back(ca_in[i] * 25);

    return result;
}
