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

    ca1.initialize(size, CA1d::Start::Middle);
    ca2.initialize(size, TotalisticCA::Start::Middle);

    BMPgenerator bmp(   size * scaling,
                        generations * scaling,
                        scaling);

//    ca1.print();
//    bmp.drawData(ca1.getData(), 0);

/*    for(int i = 1; i < generations; i++)
    {
        ca1.generate();
//        ca1.print();
        bmp.drawData(ca1.getData(), i);
    }
*/
//    ca2.print();
    bmp.drawData(ca1.getData(), 0);
    for(int i = 1; i < generations; i++)
    {
        ca2.generate();
//        ca2.print();
        bmp.drawData(ca2.getData(), i);
    }

    bmp.saveImage(ca2.str());

    std::cout << std::endl;
    return 0;
}
