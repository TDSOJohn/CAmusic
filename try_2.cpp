#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>
#include <bitset>


#include "include/CA/CA1dgen.hpp"
#include "include/CA/CA1dtot.hpp"

#include "include/MIDI/MIDIout.hpp"
#include "include/MIDI/midiToFile.hpp"
#include "include/BMP/BMPgenerator.hpp"

#include "utilities.hpp"



const int states        = 2;
const int radius        = 2;
const int rule_size_tot = (states - 1) * (radius * 2 + 1) + 1;
const int rule_size_gen = pow(states, (radius * 2 + 1));

const int size          = 140;
const int generations   = 70;
const int scaling       = 1;

std::bitset<rule_size_tot> ruleBits{0};
unsigned int dec_rule   = rand()%((int)pow(2, rule_size_tot));


CA1dgen* newCAgen(CA1dgen* ca_p)
{
    std::vector<int> rule;
    std::vector<int> t0;

    ruleBits = dec_rule;
    std::cout << "\n\n\t" << dec_rule << "\t" << ruleBits << "\n\n";

    for(int i = 0; i < rule_size_gen; i++)
        rule.push_back(ruleBits[i]);

    if(ca_p != NULL)
    {
        delete ca_p;
        ca_p = NULL;
    }
    ca_p = new CA1dgen(radius, states, rule);
    ca_p->initialize(size, CA1d::Start::Middle);

    dec_rule++;

    return ca_p;
}

CA1dtot* newCAtot(CA1dtot* ca_p)
{
    std::vector<int> rule;
    std::vector<int> t0;

    ruleBits = dec_rule;
    std::cout << "\n\n\t" << dec_rule << "\t" << ruleBits << "\n\n";

    for(int i = 0; i < rule_size_tot; i++)
        rule.push_back(ruleBits[i]);


    if(ca_p != NULL)
    {
        delete ca_p;
        ca_p = NULL;
    }
    ca_p = new CA1dtot(radius, states, rule);
    ca_p->initialize(size, CA1d::Start::Middle);

    dec_rule++;

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

    while(command != 'q')
    {
        switch(command)
        {
            case 'n':
                bmp.newImage();
        //        mtf1.newSheet();
                ca = newCAtot(ca);
        //        mtf1.drawData(ca->getData(), 1);
                std::cout << *ca << std::endl;
                bmp.drawData(ca->getData(), 0);
                for(int i = 1; i < generations; i++)
                {
                    ca->generate();
                    std::cout << *ca << std::endl;
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
