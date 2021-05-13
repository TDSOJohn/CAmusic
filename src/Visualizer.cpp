#include "../include/Visualizer.hpp"

#include "../utilities.hpp"



Visualizer::Visualizer():
    mStates(5),
    mRadius(2),
    mStart(CA1d::Start::Middle),
    mType(CA1d::Type::Totalistic),
    mScaling(2),
    ca1d(NULL),
    bmp_p(NULL),
    mtf_p(NULL),
    mRule({})
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

        attron(mStates - 1);
        mvprintw(size_y + 1, 2, "n for new rule, r for random, m for middle, l for left, s to save");
        attroff(mStates - 1);
        switch(command)
        {
            /// Analyzer
            case 'a':
                analyze();
            /// Left start
            case 'l':
                mStart = CA1d::Start::Left;
                ca1d->initialize(size_x, mStart);
                generate();
                break;
            /// Middle start
            case 'm':
                mStart = CA1d::Start::Middle;
                ca1d->initialize(size_x, mStart);
                generate();
                break;
            /// New rule (random-generated)
            case 'n':
                newCA();
                generate();
                break;
            /// Ordered start
            case 'o':
                mStart = CA1d::Other;
                t0 = {};
                for(int i = 0; i < size_x; i++)
                    t0.push_back(modulo(i, mStates));
                ca1d->initialize(t0);
                generate();
                break;
            /// Open preferences panel
            case 'p':
                preferences();
                break;
            /// Random start
            case 'r':
                mStart = CA1d::Start::Random;
                ca1d->initialize(size_x, mStart);
                generate();
                break;
            /// Save rule to file (bitmap and midi)
            case 's':
                save();
                break;

            default:
                break;
        }
        attron(mStates - 1);
        mvprintw(0, 1, "States : %d, Radius : %d", mStates, mRadius);
        attroff(mStates - 1);
        command = getch();
    }
}

//  Colors are 1, ..., min(states, colors - 1) for grey scale
//  COLORS color is left for interface definition and is (0xFF, 0xFF, 0xFF)
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
        //  Initialize color pairs (0, ..., min(COLORS, mStates)^2)
        start_color();
        initializePairs();
        initializeGrey();
    }
}


void Visualizer::initializeGrey()
{
    //  Initialize colors to be gray scale
    for(int i = 0; i < std::min(mStates, COLORS); i++)
        init_color(i, ((1000/(mStates - 1)) * i), ((1000/(mStates - 1)) * i), ((1000/(mStates - 1)) * i));
}


void Visualizer::initializePairs()
{
    for(int i = 0; i < mStates; i++)
    {
        for(int j = 0; j < mStates; j++)
        {
            //  Maybe change also pair(0,0) ?
            if((i != 0) || (j != 0))
                init_pair(((i * mStates) + j), j, i);
        }
    }
}


void Visualizer::newCA()
{
    //  Correct size_x to have complete loop in modulo start
    size_x -= modulo(size_x, mStates);

    if(ca1d != NULL)
    {
        delete ca1d;
        ca1d = NULL;
    }

    ca1d = new CA1d(mType, mRadius, mStates, mRule);
    if(mStart != CA1d::Other)
        ca1d->initialize(size_x, mStart);
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
    bmp_p = new BMPgenerator(size_x, size_y, mScaling);
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
    uint8_t color = (data_in[0] * mStates);
    attron(COLOR_PAIR(color));

    for(int i = 0; i < data_in.size(); i++)
    {
        if(data_in[i] != color)
        {
            attroff(COLOR_PAIR(color));
            color = (data_in[i] * mStates);
            attron(COLOR_PAIR(color));
        }
        mvaddch(y + 1, i, ' ');
    }
    attroff(COLOR_PAIR(color));
}


void Visualizer::generate(bool print, bool bmp, bool mtf)
{
    if(bmp)
    {
        bmp_p->newFile(size_x, size_y, mScaling);
        bmp_p->drawData(ca1d->getData(), 0, mStates);
    }
    if(mtf)
    {
        mtf_p->newFile();
//        mtf_p->drawData(ca1d->getData(), 2);
        mtf_p->drawChord(ca1d->getData(), mStates);
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
            bmp_p->drawData(ca1d->getData(), i, mStates);
        if(mtf)
            mtf_p->drawChord(ca1d->getData(), mStates);
//            mtf_p->drawData(ca1d->getData(), 2);
    }
}


void Visualizer::analyze()
{

}


void Visualizer::preferences()
{
    char command = ' ';

    mvprintw(size_y + 1, 2, "q quit r radius s states t type");
    while(command != 'q' && command != 'n')
    {
        erase();
        attron(COLOR_PAIR(mStates-1));
        mvprintw(2, 2, " Rule : ");

        if(mRule.size() == 0)
        {
            printw("RANDOM ");
            printstr(ca1d->str());
        } else
        {
            for(auto& i : mRule)
                addch(i + 48);
            addch(' ');
        }

        mvprintw(4, 2, " States : %d ", mStates);
        mvprintw(6, 2, " Radius : %d ", mRadius);
        mvprintw(8, 2, " Type : %s ", ((mType == CA1d::Type::Standard) ? "Standard" : "Totalistic"));
        mvprintw(9,2, "-----------------------");
        mvprintw(10,2, " ncurses info: ");
        mvprintw(12,2, " colors : %d ", COLORS);

//        mvprintw(4, 50, " Rule")


        command = getch();

        switch(command)
        {
            case 'r':
                mRadius = getch() - 48;
                break;

            case 's':
                changeStates();
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
    attroff(COLOR_PAIR(mStates-1));
    erase();
}


void Visualizer::changeStates()
{
    int states_temp = getch() - 48;
    if(states_temp < (COLORS - 1))
    {
        mStates = states_temp;
        initializeGrey();
        initializePairs();
    } else
    {
        mvprintw(1, 1, "NOT ENOUGH COLORS FOR THE SELECTED STATES!");
    }
}


void Visualizer::save()
{
    erase();
    newBMP();
    //  Backup of start, size_x and size_y;
    const unsigned int  size_x_bak(size_x);
    const unsigned int  size_y_bak(size_y);
    CA1d::Start         start_bak(mStart);

    //  Set size, generate and save bmps
    int image_size_x[4] = {64, 256, 512, 1024};
    int image_size_y[4] = {32, 128, 256, 512};
    mRule = ca1d->getRule();
    //  Loop through every possible Start and every possible color palette
//    for(int startInt = CA1d::Start::Random; startInt != CA1d::Start::Right; startInt++)
    for(int j = 0; j < 4; j++)
    {
        bmp_p->setPalette(j);
        for(int i = 0; i < 4; i++)
        {
            size_x = image_size_x[i];
            size_y = image_size_y[i];
            mScaling = 1024 / image_size_x[i];
    //        mStart = static_cast<CA1d::Start>(startInt);
            newCA();
            ca1d->initialize(size_x, mStart);
            generate(false, true, false);
            bmp_p->saveFile(ca1d->str());
        }
    }
    mRule = {};
    mStart = start_bak;

/*
    //  Set size, generate and save mtf
    size_x = 32;
    size_y = 20;
    newMTF();
    newBMP();
    ca1d->initialize(size_x, mStart);
    generate(false, true, true);
    mtf_p->saveFile(ca1d->str());
    bmp_p->saveFile(ca1d->str());
*/
    size_x = size_x_bak;
    size_y = size_y_bak;

    mvprintw(1, 1, "Image and MIDI saved!");
    refresh();
}
