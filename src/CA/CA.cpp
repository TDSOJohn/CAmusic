#include "../../include/CA/CA.hpp"


#include <sstream>
#include <random>



CA::CA( unsigned int stat_in,
        unsigned int rad_in,
        unsigned int neigh_in,
        double rule_size_in,
        std::vector<int> const& rule_in):
    mStates(stat_in),
    mRadius(rad_in),
    mNeighbrs(neigh_in),
    mRuleSize(rule_size_in),
    mRule(rule_in)
{
    //CHECK IF RULE IS BIGGER THAN RULE SIZE

    if(mRule.size() == 0)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, (mStates - 1));

        for(int i = 0; i < mRuleSize; i++)
            mRule.push_back(distrib(gen));
    } else
    {
        //  check rule size and correct accordingly
        while(mRule.size() < mRuleSize)
            mRule.push_back(0);
    }
}


void CA::setRule(std::vector<int> const& rule_in)
{
    mRule = rule_in;
}


void CA::setRule(const int rule_in)
{

}
