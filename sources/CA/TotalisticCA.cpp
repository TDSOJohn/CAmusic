#include "../../headers/CA/TotalisticCA.hpp"


#include <iostream>


#include "../../utilities.hpp"



TotalisticCA::TotalisticCA(std::vector<int> const& rule_in, int rad_in, int stat_in):
    CA(rule_in, rad_in, stat_in)
{
    //  calculate rule size
    mRuleSize = mStates * (mNeighbrs);
}


TotalisticCA::TotalisticCA(std::vector<int>&& rule_in, int rad_in, int stat_in):
    CA(rule_in, rad_in, stat_in)
{
    //  calculate rule size
    mRuleSize = mStates * (mNeighbrs);
}


void TotalisticCA::print()
{
    std::cout << std::endl;

    std::vector<char> char_map = { ' ', '.', '*', 'o', 'O', '0'};
    for(int i = 0; i < mDim; i++)
        std::cout << char_map[mData[i]];
}


void TotalisticCA::generate()
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
            temp +=  mData[modulo(i-j, mDim)];
        temp_data[i] = mRule[temp];
    }
    //  Central part (no wrapping)
    for(int i = mRadius; i < (mDim - mRadius); i++)
    {
        temp = 0;
        for(int j = (mRadius * (-1)); j < (mRadius + 1); j++)
            temp +=  mData[i-j];
        temp_data[i] = mRule[temp];
    }
    //  Right border (wrapping)
    for(int i = (mDim - mRadius); i < mDim; i++)
    {
        temp = 0;
        for(int j = (mRadius * (-1)); j < (mRadius + 1); j++)
            temp +=  mData[modulo(i-j, mDim)];
        temp_data[i] = mRule[temp];
    }

    mData = temp_data;
}
