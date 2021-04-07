#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>


#include "include/CA/CA1dgen.hpp"
#include "include/CA/CA1dtot.hpp"

#include "include/MIDI/MIDIout.hpp"
#include "include/MIDI/midiToFile.hpp"
#include "include/BMP/BMPgenerator.hpp"

#include "utilities.hpp"


int states              = 6;
int radius              = 3;
int rule_size           = states * (radius * 2 + 1);

int size                = 210;
int generations         = 70;
unsigned int scaling    = 15;

CA1dtot* newCAtot(CA1dtot* ca_p)
{

    std::vector<int> rule;
    std::vector<int> t0;

    for(int i = 0; i < rule_size; i++)
        rule.push_back(rand()%states);
//  rule[0] = 0;

    for(int i = 0; i < size; i++)
        t0.push_back(i / (size / (states - 1)));

    if(ca_p != NULL)
        delete ca_p;
    ca_p = new CA1dtot(rule, radius, states);
    ca_p->initialize(size, CA1d::Start::Random);
    return ca_p;
}


int main()
{
    char command = 'n';

    srand(time(NULL));

    CA1dtot*         ca = NULL;

    BMPgenerator    bmp(    size * scaling,
                            generations * scaling,
                            scaling);

    MidiToFile      mtf1;

    while(command == 'n')
    {
        bmp.newImage();
        mtf1.newSheet();
        ca = newCAtot(ca);

        ca->print();
        mtf1.drawData(ca->getData(), 1);
        bmp.drawData(ca->getData(), 0);
        for(int i = 1; i < generations; i++)
        {
            ca->generate();
            ca->print();
            mtf1.drawData(ca->getData(), 1);
            bmp.drawData(ca->getData(), i);
        }
        std::cin >> command;
    }

    mtf1.saveFile(ca->str());
    bmp.saveImage(ca->str());

    return 0;
}
