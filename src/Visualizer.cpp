#include "../include/Visualizer.hpp"


Visualizer::Visualizer():
    states(2),
    radius(2),
    start(CA1d::Start::Middle),
    mType(CA1d::Type::Totalistic),
    scaling(1),
    ca1d(NULL),
    bmp_p(NULL),
    mtf_p(NULL),
    rule({})
{
    srand(time(NULL));

    if(initscr() == NULL)
    {
        fprintf(stderr, "Error initialising ncurses\n");
        exit(EXIT_FAILURE);
    }
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    initializeColors();
    getmaxyx(stdscr, size_y, size_x);
    size_x -= 2;
    size_y -= 2;
}


Visualizer::~Visualizer()
{
    endwin();

    delete ca1d;
    delete bmp_p;
    delete mtf_p;
}


void Visualizer::Run()
{
    char command = 'n';

    while(command != 'q')
    {
        erase();

        mvprintw(size_y + 1, 2, "n for new rule, r for random, m for middle, l for left, s to save");
        switch(command)
        {
            /// Analyzer
            case 'a':
                analyze();
            /// Left start
            case 'l':
                start = CA1d::Start::Left;
                ca1d->initialize(size_x, start);
                generate();
                break;
            /// Middle start
            case 'm':
                start = CA1d::Start::Middle;
                ca1d->initialize(size_x, start);
                generate();
                break;
            /// New rule (random-generated)
            case 'n':
                newCA();
                generate();
                break;
            /// Ordered start
            case 'o':
                start = CA1d::Other;
                t0 = {};
                for(int i = 0; i < size_x; i++)
                    t0.push_back(modulo(i, states));
                ca1d->initialize(t0);
                generate();
                break;
            /// Open preferences panel
            case 'p':
                preferences();
                command = 'n';
                break;
            /// Random start
            case 'r':
                start = CA1d::Start::Random;
                ca1d->initialize(size_x, start);
                generate();
                break;
            /// Save rule to file (bitmap and midi)
            case 's':
                save();
                break;

            default:
                break;
        }
        mvprintw(0, 1, "States : %d, Radius : %d", states, radius);
//        mvprintstr(0, 1, ca1d->str());
        command = getch();
    }
}


void Visualizer::initializeColors()
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

        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if((i != 0) || (j != 0))
                    init_pair(((i * 8) + j), j, i);
            }
        }
        initializeGrey();
    }
}


void Visualizer::initializeGrey()
{
    //  Initialize colors to be gray scale
    for(int i = 0; i < std::min(states, COLORS); i++)
        init_color(i, ((1000/(states - 1)) * i), ((1000/(states - 1)) * i), ((1000/(states - 1)) * i));
}


void Visualizer::newCA()
{
    //  Correct size_x to have complete loop in modulo start
    size_x -= modulo(size_x, states);

    if(ca1d != NULL)
    {
        delete ca1d;
        ca1d = NULL;
    }

    ca1d = new CA1d(mType, radius, states, rule);
    if(start != CA1d::Other)
        ca1d->initialize(size_x, start);
    else
        ca1d->initialize(t0);
}


void Visualizer::newBMP()
{
    if(bmp_p != NULL)
    {
        delete bmp_p;
        bmp_p = NULL;
    }
    bmp_p = new BMPgenerator(size_x * scaling, size_y * scaling, scaling);
}


void Visualizer::newMTF()
{
    if(mtf_p != NULL)
    {
        delete mtf_p;
    }
    mtf_p = new MidiToFile();
}


void Visualizer::drawLine(std::vector<int> data_in, int y)
{
    uint8_t color = (data_in[0] * 8);
    attron(COLOR_PAIR(color));

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


auto Visualizer::printstr(const std::string &str) -> void
{
    for(char ch : str)
        addch (ch);
}


auto Visualizer::mvprintstr(unsigned int y, unsigned int x, const std::string &str) -> void
{
    unsigned int temp_x = x;

    for(char ch : str)
    {
        mvaddch(y, temp_x, ch);
        temp_x++;
    }
}


void Visualizer::generate(bool print, bool bmp, bool mtf)
{
    if(bmp)
    {
        bmp_p->newFile(0);
        bmp_p->drawData(ca1d->getData(), 0, states);
    }
    if(mtf)
    {
        mtf_p->newFile();
        mtf_p->drawData(ca1d->getData(), 2);
    }

    if(print)
    {
        drawLine(ca1d->getData(), 0);
        refresh();
    }

    for(int i = 1; i < size_y; i++)
    {
        ca1d->generate();
        if(print)
        {
            drawLine(ca1d->getData(), i);
            refresh();
        }
        if(bmp)
            bmp_p->drawData(ca1d->getData(), i, states);
        if(mtf)
            mtf_p->drawData(ca1d->getData(), 2);
    }
}


void Visualizer::analyze()
{

}


void Visualizer::preferences()
{
    char command = ' ';

    mvprintw(size_y + 1, 2, "q quit r radius s states");
    while(command != 'q')
    {
        erase();
        attron(COLOR_PAIR(8));
        mvprintw(2, 2, " Rule : ");

        if(rule.size() == 0)
            printw("RANDOM ");
        else
        {
            for(auto& i : rule)
                addch(i + 48);
            addch(' ');
        }

        mvprintw(4, 2, " States : %d ", states);
        mvprintw(6, 2, " Radius : %d ", radius);
        mvprintw(8, 2, " Type : %s ", ((mType == CA1d::Type::Standard) ? "Standard" : "Totalistic"));

        attroff(COLOR_PAIR(15));

        command = getch();

        switch(command)
        {
            case 'r':
                radius = getch() - 48;
                break;

            case 's':
                states = getch() - 48;
                initializeGrey();
                break;

            case 't':
                command = getch();
                if(command == 't')
                    mType = CA1d::Type::Totalistic;
                else if(command == 's')
                    mType = CA1d::Type::Standard;
                break;

            default:
                break;
        }
    }
}


void Visualizer::save()
{
    erase();
    //  Backup of size_x and size_y;
    const unsigned int size_x_bak(size_x);
    const unsigned int size_y_bak(size_y);

    //  Set size, generate and save bmp
    size_x = 2000;
    size_y = 1000;
    newBMP();
    ca1d->initialize(size_x, start);
    generate(false, true, false);
    bmp_p->saveFile(ca1d->str());

    //  Set size, generate and save mtf
    size_x = 32;
    size_y = 20;
    newMTF();
    newBMP();
    ca1d->initialize(size_x, start);
    generate(false, true, true);
    mtf_p->saveFile(ca1d->str());
    bmp_p->saveFile(ca1d->str());

    size_x = size_x_bak;
    size_y = size_y_bak;

    mvprintw(1, 1, "Image and MIDI saved!");
    refresh();
}
