#include "../../include/CA/CA.hpp"


#include <sstream>
#include <iostream>



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

    std::cout << "\n";
    if(mRule.size() == 0)
    {
        std::cout << "RANDOM RULE\n\n";
        for(int i = 0; i < mRuleSize; i++)
            mRule.push_back(rand()%mStates);
    } else
    {
        //  check rule size and correct accordingly
        while(mRule.size() < mRuleSize)
            mRule.push_back(0);
    }

    for(auto i : mRule)
        std::cout << i << "\t";

    std::cout << "\nRule size: " << mRuleSize
            << "\tStates: " << mStates
            << "\tRadius: " << mRadius
            << "\tNeigh: " << mNeighbrs
            << std::endl;
}
