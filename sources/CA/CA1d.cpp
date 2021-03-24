#include "../../headers/CA/CA1d.hpp"


#include <iostream>
#include <cmath>


#include "../../utilities.hpp"



CA1d::CA1d(std::vector<int>& rule_in, int rad_in, int stat_in):
    CA(rule_in, rad_in, stat_in)
{
    //  store neighborhood size for efficiency
    mNeighbrs = (2 * mRadius) + 1;
    //  calculate rules vector dimensions using radius and status count
    mRuleSize = pow(mStates, mNeighbrs);

    //  check rule size and correct accordingly
    while(mRule.size() < mRuleSize)
        mRule.push_back(0);

    //  if rule vector is too big (add throw error)
    if(mRule.size() > mRuleSize)
        std::cout << "\n\terror, rule array is bigger than expected!\n";
}


void CA1d::initialize(int size_in, Start t0)
{
    mDim     = size_in;

    if(t0 == Start::Random)
    {
        for(int i = 0; i < mDim; i++)
            mData.push_back(rand()%mStates);
    } else
    {
        for(int i = 0; i < mDim; i++)
            mData.push_back(0);

        if(t0 == Start::Middle)
            mData[mDim/2] = 1;
        if(t0 == Start::Left)
            mData[0] = 1;
        if(t0 == Start::Right)
            mData[mDim-1] = 1;
    }
}


void CA1d::initialize(std::vector<int>& t0)
{
    mData    = t0;
    mDim     = mData.size();
}


std::vector<int> CA1d::getData()
{
    return mData;
}


void CA1d::print()
{
    std::cout << std::endl;

    std::vector<char> char_map = { ' ', '.', '*', 'o', 'O', '0'};
    for(int i = 0; i < mDim; i++)
        std::cout << char_map[mData[i]];
}


void CA1d::generate()
{
    int temp = 0;

    //  Maybe not the best way, copying entire vector is not efficient
    std::vector<int> temp_data(mData);

    //  Having 3 separate for cycles seems like the most efficient way to do it
    //  (no if at every step, no module at every step)
    //  Left border (wrapping)
    for(int i = 0; i < mRadius; i++)
    {
        temp = 0;
        for(int j = (mRadius * (-1)); j < (mRadius + 1); j++)
            temp +=  (mData[modulo(i-j, mDim)] * pow(mStates, (j + mRadius)));
        temp_data[i] = mRule[temp];
    }
    //  Central part (no wrapping)
    for(int i = mRadius; i < (mDim - mRadius); i++)
    {
        temp = 0;
        for(int j = (mRadius * (-1)); j < (mRadius + 1); j++)
            temp +=  (mData[i-j] * pow(mStates, (j + mRadius)));
        temp_data[i] = mRule[temp];
    }
    //  Right border (wrapping)
    for(int i = (mDim - mRadius); i < mDim; i++)
    {
        temp = 0;
        for(int j = (mRadius * (-1)); j < (mRadius + 1); j++)
            temp +=  (mData[modulo(i-j, mDim)] * pow(mStates, (j + mRadius)));
        temp_data[i] = mRule[temp];
    }

    mData = temp_data;
}
