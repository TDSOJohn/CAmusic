#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>


#include "headers/CA/CA1d.hpp"
#include "headers/CA/TotalisticCA.hpp"

//#include "headers/MIDI/MIDIout.hpp"
#include "headers/BMP/BMPgenerator.hpp"

#include "utilities.hpp"


int main()
{
    srand(time(NULL));

    int states              = 5;
    int radius              = 1;
    int rule1_size          = pow(states, (radius * 2 + 1));
    int rule2_size          = states * (radius * 2 + 1);

    int size                = 200;
    int generations         = 150;
    unsigned int scaling    = 15;

    std::vector<int> rule1;
    std::vector<int> rule2;


    for(int i = 0; i < rule1_size; i++)
        rule1.push_back(rand()%states);

    for(int i = 0; i < rule2_size; i++)
        rule2.push_back(rand()%states);

    rule1[0] = 0;
    rule2[0] = 1;

    CA1d            ca1(rule1, radius, states);
    TotalisticCA    ca2(rule2, radius, states);

    BMPgenerator bmp1(  size * scaling,
                        generations * scaling,
                        scaling);
    BMPgenerator bmp2(  size * scaling,
                        generations * scaling,
                        scaling);

    ca2.initialize(size, CA::Start::Random);

    bmp1.drawData(ca2.getData(), 0);
    for(int i = 1; i < generations; i++)
    {
        ca2.generate();
        bmp1.drawData(ca2.getData(), i);
    }
    bmp1.saveImage(ca2.str());

    ca2.initialize(size, CA::Start::Middle);

    bmp2.drawData(ca2.getData(), 0);
    for(int i = 1; i < generations; i++)
    {
        ca2.generate();
        bmp2.drawData(ca2.getData(), i);
    }
    bmp2.saveImage(ca2.str());

    return 0;
}
