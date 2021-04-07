#include "../../include/CA/CA1d.hpp"


#include <iostream>
#include <sstream>



CA1d::CA1d(std::vector<int> const& rule_in, unsigned int rad_in, unsigned int stat_in):
    CA(rule_in, stat_in),
    mRadius(rad_in)
{
    mNeighbrs = (mRadius * 2 + 1);
}


CA1d::CA1d(std::vector<int>&& rule_in, unsigned int rad_in, unsigned int stat_in):
    CA(rule_in, stat_in),
    mRadius(rad_in)
{
    mNeighbrs = (mRadius * 2 + 1);
}


void CA1d::initialize(unsigned int size_in, Start t0)
{
    mStart = t0;
    srand(time(NULL));

    mDim = size_in;
    while(mData.size() < mDim)
        mData.push_back(0);

    if(mStart == Start::Random)
    {
        for(auto& i : mData)
            i = rand()%mStates;
    } else
    {
        for(auto& i : mData)
            i = 0;

        if(mStart == Start::Middle)
            mData[mDim/2] = 1;
        if(mStart == Start::Left)
            mData[0] = 1;
        if(mStart == Start::Right)
            mData[mDim - 1] = 1;
    }
}


void CA1d::initialize(std::vector<int> const& t0)
{
    mStart = Start::Other;
    mData = t0;
}


void CA1d::initialize(std::vector<int>&& t0)
{
    mData = std::move(t0);
}


std::vector<int> CA1d::getData()
{
    return mData;
}


void CA1d::print()
{
    std::vector<char> char_map = { ' ', '.', '*', 'o', 'O', '0'};

    for(int i = 0; i < mDim; i++)
        std::cout << char_map[mData[i]];
    std::cout << std::endl;
}


std::string CA1d::str()
{
    std::stringstream ss;
    ss << "results/";
    ss << "r";

    if(mRule.size() < 248)
    {
        for(auto i: mRule)
            ss << i;
    }
//    std::copy(mRule.begin(), mRule.end(), std::ostream_iterator<std::string>(ss));
    ss << "k" << mRadius;
    ss << "s" << mStates;

    if(ss.str().size() < 251)
        ss << "_" << mStart;

    return ss.str();
}
