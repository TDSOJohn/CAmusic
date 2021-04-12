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



int states              = 2;
int radius              = 2;
int rule_size_tot       = (states - 1) * (radius * 2 + 1);
int rule_size_gen       = pow(states, (radius * 2 + 1));

int size                = 700;
int generations         = 2000;
unsigned int scaling    = 1;

CA1dgen* newCAgen(CA1dgen* ca_p)
{
    std::vector<int> rule = {0,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};
    std::vector<int> t0;

    if(ca_p != NULL)
    {
        delete ca_p;
        ca_p = NULL;
    }
    ca_p = new CA1dgen(radius, states);
    ca_p->initialize(size, CA1d::Start::Random);
    return ca_p;
}

CA1dtot* newCAtot(CA1dtot* ca_p)
{
    std::vector<int> rule = {0,0,1,0,1};
    std::vector<int> t0;

    if(ca_p != NULL)
    {
        delete ca_p;
        ca_p = NULL;
    }
    ca_p = new CA1dtot(radius, states, rule);
    ca_p->initialize(size, CA1d::Start::Random);
    return ca_p;
}


int main()
{
    char command = 'n';

    srand(time(NULL));

    CA1dgen*         ca = NULL;

    BMPgenerator    bmp(    size * scaling,
                            generations * scaling,
                            scaling);

    MidiToFile      mtf1;

    while(command != 'q')
    {
        switch(command)
        {
            case 'n':
                bmp.newImage();
        //        mtf1.newSheet();
                ca = newCAgen(ca);
        //        mtf1.drawData(ca->getData(), 1);
//                std::cout << *ca << std::endl;
                bmp.drawData(ca->getData(), 0);
                for(int i = 1; i < generations; i++)
                {
                    ca->generate();
//                    std::cout << *ca << std::endl;
        //            mtf1.drawData(ca->getData(), 1);
                    bmp.drawData(ca->getData(), i);
                }
            break;

            case 's':
//                mtf1.saveFile(ca->str());
                bmp.saveImage(ca->str());
                break;

            default:
                break;
        }
        std::cout << "q to quit, s to save, n to generate new: \t";
        std::cin >> command;
    }

    return 0;
}
