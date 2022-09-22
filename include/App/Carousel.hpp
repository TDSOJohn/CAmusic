#ifndef carousel_hpp
#define carousel_hpp


#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

#include "ResourceIdentifiers.hpp"
#include "App/Canvas.hpp"
#include "CA/CA1d.hpp"
#include "GUI/Button.hpp"
#include "GUI/Container.hpp"
#include "MIDI/midiToFile.hpp"


struct CAHolder;

class MidiToFile;

class Carousel : private sf::NonCopyable
{
public:
    explicit                            Carousel(sf::RenderTarget& outputTarget, const eng::TextureHolder& textures, const eng::FontHolder& fonts);

    void                                update();
    void                                draw();

    void                                handleEvent(sf::Event event);

private:
    //  If i == -1, initialize all CAs. If i != -1, initialize CA[i]
    void                                initializeCA(int i = -1);
    //  IMPROVE If i == -1, initialize all CAs. If i != -1, initialize CA[i]
    void                                changeRule(int i);

    void                                generate();
    void                                resetAndGenerate();
    void                                scroll();

    void                                changePalettes(int i = -1);
    void                                changeStart(int i = -1);
    void                                changeScrolling() { mScrolling = !mScrolling; }

    void                                save();
    void                                load(std::string filename);

    void                                buildGUI();

private:
    sf::RenderTarget&                   mTarget;
    const eng::TextureHolder&           mTextures;
    const eng::FontHolder&              mFonts;

    Canvas                              mCanvas;

    //Used for screen output
    int                                 size_x;
    int                                 size_y;
    int                                 global_scaling;

    int                                 updateCounter;
    int                                 frameCounter;
    int                                 directionCounter;
    bool                                mScrolling;

    std::vector<CAHolder>               mCAHolder;

    CA1d                                ca1d;

    eng::Container                      mGUIContainer;

    MidiToFile                          mMTF;
};
#endif //carousel_hpp
