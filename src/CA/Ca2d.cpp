#include "../../include/CA/CA2d.hpp"

#include <iostream>


CA2d::CA2d(std::vector<int> const& rule, unsigned int states, unsigned int radius):
    CA(rule, states)
{

}


CA2d::CA2d(std::vector<int>&& rule, unsigned int states, unsigned int radius):
    CA(rule, states)
{

}
