#include "CA/CA2d.hpp"


CA2d::CA2d(CA::Type type_in, int rad_in, int stat_in, std::vector<int> const& rule):
    CA(type_in, stat_in, rad_in, 8, 8, rule)
{

}

void CA2d::generate()
{
//    for(int i = 0; i < )
}

void CA2d::initialize(int size_x_in, int size_y_in, Start t0)
{
    for(int i = 0; i < size_x_in; i++)
    {
        mData.push_back({});
        for(int j = 0; j < size_y_in; j++)
        {
            mData[i].push_back(0);
        }
    }
}

void CA2d::initialize(std::vector<std::vector<int> > const& t0)
{
    mData = t0;
}
