#ifndef visualizer_hpp
#define visualizer_hpp

#include <string>
#include <vector>

#include <curses.h>

#include "CA/CA1d.hpp"

//  #include "MIDI/MIDIout.hpp"
#include "MIDI/midiToFile.hpp"
#include "BMP/BMPgenerator.hpp"

#include "../utilities.hpp"


class Visualizer
{
public:
                                        Visualizer();
                                        ~Visualizer();

    void                                Run();


private:
    int                                 states;
    int                                 radius;

    //  Used for screen output
    int                                 size_x;
    int                                 size_y;

    CA1d::Start                         start;
    CA1d::Type                          mType;
    int                                 scaling;

    CA1d*                               ca1d;

    BMPgenerator*                       bmp_p;
    MidiToFile*                         mtf_p;

    std::vector<int>                    rule;
    std::vector<int>                    t0;

private:
    void                                initializeColors();
    void                                initializeGrey();
    void                                newCA();
    void                                newBMP();
    void                                newMTF();

    void                                drawLine(std::vector<int> data_in, int y);
    auto                                printstr(const std::string &str) -> void;
    auto                                mvprintstr(unsigned int y, unsigned int x, const std::string &str) -> void;

    void                                generate(bool print = true, bool bmp = false, bool mtf = false);

    void                                analyze();
    void                                preferences();
    void                                save();
};


// rule 101010

#endif //visualizer_hpp
