#include "../headers/TotalisticCA.hpp"
#include "../utilities.hpp"



TotalisticCA::TotalisticCA(std::vector<int>& rule_in, int rad_in, int stat_in):
    CA(rule_in, rad_in, stat_in)
{
    std::cout << std::endl << radius << "\t\t" << states << std::endl;
}


void TotalisticCA::generate()
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
            temp +=  data[modulo(i-j, dim)];
        temp_data[i] = rule[temp];
    }
    //  Central part (no wrapping)
    for(int i = radius; i < (dim - radius); i++)
    {
        temp = 0;
        for(int j = (radius * (-1)); j < (radius + 1); j++)
            temp +=  data[i-j];
        temp_data[i] = rule[temp];
    }
    //  Right border (wrapping)
    for(int i = (dim - radius); i < dim; i++)
    {
        temp = 0;
        for(int j = (radius * (-1)); j < (radius + 1); j++)
            temp +=  data[modulo(i-j, dim)];
        temp_data[i] = rule[temp];
    }

    data = temp_data;
}
