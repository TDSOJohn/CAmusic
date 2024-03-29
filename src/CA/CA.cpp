#include "CA/CA.hpp"
#include "utilities.hpp"

#include <sstream>
#include <random>

#include <iostream>


CA::CA( Type type_in,
        unsigned int stat_in,
        unsigned int rad_in,
        unsigned int neigh_in,
        double rule_size_in,
        std::vector<int> const& rule_in):
    mType(type_in),
    mStates(stat_in),
    mRadius(rad_in),
    mNeighbrs(neigh_in),
    mRuleSize(rule_size_in),
    mRule(rule_in)
{
    setRule(rule_in);
}

void CA::setRule(std::vector<int> const& rule_in)
{
    mRule = rule_in;
    if(mRule.size() == 0)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, (mStates - 1));

        for(int i = 0; i < mRuleSize; i++)
            mRule.push_back(distrib(gen));
    } else
    {
        //  check rule size and delete elements if too big
        while(mRule.size() > mRuleSize)
            mRule.pop_back();
        //  check rule size and add zeros if too small
        while(mRule.size() < mRuleSize)
            mRule.push_back(0);
    }
}

std::string CA::getRuleString() const
{
    std::stringstream ss;
    for(auto& i : mRule)
        ss << i;
    return ss.str();
}
