#ifndef visualizer_hpp
#define visualizer_hpp

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

#include "App/Canvas.hpp"
#include "CA/CA1d.hpp"


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

    CAHolder(   unsigned int states_in,
                unsigned int radius_in,
                unsigned int palette_in,
                CA1d::Start start_in,
                CA1d::Type type_in,
                unsigned int scaling_in,
                Canvas::BlendMode blend_in):
            states(states_in),
            radius(radius_in),
            palette(palette_in),
            start(start_in),
            type(type_in),
            scaling(scaling_in),
            blendMode(blend_in)
    {
        ca1d = std::make_unique<CA1d>(type, radius, states);
    }
};


class Visualizer : private sf::NonCopyable
{
public:
    explicit                            Visualizer(sf::RenderTarget& outputTarget);

    void                                update();
    void                                draw();

    void                                handleEvent(sf::Event event);

//    CA1d*                               getCA() { return [0]; }

private:
    void                                newCA();

    void                                drawLine(std::vector<int> data_in, int y);
    void                                generate();
    void                                scrolling();
    void                                clearBuffer();

    void                                save();

private:
    sf::RenderTarget&                   mTarget;

    Canvas                              mCanvas;

    //Used for screen output
    int                                 size_x;
    int                                 size_y;

    std::vector<CAHolder>               mCAHolder;
};
#endif //visualizer_hpp
