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


class Visualizer : private sf::NonCopyable
{
public:
    explicit                            Visualizer(sf::RenderTarget& outputTarget, const eng::TextureHolder& textures, const eng::FontHolder& fonts);

    void                                update();
    void                                draw();

    void                                handleEvent(sf::Event event);

private:
    void                                initializeCA();
    void                                updateRules();

    void                                generate();
    void                                scroll();

    void                                changePalettes(int i);
    void                                changeScrolling() { mScrolling = !mScrolling; }

    void                                save();
    void                                load(std::string filename);

private:
    sf::RenderTarget&                   mTarget;
    eng::TextureHolder                  mTextures;

    Canvas                              mCanvas;

    //Used for screen output
    int                                 size_x;
    int                                 size_y;

    bool                                mScrolling;

    std::vector<CAHolder>               mCAHolder;

    eng::Container                      mGUIContainer;
};
#endif //visualizer_hpp
