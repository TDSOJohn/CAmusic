#ifndef visualizer_hpp
#define visualizer_hpp


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


struct CAHolder
{
    std::unique_ptr<CA1d>   ca1d;
    unsigned int            states;
    unsigned int            radius;
    unsigned int            palette;
    CA1d::Start             start;
    CA1d::Type              type;
    int                     scaling;
    Canvas::BlendMode       blendMode;
    std::vector<int>        rule;

    CAHolder(   unsigned int states_in,
                unsigned int radius_in,
                unsigned int palette_in,
                CA1d::Start start_in,
                CA1d::Type type_in,
                unsigned int scaling_in,
                Canvas::BlendMode blend_in,
                std::vector<int> rule_in = {}):
            states(states_in),
            radius(radius_in),
            palette(palette_in),
            start(start_in),
            type(type_in),
            scaling(scaling_in),
            blendMode(blend_in),
            rule(rule_in)
    {
        ca1d = std::make_unique<CA1d>(type, radius, states, rule);
    }
};


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

    void                                randomizePalettes();

    void                                save();
    void                                load(std::string filename);

private:
    sf::RenderTarget&                   mTarget;
    eng::TextureHolder                  mTextures;

    Canvas                              mCanvas;

    //Used for screen output
    int                                 size_x;
    int                                 size_y;

    std::vector<CAHolder>               mCAHolder;

    eng::Container                      mGUIContainer;
};
#endif //visualizer_hpp
