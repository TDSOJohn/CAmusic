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
    int                                 mStates;
    int                                 mRadius;

    //  Used for screen output
    int                                 size_x;
    int                                 size_y;

    CA1d::Start                         mStart;
    CA1d::Type                          mType;
    int                                 mScaling;

    CA1d*                               ca1d;

    BMPgenerator*                       bmp_p;
    MidiToFile*                         mtf_p;

    std::vector<int>                    mRule;
    std::vector<int>                    t0;

    bool                                analyzeData;
    std::vector<int>                    analyzeOutput;

private:
    void                                initializeColors();
    void                                initializeGrey();
    void                                initializePairs();

    void                                newCA();
    void                                newBMP();
    void                                newMTF();

    void                                drawLine(std::vector<int> data_in, int y);

    void                                generate(bool print = true, bool bmp = false, bool mtf = false);

    void                                analyze();

    void                                preferences();
    void                                changeStates();

    void                                save();
};

// rule 101010

#endif //visualizer_hpp
