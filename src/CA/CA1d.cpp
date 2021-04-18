#include "../../include/CA/CA1d.hpp"


#include <sstream>
#include <iterator>
#include <cmath>

#include "../../utilities.hpp"



CA1d::CA1d( Type ca_type,
            unsigned int rad_in,
            unsigned int stat_in,
            std::vector<int> const& rule_in):
    CA( stat_in,
        rad_in,
        (rad_in * 2 + 1),
        ((ca_type == Type::Standard) ? (pow(stat_in, rad_in * 2 + 1)) : ((stat_in - 1) * (rad_in * 2 + 1) + 1)),
        rule_in),
    mType(ca_type)
{}


void CA1d::initialize(unsigned int size_in, Start t0)
{
    mStart = t0;
    srand(time(NULL));

    mDim = size_in;

    mData.resize(mDim);

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
        {
            if(mType == Type::Standard)
                temp +=  (mData[modulo(i-j, mDim)] * pow(mStates, (j + mRadius)));
            else if(mType == Type::Totalistic)
                temp +=  mData[modulo(i-j, mDim)];
        }
        temp_data[i] = mRule[temp];
    }
    //  Central part (no wrapping)
    for(int i = mRadius; i < (mDim - mRadius); i++)
    {
        temp = 0;
        for(int j = (mRadius * (-1)); j < (mRadius + 1); j++)
        {
            if(mType == Type::Standard)
                temp +=  (mData[modulo(i-j, mDim)] * pow(mStates, (j + mRadius)));
            else if(mType == Type::Totalistic)
                temp +=  mData[modulo(i-j, mDim)];
        }
        temp_data[i] = mRule[temp];
    }
    //  Right border (wrapping)
    for(int i = (mDim - mRadius); i < mDim; i++)
    {
        temp = 0;
        for(int j = (mRadius * (-1)); j < (mRadius + 1); j++)
        {
            if(mType == Type::Standard)
                temp +=  (mData[modulo(i-j, mDim)] * pow(mStates, (j + mRadius)));
            else if(mType == Type::Totalistic)
                temp +=  mData[modulo(i-j, mDim)];
        }
        temp_data[i] = mRule[temp];
    }
    mData = temp_data;
}


std::vector<int> CA1d::getData() const
{
    return mData;
}


std::string CA1d::str() const
{
    std::stringstream ss;
    ss << "results/";
    ss << "r";

    // This string has lsb on the left, should invert all numbers instead!
    std::copy(mRule.rbegin(), mRule.rend(), std::ostream_iterator<int>(ss));

    ss << "k" << mRadius;
    ss << "s" << mStates;

    if(ss.str().size() < 240)
    {
        ss << "_" << mStart;
        ss << "_" << mData.size();
    }

    return ss.str();
}


std::ostream& operator<<(std::ostream& os, const CA1d& ca_out)
{
    std::copy(ca_out.mData.rbegin(), ca_out.mData.rend(), std::ostream_iterator<int>(os));
    return os;
}
