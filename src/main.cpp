#include "App/Application.hpp"

#include <iostream>
#include <stdexcept>


int main()
{
    try
    {
        Application app;
        app.run();
    }
    catch(std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
