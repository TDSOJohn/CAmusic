#ifndef application_hpp
#define application_hpp

#include <string>
#include <vector>

#include "CA/CA1d.hpp"

//  #include "MIDI/MIDIout.hpp"
//  #include "MIDI/midiToFile.hpp"
#include "App/StateStack.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "utilities.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>


class Application
{
public:
                                        Application();
                                        ~Application();// = default;

    void                                run();

private:
    sf::RenderWindow                    mWindow;
    StateStack                          mStateStack;
    FontHolder                          mFonts;

private:
    void                                registerStates();

    void                                processInput();
    void                                update();
    void                                draw();
};

// rule 101010

#endif //application_hpp
