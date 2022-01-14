#ifndef Settings_hpp
#define visualizer_hpp

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

#include "App/State.hpp"
#include "CA/CA1d.hpp"
#include "MIDI/midiToFile.hpp"


class Settings : private sf::NonCopyable
{
public:
    explicit                            Settings(State::Context* context);

    void                                update();
    void                                draw();

    void                                handleEvent(sf::Event event);

private:

    void                                save();

private:
    sf::RenderWindow&                   mTarget;
};
#endif //visualizer_hpp
