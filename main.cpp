#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>


#include "headers/MIDI/MIDIout.hpp"

#include "headers/CA/CA1d.hpp"
#include "headers/CA/TotalisticCA.hpp"

#include "utilities.hpp"


int main()
{
    srand(time(NULL));

    int states = 4;
    int radius = 1;
    int rule_size = pow(states, (radius * 2 + 1));
    int size = 200;
    int generations = 100;

    std::vector<int> rule1;
    std::vector<int> rule2;

    for(int i = 0; i < rule_size; i++)
    {
        rule1.push_back(rand()%states);
        std::cout << "\t" << rule1[i];
        rule2.push_back(rand()%states);
    }

    rule1[0] = 0;

    CA1d ca1(rule1, radius, states);
    TotalisticCA ca2(rule2, radius, states);

    ca1.initialize(size, CA1d::Start::Random);
    ca2.initialize(size, TotalisticCA::Start::Middle);


    ca1.print();
    for(int i = 0; i < generations; i++)
    {
        ca1.generate();
        ca1.print();
    }

    ca2.print();
    for(int i = 0; i < generations; i++)
    {
        ca2.generate();
        ca2.print();
    }

    std::cout << std::endl;
    return 0;
}
