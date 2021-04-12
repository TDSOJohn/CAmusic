#ifndef ca1dgen_hpp
#define ca1dgen_hpp


#include <vector>


#include "CA1d.hpp"



class CA1dgen: public CA1d
{
public:
                        CA1dgen(unsigned int rad_in             = 1,
                                unsigned int stat_in            = 2,
                                std::vector<int> const& rule_in = {});

    void                generate();
};


#endif //ca1dgen_hpp
