
#include "include/Visualizer.hpp"



int main()
{
    Visualizer v1;
    v1.Run();

    return 0;
}

/*
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

void generate(CA1d* ca_p, BMPgenerator& bmp_p, MidiToFile& mtf_p)
{
    bmp_p.newImage(0);
    mtf_p.newSheet();

    draw_line(ca_p->getData(), 0);
    bmp_p.drawData(ca_p->getData(), 0, states);
    mtf_p.drawData(ca_p->getData(), 1);
    refresh();

    for(int i = 1; i < generations; i++)
    {
        ca_p->generate();
        draw_line(ca_p->getData(), i);
        bmp_p.drawData(ca_p->getData(), i, states);
        mtf_p.drawData(ca_p->getData(), 2);
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

    CA1dtot*        ca = NULL;
    BMPgenerator    bmp(    size * scaling,
                            generations * scaling,
                            scaling);

    MidiToFile      mtf1;

    while(command != 'q')
    {
        switch(command)
        {
            case 'n':
                erase();
                ca = newCAtot(ca);
                printstr(ca->str());
                generate(ca, bmp, mtf1);
                break;

            case 'r':
                erase();
                ca->initialize(size, CA1d::Start::Random);
                printstr(ca->str());
                generate(ca, bmp, mtf1);
                break;

            case 'm':
                erase();
                ca->initialize(size, CA1d::Start::Middle);
                printstr(ca->str());
                generate(ca, bmp, mtf1);
                break;

            case 'l':
                erase();
                ca->initialize(size, CA1d::Start::Left);
                printstr(ca->str());
                generate(ca, bmp, mtf1);
                break;

            case 's':
                mtf1.saveFile(ca->str());
                bmp.saveImage(ca->str());
                mvprintw(1, 1, "Image and MIDI saved!");
                refresh();
                break;

            default:
                break;
        }
        command = getch();
    }

    endwin();
    return 0;
}
*/
