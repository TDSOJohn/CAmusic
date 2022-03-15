#include "CA/CA2d.hpp"

#include <iostream>
#include <sstream>


CA2d::CA2d(CA::Type type_in, Neighborhood ngh_in, int rad_in, int stat_in, std::vector<int> const& rule):
    CA(type_in, stat_in, rad_in, 0, 6, rule),
    mDimX(10),
    mDimY(10)
{
    for(auto& i : mRule)
        std::cout << i << "\t";
    std::cout << std::endl;
}

void CA2d::generate()
{
    int temp;

    std::vector<std::vector<int> > temp_data(mData);

    for(int i = mRadius; i < (mDimY - mRadius); i++)
    {
        for(int j = mRadius; j < (mDimX - mRadius); j++)
        {
            temp = 0;
            if(mNeighborhood == Moore)
                for(int k_y = -mRadius; k_y <= mRadius; k_y++)
                    for(int k_x = -mRadius; k_x <= mRadius; k_x++)
                        temp += mData[i+k_y][j+k_x];

            else if(mNeighborhood == VonNeumann)
            {
                for(int k_y = -mRadius; k_y <= mRadius; k_y++)
                    temp += mData[i+k_y][j];
                // Check if k_x != 0 because otherwise it counts [i][j] 2 times
                for(int k_x = -mRadius; k_x <= mRadius; k_x++)
                    if(k_x != 0)
                        temp += mData[i][j+k_x];

            }
//            std::cout << temp << " ";
            temp_data[i][j] = mRule[(mRuleSize - 1) - temp];
        }
//        std::cout << std::endl;
    }
    mData = temp_data;
}

void CA2d::initialize(int size_x_in, int size_y_in, Start t0)
{
    mDimX = size_x_in;
    mDimY = size_y_in;

    mData.resize(mDimY);
    for(auto& i : mData)
        i.resize(mDimX);

    if(t0 == Start::Middle)
        mData[mDimY/2][mDimX/2] = mStates - 1;
    else if(t0 == Start::Corner)
        mData[mDimY-1][mDimX-1] = mStates - 1;

}

void CA2d::initialize(std::vector<std::vector<int> > const& t0)
{
    mData = t0;
}

std::string CA2d::str() const
{
    std::stringstream ss;

    for(auto& i : mData)
        for(auto& j : i)
            ss << j << "\t";
        ss << "\n\n";

    return ss.str();
}

void CA2d::setNeighborhoodType(Neighborhood n_in)
{
    mNeighborhood = n_in;
    if(mNeighborhood == Neighborhood::Moore)
        mNeighbrs = (1 + 2 * mRadius)*(1 + 2 * mRadius);
    if(mNeighborhood == Neighborhood::VonNeumann)
        mNeighbrs = mRadius*mRadius + (mRadius+1)*(mRadius+1);
}


// IMPROVE (see CA1d function, it uses some weird std::copy stuff)
std::ostream& operator<<(std::ostream& os, const CA2d& ca_out)
{
    for(auto& i : ca_out.mData)
    {
        for(auto& j : i)
            os << j << " ";
        os << "\n";
    }
    return os;
}
