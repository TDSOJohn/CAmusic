#ifndef utilities_hpp
#define utilities_hpp

#include <vector>



//  Simple modulo operator function that only returns positive values
unsigned modulo(int value, int m);

//  MIDI note 0 is not a good choice, better just turn it off somehow
std::vector<int> ca_to_midi_note(std::vector<int> data_in, int octave);

std::vector<int> ca_to_velocity(std::vector<int> data_in);

#endif //utilities_hpp
