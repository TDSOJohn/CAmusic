#ifndef ca1d_hpp
#define ca1d_hpp


#include <vector>
#include <string>

#include "CA.hpp"



class CA1d : public CA
{
public:
    enum Start
    {
        Random,
        Middle,
        Left,
        Right,
        Other
    };

public:
                        /// Constructor that copies rule_in lvalue or rvalue
                        CA1d(std::vector<int> const& rule_in,
                             unsigned int rad_in,
                             unsigned int stat_in);
                        /// Constructor that moves rule_in rvalue
                        CA1d(std::vector<int>&& rule_in,
                             unsigned int rad_in,
                             unsigned int stat_in);

    void                initialize(unsigned int size_in, Start t0);
    void                initialize(std::vector<int> const& t0);
    void                initialize(std::vector<int>&& t0);

    virtual void        generate()  = 0;

    std::vector<int>    getData();
    void                print();
    std::string         str();

protected:
    int                 mDim;
    std::vector<int>    mData;

    int                 mRadius;

    Start               mStart;
};



#endif //ca1d_hpp
