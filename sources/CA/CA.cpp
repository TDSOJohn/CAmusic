#include "../../headers/CA/CA.hpp"


#include <iostream>
#include <sstream>



CA::CA(std::vector<int> const& rule_in, int rad_in, int stat_in):
    mRule(rule_in),
    mRadius(rad_in),
    mStates(stat_in),
    mNeighbrs(mRadius * 2 + 1)
{}


CA::CA(std::vector<int>&& rule_in, int rad_in, int stat_in):
    mRule(std::move(rule_in)),
    mRadius(rad_in),
    mStates(stat_in),
    mNeighbrs(mRadius * 2 + 1)
{}


void CA::initialize(int size_in, Start t0)
{
    srand(time(NULL));

    mDim = size_in;
    while(mData.size() < mDim)
        mData.push_back(0);

    if(t0 == Start::Random)
    {
        for(auto& i : mData)
            i = rand()%mStates;
    } else
    {
        for(auto& i : mData)
            i = 0;

        if(t0 == Start::Middle)
            mData[mDim/2] = 1;
        if(t0 == Start::Left)
            mData[0] = 1;
        if(t0 == Start::Right)
            mData[mDim - 1] = 1;
    }
}


void CA::initialize(std::vector<int> const& t0)
{
    mData = t0;
}

/*
void CA::initialize(std::vector<int>&& t0)
{
    mData = t0;
}
*/

std::vector<int> CA::getData()
{
    return mData;
}


void CA::print()
{
    std::vector<char> char_map = { ' ', '.', '*', 'o', 'O', '0'};

    for(int i = 0; i < mDim; i++)
        std::cout << char_map[mData[i]];
    std::cout << std::endl;
}


std::string CA::str()
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

    if(ss.str().size() < 245)
        ss << "_" << rand()%1000000;

    ss << ".bmp";

    return ss.str();
}
