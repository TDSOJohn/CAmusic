#include <iostream>
#include <vector>
#include <algorithm>

#include "include/MIDI/midiToFile.hpp"

//#include "include/Data/DataAnalyzer.hpp"


const int states = 8;

std::vector<int> const_v0;
std::vector<int> const_v1;
std::vector<int> const_v2;
std::vector<int> rand_v0;
std::vector<int> order_v0;
std::vector<int> edge_v0 = {1,1,2,2,3,1,3,3,2,1,2,3,1,1,2,2,3,1,3,3};


int main()
{
    srand(time(NULL));

    const_v0.resize(20, 0);
    const_v1.resize(20, 1);
    const_v2.resize(20, 2);
    for(int i = 0; i < 20; i++)
        rand_v0.push_back(rand()%states);
    for(int i = 0; i < 20; i++)
        order_v0.push_back(i%states);

    for(auto& i : rand_v0)
        std::cout << i << "\t";
    std::cout << "\n";


    MidiToFile mtf;
    mtf.newFile();

    mtf.drawChord(rand_v0, states);
    mtf.saveFile("diocan");

    return 0;
}
