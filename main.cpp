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

auto printstr(const std::string &str) -> void
{
        for (char ch : str)
        {
                addch (ch);
        }
}


//  Useful Cellular Automaton constants
const int states        = 10;
const int radius        = 2;
const int rule_size_tot = (states - 1) * (radius * 2 + 1) + 1;
const int rule_size_gen = pow(states, (radius * 2 + 1));

int size                = 140;
int generations         = 70;
const int scaling       = 1;
//  End of useful constants



CA1dgen* newCAgen(CA1dgen* ca_p)
{
    std::vector<int> rule;
    std::vector<int> t0;

    if(ca_p != NULL)
    {
        delete ca_p;
        ca_p = NULL;
    }
    ca_p = new CA1dgen(radius, states);
    ca_p->initialize(size, CA1d::Start::Random);

    return ca_p;
}

CA1dtot* newCAtot(CA1dtot* ca_p)
{
    std::vector<int> rule;
    std::vector<int> t0;

    if(ca_p != NULL)
    {
        delete ca_p;
        ca_p = NULL;
    }
    ca_p = new CA1dtot(radius, states);
    ca_p->initialize(size, CA1d::Start::Middle);

    return ca_p;
}

void generate(CA1d* ca_p)
{
    draw_line(ca_p->getData(), 0);
    refresh();
    for(int i = 1; i < generations; i++)
    {
        ca_p->generate();
        draw_line(ca_p->getData(), i);
        refresh();
    }

}

void initialize_colors()
{
    //  Check if terminal has color support
    if(has_colors() == FALSE)
    {
        printw("your terminal does now support colors!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        //  Initialize color pairs (0, ..., 49)
        start_color();
        //  Initialize colors to be gray scale
        for(int i = 0; i < std::min(states, COLORS); i++)
            init_color(i, ((1000/(states - 1)) * i), ((1000/(states - 1)) * i), ((1000/(states - 1)) * i));

        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if((i != 0) || (j != 0))
                    init_pair(((i * 8) + j), j, i);
            }
        }
    }

}


int main()
{
    srand(time(NULL));

    unsigned int size_x, size_y;
    char command = 'n';

    if(initscr() == NULL)
    {
        fprintf(stderr, "Error initialising ncurses\n");
        exit(EXIT_FAILURE);
    }

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    initialize_colors();

    getmaxyx(stdscr, size_y, size_x);
    size        = size_x - 1;
    generations = size_y - 1;

    CA1dtot*         ca = NULL;

    while(command != 'q')
    {
        switch(command)
        {
            case 'n':
                erase();
                ca = newCAtot(ca);
                printstr(ca->str());
                generate(ca);
                break;

            case 'r':
                erase();
                ca->initialize(size, CA1d::Start::Random);
                printstr(ca->str());
                generate(ca);
                break;

            case 'm':
                erase();
                ca->initialize(size, CA1d::Start::Middle);
                printstr(ca->str());
                generate(ca);
                break;

            case 'l':
                erase();
                ca->initialize(size, CA1d::Start::Left);
                printstr(ca->str());
                generate(ca);
                break;

            default:
                break;
        }
        command = getch();
    }

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
        mvaddch(y + 1, i, ' ');
    }
    attroff(COLOR_PAIR(color));
}
