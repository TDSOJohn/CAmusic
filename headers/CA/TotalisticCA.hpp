#ifndef totalisticca_hpp
#define totalisticca_hpp


#include <vector>


#include "CA.hpp"



class TotalisticCA: public CA
{
public:
    enum Start
    {
        Random,
        Middle,
        Left,
        Right
    };


public:
                        TotalisticCA(std::vector<int> const& rule_in, int rad_in, int stat_in);
                        TotalisticCA(std::vector<int>&& rule_in, int rad_in, int stat_in);

    void                initialize(int size_in, Start t0);
    void                initialize(std::vector<int>& t0);

    void                print();

    void                generate();

protected:
    std::vector<int>    mData;
};


#endif //totalisticca_hpp
