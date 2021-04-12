#include <string>
#include <sstream>
#include <vector>

#include <curses.h>


#include "include/CA/CA1dgen.hpp"
#include "include/CA/CA1dtot.hpp"

#include "include/MIDI/MIDIout.hpp"
#include "include/MIDI/midiToFile.hpp"
#include "include/BMP/BMPgenerator.hpp"

#include "utilities.hpp"


void draw_line(std::vector<int> data_in, int y);


//  Useful Cellular Automaton constants
const int states        = 6;
const int radius        = 1;
const int rule_size_tot = (states - 1) * (radius * 2 + 1) + 1;
const int rule_size_gen = pow(states, (radius * 2 + 1));

int size                = 140;
int generations         = 70;
const int scaling       = 1;

std::bitset<rule_size_tot> ruleBits{0};
unsigned int dec_rule   = rand()%((int)pow(2, rule_size_tot));
//  End of useful constants



CA1dgen* newCAgen(CA1dgen* ca_p)
{
    std::vector<int> rule;
    std::vector<int> t0;

    ruleBits = dec_rule;

    for(int i = 0; i < rule_size_gen; i++)
        rule.push_back(ruleBits[i]);

    if(ca_p != NULL)
    {
        delete ca_p;
        ca_p = NULL;
    }
    ca_p = new CA1dgen(radius, states, rule);
    ca_p->initialize(size, CA1d::Start::Random);

    dec_rule++;

    return ca_p;
}

CA1dtot* newCAtot(CA1dtot* ca_p)
{
    std::vector<int> rule;
    std::vector<int> t0;

    ruleBits = dec_rule;

    for(int i = 0; i < rule_size_tot; i++)
        rule.push_back(ruleBits[i]);


    if(ca_p != NULL)
    {
        delete ca_p;
        ca_p = NULL;
    }
    ca_p = new CA1dtot(radius, states, rule);
    ca_p->initialize(size, CA1d::Start::Middle);

    dec_rule++;

    return ca_p;
}


int main()
{
    dec_rule = 219433;

    unsigned int size_x, size_y;

    if(initscr() == NULL)
    {
        fprintf(stderr, "Error initialising ncurses\n");
        exit(EXIT_FAILURE);
    }

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    getmaxyx(stdscr, size_y, size_x);
    size        = size_x - 1;
    generations = size_y - 1;

    printw("This screen is: %d x %d\n", size_x, size_y);
    refresh();

    if(has_colors() == FALSE)
        printw("your terminal does now support colors!\n");
    else
    {
        start_color();
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if((i != 0) || (j != 0))
                    init_pair(((i * 8) + j), j, i);
            }
        }
    }

    srand(time(NULL));

    CA1dtot*         ca = NULL;

    ca = newCAtot(ca);

    int i = 1;
    uint8_t color = 0;

    draw_line(ca->getData(), 0);
    refresh();

    for(i = 1; i < generations; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ca->generate();
        draw_line(ca->getData(), i);
        refresh();
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    endwin();
    return 0;
}


void draw_line(std::vector<int> data_in, int y)
{
    uint8_t color = (data_in[0] * 8);
    attron(color);

    for(int i = 0; i < data_in.size(); i++)
    {
        if(data_in[i] != color)
        {
            attroff(COLOR_PAIR(color));
            color = (data_in[i] * 8);
            attron(COLOR_PAIR(color));
        }
        mvaddch(y, i, (char)(data_in[i] + 48));
    }
    attroff(color);
}
