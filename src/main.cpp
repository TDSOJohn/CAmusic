#include "Visualizer.hpp"

#include <iostream>
#include <stdexcept>


int main()
{
    try
    {
        Visualizer app;
        app.run();
    }
    catch(std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
