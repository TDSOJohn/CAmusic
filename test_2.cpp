#include <string>
#include <thread>
#include <chrono>
#include <vector>

#include <cursesw.h>


const int states = 2;


auto printstr(const std::string &str) -> void
{
    for(char ch : str)
        addch (ch);
}

auto mvprintstr(unsigned int y, unsigned int x, const std::string &str) -> void
{
    unsigned int temp_x = x;

    for(char ch : str)
    {
        mvaddch(y, temp_x, ch);
        temp_x++;
    }
}

void initializeGrey()
{
    //  Initialize colors to be gray scale
    for(int i = 0; i < std::min(states, COLORS); i++)
        init_color(i, ((1000/(states - 1)) * i), ((1000/(states - 1)) * i), ((1000/(states - 1)) * i));
}

void drawLine(std::vector<int> data_in, int y)
{
    int color = (data_in[0] * 8);
    attron(COLOR_PAIR(color));

    for(int i = 0; i < data_in.size(); i++)
    {
        if(data_in[i] != color)
        {
//            attroff(COLOR_PAIR(color));
            color = (data_in[i] * 8);
//            attron(COLOR_PAIR(color));
        }
//        mvprintw()
        mvaddch(y + 1, i, data_in[i] + 48);
    }
    attroff(COLOR_PAIR(color));
}


int main()
{
    srand(time(NULL));
    int size_x = 0;
    int size_y = 0;

    if(initscr() == NULL)
    {
        fprintf(stderr, "Error initialising ncurses\n");
        exit(EXIT_FAILURE);
    }
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    erase();

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
        printw("Colors available: %d", COLOR_PAIRS);
    }
    getmaxyx(stdscr, size_y, size_x);
    size_x -= 2;
    size_y -= 2;

    mvprintw(10, 5, "Size is: %d by %d", size_x, size_y);
    refresh();

    std::vector<int> data;
    for(int i = 0; i < size_x; i++)
    {
        data.push_back(rand()%states);
        mvaddch(9, i, data[i] + 48);
    }

    drawLine(data, 11);
    refresh();

    char c = getch();
//    std::this_thread::sleep_for(std::chrono::seconds(5));

    endwin();
    return 0;
}
