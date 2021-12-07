#ifndef visualizer_hpp
#define visualizer_hpp

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

#include "CA/CA1d.hpp"
#include "MIDI/midiToFile.hpp"


class Visualizer : private sf::NonCopyable
{
public:
    explicit                            Visualizer(sf::RenderTarget& outputTarget);

    void                                update();
    void                                draw();

    void                                handleEvent(sf::Event event);

private:
    void                                newCA();

    void                                drawLine(std::vector<int> data_in, int y);
    void                                generate();
    void                                scrolling();

    void                                save();

private:
    sf::RenderTarget&                   mTarget;

    sf::Texture                         mTexture;
    sf::Sprite                          mSprite;

    //Used for screen output
    int                                 size_x = 720;
    int                                 size_y = 450;

    int                                 mStates;
    int                                 mRadius;

    CA1d::Start                         mStart;
    CA1d::Type                          mType;
    int                                 mScaling;

    std::vector<uint8_t>                buffer;
    int                                 mPalette;

    CA1d*                               ca1d;
    MidiToFile                          mtf_p;

    std::vector<int>                    mRule;
    std::vector<int>                    t0;
};
#endif //visualizer_hpp
