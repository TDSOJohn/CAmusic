#ifndef ca_hpp
#define ca_hpp


#include <iostream>
#include <vector>



class CA
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
                        CA(std::vector<int>& rule_in, int rad_in, int stat_in);

    void                initialize(int size_in, Start t0);
    void                initialize(std::vector<int>& t0);

    std::vector<int>    getData();
    void                print();

    void                generate();

protected:
    std::vector<int>    data;
    int                 dim;

    std::vector<int>    rule;
    int                 states;
    int                 radius;
    int                 neighbrs;
};



#endif //ca_hpp
