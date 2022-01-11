#ifndef utilities_hpp
#define utilities_hpp

#include <vector>
#include <string>

struct Pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

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

Pixel inverse(const Pixel& in);
std::vector<Pixel> state_to_palette(int states, int palette = 0);

#endif //utilities_hpp
