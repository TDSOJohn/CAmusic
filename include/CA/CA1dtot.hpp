#ifndef ca1dtot_hpp
#define ca1dtot_hpp


#include <vector>


#include "CA1d.hpp"



class CA1dtot: public CA1d
{
public:
                        CA1dtot(std::vector<int> const& rule_in,
                                unsigned int rad_in,
                                unsigned int stat_in);
                        CA1dtot(std::vector<int>&& rule_in,
                                unsigned int rad_in,
                                unsigned int stat_in);

    void                generate();
};


#endif //ca1dtot_hpp
