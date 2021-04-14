#include "../../include/CA/CA1d.hpp"


#include <sstream>
#include <iterator>



CA1d::CA1d( unsigned int rad_in,
            unsigned int stat_in,
            double rule_size_in,
            std::vector<int> const& rule_in):
    CA(stat_in, rad_in, (rad_in * 2 + 1), rule_size_in, rule_in)
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


std::vector<int> CA1d::getData()
{
    return mData;
}


std::string CA1d::str()
{
    std::stringstream ss;
    ss << "results/";
    ss << "r";

    // This string has lsb on the left, should invert all numbers instead!
    std::copy(mRule.begin(), mRule.end(), std::ostream_iterator<int>(ss));

    ss << "k" << mRadius;
    ss << "s" << mStates;

    if(ss.str().size() < 251)
        ss << "_" << mStart;

    return ss.str();
}


std::ostream& operator<<(std::ostream& os, const CA1d& ca_out)
{
    std::copy(ca_out.mData.begin(), ca_out.mData.end(), std::ostream_iterator<int>(os));
    return os;
}
