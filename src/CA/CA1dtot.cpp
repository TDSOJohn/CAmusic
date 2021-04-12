#include "../../include/CA/CA1dtot.hpp"
#include "../../utilities.hpp"



CA1dtot::CA1dtot(   unsigned int rad_in,
                    unsigned int stat_in,
                    std::vector<int> const& rule_in):
    CA1d(rad_in, stat_in, ((stat_in - 1) * (rad_in * 2 + 1) + 1), rule_in)
{}


void CA1dtot::generate()
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
        {
            temp +=  mData[i-j];
        }
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
