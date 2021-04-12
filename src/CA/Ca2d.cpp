#include "../../include/CA/CA2d.hpp"



CA2d::CA2d(std::vector<int> const& rule, unsigned int states, unsigned int radius):
    CA(rule, states)
{

}


CA2d::CA2d(std::vector<int>&& rule_in, unsigned int states, unsigned int radius):
    CA(rule, states)
{

}


void CA2d::initialize(unsigned int size_in, Start t0);
{

}


void CA2d::initialize(std::vector<std::vector<int> > const& t0)
{

}


void CA2d::initialize(std::vector<std::vector<int> >&& t0)
{

}
