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
    int rule_size           = states * (radius * 2 + 1);

    int size                = 200;
    int generations         = 150;
    unsigned int scaling    = 15;

    std::vector<int> rule;


    for(int i = 0; i < rule_size; i++)
        rule.push_back(rand()%states);

    rule[0] = 0;

    TotalisticCA    ca(rule, radius, states);

    BMPgenerator bmp(   size * scaling,
                        generations * scaling,
                        scaling);

    ca.initialize(size, CA::Start::Random);

    bmp.drawData(ca.getData(), 0);
    for(int i = 1; i < generations; i++)
    {
        ca.generate();
        bmp.drawData(ca.getData(), i);
    }
    bmp.saveImage(ca.str());

    bmp.newImage();

    ca.initialize(size, CA::Start::Middle);

    bmp.drawData(ca.getData(), 0);
    for(int i = 1; i < generations; i++)
    {
        ca.generate();
        bmp.drawData(ca.getData(), i);
    }
    bmp.saveImage(ca.str());

    return 0;
}
