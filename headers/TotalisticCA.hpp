#ifndef totalisticca_hpp
#define totalisticca_hpp


#include "CA.hpp"



class TotalisticCA: public CA
{
public:
    TotalisticCA(std::vector<int>& rule_in, int rad_in, int stat_in);

    void generate();
};


#endif //totalisticca_hpp
