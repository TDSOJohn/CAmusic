#include "../../headers/CA/CA.hpp"


#include <sstream>



CA::CA(std::vector<int> const& rule_in, int rad_in, int stat_in):
    mRule(rule_in),
    mRadius(rad_in),
    mStates(stat_in)
{}


CA::CA(std::vector<int>&& rule_in, int rad_in, int stat_in):
    mRule(std::move(rule_in)),
    mRadius(rad_in),
    mStates(stat_in)
{}


std::string CA::str()
{
    std::stringstream ss;
    ss << "results/";
    ss << "r";

    if(mRule.size() < 248)
    {
        for(auto i: mRule)
            ss << i;    
    }
//    std::copy(mRule.begin(), mRule.end(), std::ostream_iterator<std::string>(ss));
    ss << "k" << mRadius;
    ss << "s" << mStates;
    ss << ".bmp";

    return ss.str();
}
