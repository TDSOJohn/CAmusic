#include "../headers/CA.hpp"


#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>



//  Simple modulo operator function that only returns positive values
unsigned modulo(int value, int m)
{
    int mod = value % m;
    if(mod < 0)
        mod += m;
    return mod;
}



CA::CA(std::vector<int>& rule_in, int rad_in, int stat_in):
    rule(rule_in),
    radius(rad_in),
    states(stat_in)
{
    //  calculate rules vector dimensions using radius and status count
    double rule_size = pow(states, (2 * radius + 1));
    std::cout << rule_size;

    //  store neighborhood size for efficiency
    neighbrs = (2 * radius) + 1;
    //  check rule size and correct accordingly
    while(rule.size() < rule_size)
    {
        rule.push_back(0);
    }
    std::cout << "\n\nadded missing values to rule vector:\t" << rule.size() << std::endl;
    //  if rule vector is too big (add throw error)
    if(rule.size() > rule_size)
        std::cout << "\n\terror, rule array is bigger than expected!\n";
}


void CA::initialize(int size_in, Start t0)
{
    dim     = size_in;

    if(t0 == Start::Random)
    {
        for(int i = 0; i < dim; i++)
            data.push_back(rand()%states);
    } else
    {
        for(int i = 0; i < dim; i++)
            data.push_back(0);

        if(t0 == Start::Middle)
            data[dim/2] = 1;
        if(t0 == Start::Left)
            data[0] = 1;
        if(t0 == Start::Right)
            data[dim-1] = 1;
    }
}


void CA::initialize(std::vector<int>& t0)
{
    data    = t0;
    dim     = data.size();
}


std::vector<int> CA::getData()
{
    return data;
}


void CA::print()
{
    std::cout << std::endl;

    std::vector<char> char_map = { ' ', '.', 'o', 'O', '0'};
    for(int i = 0; i < dim; i++)
        std::cout << char_map[data[i]];
}


void CA::generate()
{
    int temp = 0;

    //  Maybe not the best way, copying entire vector is not efficient
    std::vector<int> temp_data(data);

    //  Having 3 separate for cycles seems like the most efficient way to do it
    //  (no if at every step, no module at every step)
    //  Left border (wrapping)
    for(int i = 0; i < radius; i++)
    {
        temp = 0;
        for(int j = (radius * (-1)); j < (radius + 1); j++)
            temp +=  (data[modulo(i-j, dim)] * pow(states, (j + radius)));
        temp_data[i] = rule[temp];
    }
    //  Central part (no wrapping)
    for(int i = radius; i < (dim - radius); i++)
    {
        temp = 0;
        for(int j = (radius * (-1)); j < (radius + 1); j++)
            temp +=  (data[i-j] * pow(states, (j + radius)));
        temp_data[i] = rule[temp];
    }
    //  Right border (wrapping)
    for(int i = (dim - radius); i < dim; i++)
    {
        temp = 0;
        for(int j = (radius * (-1)); j < (radius + 1); j++)
            temp +=  (data[modulo(i-j, dim)] * pow(states, (j + radius)));
        temp_data[i] = rule[temp];
    }

    data = temp_data;
}
