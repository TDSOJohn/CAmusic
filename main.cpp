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

    int states = 6;
    int radius = 1;
    int rule_size = pow(states, (radius * 2 + 1));
    int size = 50;
    int generations = 30;

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
    MIDIout midi1(480);

    std::vector<int> t0;
    std::vector<int> t1;

    for(int i = 0; i < size; i++)
    {
        t0.push_back(i/26);
        t1.push_back(rand()%5);
    }

    ca1.initialize(size, CA1d::Start::Random);
    //ca2.initialize(t1);

    t0 = ca_to_midi_note(ca1.getData());
    //t1 = ca_to_velocity(ca2.getData());

    midi1.setPattern(t0);
    ca1.print();
    midi1.setState(MIDIout::State::Play);

    for(int i = 0; i < generations; i++)
    {
        ca1.generate();
        ca1.print();
        t0 = ca_to_midi_note(ca1.getData());
        midi1.setPattern(t0);
        midi1.setState(MIDIout::State::Play);
    }

    std::cout << std::endl;
    return 0;
}
