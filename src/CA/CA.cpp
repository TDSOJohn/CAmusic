#include "../../include/CA/CA.hpp"


#include <sstream>



CA::CA(std::vector<int> const& rule_in, int stat_in):
    mRule(rule_in),
    mStates(stat_in)
{}


CA::CA(std::vector<int>&& rule_in, int stat_in):
    mRule(std::move(rule_in)),
    mStates(stat_in)
{}
