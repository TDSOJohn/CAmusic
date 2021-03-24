#ifndef totalisticca_hpp
#define totalisticca_hpp


#include <vector>


#include "CA.hpp"



class TotalisticCA: public CA
{
public:
                        TotalisticCA(std::vector<int>& rule_in, int rad_in, int stat_in);

    void                print();

    void                generate();

protected:
    std::vector<int>    mData;
};


#endif //totalisticca_hpp
