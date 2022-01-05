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


class Visualizer : private sf::NonCopyable
{
public:
    explicit                            Visualizer(sf::RenderTarget& outputTarget);

    void                                update();
    void                                draw();

    void                                handleEvent(sf::Event event);

    CA1d*                               getCA() { return mCa1dArray[0]; }

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

    int                                 mStates;
    int                                 mRadius;

    CA1d::Start                         mStart;
    CA1d::Type                          mType;
    int                                 mScaling;

    int                                 mPalette;

    CA1d*                               mCa1dArray[2];
    int                                 mCa1dSize;
};
#endif //visualizer_hpp
