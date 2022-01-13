#ifndef utilities_hpp
#define utilities_hpp

#include "Utility.hpp"

#include <vector>
#include <string>


/// \brief Simple decimal int to base n vector converter
/// Converts a long long int to a base n [std::vector<int>](https://en.cppreference.com/w/cpp/container/vector)
/// \param n long long int input number
/// \param base The base to convert to
/// \returns [std::vector<int>](https://en.cppreference.com/w/cpp/container/vector) containing an int element for each digit of the number
std::vector<int> decimalToBaseN(const long long int n, const int base);


/// \brief Simple base n vector to decimal int converter
/// Converts a [std::vector<int>](https://en.cppreference.com/w/cpp/container/vector) of numerical digits in a generic base n to a decimal long long int
/// \param n The [std::vector<int>](https://en.cppreference.com/w/cpp/container/vector) input
/// \param base The base to convert the vector from
/// \returns A long long int containing the decimal rappresentation of the input number
long long int baseNtoDecimal(std::vector<int> const& n, const int base);


/// \brief Simple function that maps 0-8 ints to (note off) and C major scale
/// \param data_in [std::vector<int>](https://en.cppreference.com/w/cpp/container/vector) containing data
/// \param octave int used to transpose by a number of octaves
/// Octave is calculated from C0 (int octave = 3 ==> map[1] = C3)
/// \returns [std::vector<int>](https://en.cppreference.com/w/cpp/container/vector) containing the midi note values
std::vector<int> ca_to_midi_note(std::vector<int> data_in, int octave);


/// Simple function that maps 0-max_val ints to 0-125 velocity
/// \param data_in [std::vector<int>](https://en.cppreference.com/w/cpp/container/vector) containing data
/// \param max_val int containing the steps to divide velocity in
/// \returns [std::vector<int>](https://en.cppreference.com/w/cpp/container/vector) with the correct 0..127 velocity
std::vector<int> ca_to_velocity(std::vector<int> data_in, int max_val);


std::vector<Pixel> state_to_palette(int states, int palette = 0);


#endif //utilities_hpp
