#include <iostream>
#include <vector>
#include <thread>
#include <chrono>


#include "headers/MIDIout.hpp"
#include "headers/CA.hpp"


std::vector<int> ca_to_midi_note(std::vector<int> ca_in)
{
    std::vector<int> result;
    std::vector<int> map = {48, 50, 52, 53, 55, 57, 59};

    for(int i = 0; i < ca_in.size(); i++)
        result.push_back(map[ca_in[i]]);

    return result;
}

std::vector<int> ca_to_velocity(std::vector<int> ca_in)
{
    std::vector<int> result;

    for(int i = 0; i < ca_in.size(); i++)
        result.push_back(ca_in[i] * 25);

    return result;
}


int main()
{
    srand(time(NULL));

    int states = 5;
    std::vector<int> rule1;
    std::vector<int> rule2;

    for(int i = 0; i < 125; i++)
    {
        rule1.push_back(rand()%states);
        rule2.push_back(rand()%states);
    }

    CA ca1(rule1, 1, states);
    CA ca2(rule2, 1, states);
    MIDIout midi1(240);

    std::vector<int> t0;
    std::vector<int> t1;

    for(int i = 0; i < 25; i++)
    {
        t0.push_back(i/5);
        t1.push_back(rand()%5);
    }

    ca1.initialize(t0);
    ca2.initialize(t1);

    ca1.print();
    ca2.print();

    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    t0 = ca_to_midi_note(ca1.getData());
    t1 = ca_to_velocity(ca2.getData());
    midi1.setPattern(t0, t1);
    midi1.setState(MIDIout::State::Play);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    midi1.setState(MIDIout::State::Play);


    for(int i = 0; i < 100; i++)
    {
        t0 = ca_to_midi_note(ca1.getData());
        t1 = ca_to_velocity(ca2.getData());
        midi1.setPattern(t0, t1);
        ca1.generate();
        ca2.generate();
        ca1.print();
        ca2.print();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    std::this_thread::sleep_for(std::chrono::seconds(20));

    std::cout << std::endl;

    return 0;
}
