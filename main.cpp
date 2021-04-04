#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>


#include "include/CA/CA1d.hpp"
#include "include/CA/TotalisticCA.hpp"

#include "include/MIDI/MIDIout.hpp"
#include "include/MIDI/midiToFile.hpp"
#include "include/BMP/BMPgenerator.hpp"

#include "utilities.hpp"


int main()
{
    srand(time(NULL));

    int states              = 5;
    int radius              = 1;
    int rule_size           = states * (radius * 2 + 1);

    int size                = 30;
    int generations         = 40;
    unsigned int scaling    = 15;

    std::vector<int> rule;
    std::vector<int> t0;


    for(int i = 0; i < rule_size; i++)
        rule.push_back(rand()%states);
    rule[0] = 0;

    TotalisticCA ca(rule, radius, states);

    BMPgenerator bmp(   size * scaling,
                        generations * scaling,
                        scaling);

    MidiToFile   mtf1;

    for(int i = 0; i < size; i++)
        t0.push_back(i / ((size + 1) / states));

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
    mtf1.drawData(ca.getData());
    bmp.drawData(ca.getData(), 0);
    for(int i = 1; i < generations; i++)
    {
        ca.generate();
        mtf1.drawData(ca.getData());
        bmp.drawData(ca.getData(), i);
    }
    mtf1.saveFile("results/midi1");
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
