#ifndef visualizer_hpp
#define visualizer_hpp

#include <string>
#include <vector>

#include "CA/CA1d.hpp"

//  #include "MIDI/MIDIout.hpp"
#include "MIDI/midiToFile.hpp"

#include "utilities.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>


class Visualizer
{
public:
                                        Visualizer();
                                        ~Visualizer() = default;

    void                                run();

private:
    int                                 mStates;
    int                                 mRadius;

    //  DON'T LIKE IT   Used for screen output
    int                                 size_x = 720;
    int                                 size_y = 450;

    CA1d::Start                         mStart;
    CA1d::Type                          mType;
    int                                 mScaling;

    std::vector<uint8_t>                buffer;
    int                                 mPalette;

    CA1d*                               ca1d;
    MidiToFile                          mtf_p;

    std::vector<int>                    mRule;
    std::vector<int>                    t0;

    bool                                genBMP, genMIDI, genPRINT;

    sf::RenderWindow                    mWindow;
    sf::Texture                         mTexture;
    sf::Sprite                          mSprite;

private:
    void                                newCA();
    void                                newBMP();
    void                                newMTF();

    void                                drawLine(std::vector<int> data_in, int y);

    void                                generate();
    void                                scrolling();

    void                                processInput();
    void                                update();
    void                                render();

    void                                preferences();
    void                                save();
};

// rule 101010

#endif //visualizer_hpp
