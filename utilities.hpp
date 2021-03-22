#ifndef utilities_hpp
#define utilities_hpp

#include <vector>



//  Simple modulo operator function that only returns positive values
unsigned modulo(int value, int m);

std::vector<int> ca_to_midi_note(std::vector<int> ca_in);

std::vector<int> ca_to_velocity(std::vector<int> ca_in);

#endif //utilities_hpp
