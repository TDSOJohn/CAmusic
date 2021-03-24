#ifndef ca1d_hpp
#define ca1d_hpp


#include <vector>


#include "CA.hpp"



class CA1d: public CA
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
                        CA1d(std::vector<int>& rule_in, int rad_in, int stat_in);

    void                initialize(int size_in, Start t0);
    void                initialize(std::vector<int>& t0);

    std::vector<int>    getData();
    void                print();

    void                generate();

protected:
    std::vector<int>    mData;
};



#endif //ca1d_hpp
