#ifndef ca1dtot_hpp
#define ca1dtot_hpp


#include <vector>


#include "CA1d.hpp"



class CA1dtot: public CA1d
{
public:
                        CA1dtot(unsigned int rad_in             = 1,
                                unsigned int stat_in            = 2,
                                std::vector<int> const& rule_in = {});

    void                generate();
};


#endif //ca1dtot_hpp
