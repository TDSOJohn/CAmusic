#ifndef visualizer_hpp
#define visualizer_hpp


#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

#include "ResourceIdentifiers.hpp"
#include "App/CAHolder.hpp"
#include "App/Canvas.hpp"
#include "CA/CA1d.hpp"
#include "GUI/Button.hpp"
#include "GUI/Container.hpp"

#include "CA/CA2d.hpp"


class Visualizer : private sf::NonCopyable
{
public:
    explicit                            Visualizer(sf::RenderTarget& outputTarget, const eng::TextureHolder& textures, const eng::FontHolder& fonts);

    void                                update();
    void                                draw();

    void                                handleEvent(sf::Event event);

private:
    //  If i == -1, initialize all CAs. If i != -1, initialize CA[i]
    void                                initializeCA(int i = -1);
    //  IMPROVE If i == -1, initialize all CAs. If i != -1, initialize CA[i]
    void                                changeRule(int i);

    void                                generate();
    void                                scroll();

    void                                changePalettes(int i);
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

    bool                                mScrolling;

    std::vector<CAHolder>               mCAHolder;

    CA1d                                ca1d;
//    CA2d                                ca2d;

    eng::Container                      mGUIContainer;
};
#endif //visualizer_hpp
