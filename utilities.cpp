#include "utilities.hpp"



void printstr(const std::string &str)
{
    for(char ch : str)
        addch (ch);
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


unsigned modulo(int value, int m)
{
    int mod = value % m;
    if(mod < 0)
        mod += m;
    return mod;
}

std::vector<int> decimalToBaseN(const int n)
{

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
