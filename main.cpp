#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>


#include "headers/CA/CA1d.hpp"
#include "headers/CA/TotalisticCA.hpp"

#include "headers/MIDI/MIDIout.hpp"
#include "headers/BMP/BMPgenerator.hpp"

#include "utilities.hpp"


int main()
{
    srand(time(NULL));

    int states              = 5;
    int radius              = 1;
    int rule_size           = states * (radius * 2 + 1);

    int size                = 200;
    int generations         = 300;
    unsigned int scaling    = 15;

    std::vector<int> rule;
    std::vector<int> t0;


    for(int i = 0; i < rule_size; i++)
        rule.push_back(rand()%states);
    rule[0] = 0;

    for(int i = 0; i < size; i++)
        t0.push_back(i / ((size + 1) / states));

    TotalisticCA ca(rule, radius, states);

    BMPgenerator bmp(   size * scaling,
                        generations * scaling,
                        scaling);

    //  Random start
    ca.initialize(size, CA::Start::Random);
    bmp.drawData(ca.getData(), 0);
    for(int i = 1; i < generations; i++)
    {
        ca.generate();
        bmp.drawData(ca.getData(), i);
    }
    bmp.saveImage(ca.str());

    //  Middle start
    bmp.newImage();
    ca.initialize(size, CA::Start::Middle);
    bmp.drawData(ca.getData(), 0);
    for(int i = 1; i < generations; i++)
    {
        ca.generate();
        bmp.drawData(ca.getData(), i);
    }
    bmp.saveImage(ca.str());

    //  Ordered start
    bmp.newImage();
    ca.initialize(t0);
    bmp.drawData(ca.getData(), 0);
    for(int i = 1; i < generations; i++)
    {
        ca.generate();
        bmp.drawData(ca.getData(), i);
    }
    bmp.saveImage(ca.str());
    return 0;
}
