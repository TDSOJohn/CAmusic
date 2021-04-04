#ifndef ca1d_hpp
#define ca1d_hpp


#include <vector>


#include "CA.hpp"



class CA1d: public CA
{
public:
                        CA1d(std::vector<int> const& rule_in, int rad_in, int stat_in);
                        CA1d(std::vector<int>&& rule_in, int rad_in, int stat_in);

    void                generate();
};



#endif //ca1d_hpp
