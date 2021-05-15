#ifndef utilities_hpp
#define utilities_hpp

#include <vector>
#include <string>

#include <curses.h>



/// A set of C++11 functions to simplify dealing with ncurses bad std::string support

void printstr(const std::string &str);

void mvprintstr(const int y, const int x, const std::string &str);

void printvec(std::vector<int> const& v_in);

void mvprintvec(const int y, const int x, std::vector<int> const& v_in);



/// Simple modulo operator function that only returns positive values
unsigned modulo(int value, int m);

/// Simple decimal int to base n vector converter
std::vector<int> decimalToBaseN(const long long int n, const int base);

/// Simple base n vector to decimal int converter
long long int baseNtoDecimal(std::vector<int> const& n, const int base);



/// Simple function that maps 0-8 ints to (note off) and C major scale
/// Octave is calculated from C0 (int octave = 3 ==> map[1] = C3)
std::vector<int> ca_to_midi_note(std::vector<int> data_in, int octave);

/// Simple function that maps 0-5 ints to 0-125 velocity
std::vector<int> ca_to_velocity(std::vector<int> data_in);

#endif //utilities_hpp
