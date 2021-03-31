#include "../../headers/CA/CA1d.hpp"
#include "../../utilities.hpp"


#include <iostream>
#include <cmath>



CA1d::CA1d(std::vector<int> const& rule_in, int rad_in, int stat_in):
    CA(rule_in, rad_in, stat_in)
{
    //  calculate rules vector dimensions using radius and status count
    mRuleSize = pow(mStates, mNeighbrs);

    //  check rule size and correct accordingly
    while(mRule.size() < mRuleSize)
        mRule.push_back(0);

    //  if rule vector is too big (add throw error)
    if(mRule.size() > mRuleSize)
        std::cout << "\n\terror, rule array is bigger than expected!\n";
}


CA1d::CA1d(std::vector<int>&& rule_in, int rad_in, int stat_in):
    CA(rule_in, rad_in, stat_in)
{
    //  calculate rules vector dimensions using radius and status count
    mRuleSize = pow(mStates, mNeighbrs);

    //  check rule size and correct accordingly
    while(mRule.size() < mRuleSize)
        mRule.push_back(0);

    //  if rule vector is too big (add throw error)
    if(mRule.size() > mRuleSize)
        std::cout << "\n\terror, rule array is bigger than expected!\n";
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
