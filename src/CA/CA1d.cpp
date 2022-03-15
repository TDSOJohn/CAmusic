#include "Utility.hpp"
#include "CA/CA1d.hpp"

#include <sstream>
#include <iterator>
#include <cmath>

#include <iostream>


CA1d::CA1d( CA::Type ca_type,
            unsigned int rad_in,
            unsigned int stat_in,
            std::vector<int> const& rule_in):
    CA( ca_type,
        stat_in,
        rad_in,
        (rad_in * 2 + 1),
        //  Unreadable, but works
        ((ca_type == Type::Standard) ? (pow(stat_in, rad_in * 2 + 1)) : ((stat_in - 1) * (rad_in * 2 + 1) + 1)),
        rule_in)
{
    std::cout << "total rule size: " << mRuleSize << std::endl;
}

void CA1d::initialize(unsigned int size_in, Start t0)
{
    mStart = t0;
    mDim = size_in;
    mData.resize(mDim);

    if(mStart == Start::Random)
    {
        for(auto& i : mData)
            i = rand()%mStates;
    } else if(mStart != Other)
    {
        for(auto& i : mData)
            i = 0;

        if(mStart == Start::Middle)
            mData[mDim/2] = (mStates - 1);
    } else
    {
        int counter = 0;
        for(auto& i : mData)
        {
            i = counter%mStates;
            counter++;
        }
    }
}

void CA1d::initialize(std::vector<int> const& t0)
{
    mStart = Start::Other;
    mData = t0;
    mDim = mData.size();
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
                temp +=  (mData[eng::modulo(i-j, mDim)] * pow(mStates, (j + mRadius)));
            else if(mType == Type::Totalistic)
                temp +=  mData[eng::modulo(i-j, mDim)];
        }
        temp_data[i] = mRule[(mRuleSize - 1) - temp];
    }
    //  Central part (no wrapping)
    for(int i = mRadius; i < (mDim - mRadius); i++)
    {
        temp = 0;
        for(int j = (mRadius * (-1)); j < (mRadius + 1); j++)
        {
            if(mType == Type::Standard)
                temp +=  (mData[eng::modulo(i-j, mDim)] * pow(mStates, (j + mRadius)));
            else if(mType == Type::Totalistic)
                temp +=  mData[eng::modulo(i-j, mDim)];
        }
        temp_data[i] = mRule[(mRuleSize - 1) - temp];
    }
    //  Right border (wrapping)
    for(int i = (mDim - mRadius); i < mDim; i++)
    {
        temp = 0;
        for(int j = (mRadius * (-1)); j < (mRadius + 1); j++)
        {
            if(mType == Type::Standard)
                temp +=  (mData[eng::modulo(i-j, mDim)] * pow(mStates, (j + mRadius)));
            else if(mType == Type::Totalistic)
                temp +=  mData[eng::modulo(i-j, mDim)];
        }
        temp_data[i] = mRule[(mRuleSize - 1) - temp];
    }
    mData = temp_data;
}

void CA1d::setRule(std::vector<int> const& rule_in)
{
    CA::setRule(rule_in);
}

std::vector<int> CA1d::getData() const
{
    return mData;
}

std::string CA1d::str() const
{
    std::stringstream ss;

    if(mType == Type::Standard)
        ss << "std";
    else
        ss << "tot";

    ss << "_rule";

    ss << getRuleString();

    ss << "_r" << mRadius;
    ss << "_k" << mStates;

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
