#include "../../headers/CA/CA.hpp"



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
