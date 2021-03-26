#ifndef ca_hpp
#define ca_hpp


#include <vector>



class CA
{
public:
                        /// Constructor that copies rule_in lvalue or rvalue
                        CA(std::vector<int> const& rule_in, int rad_in, int stat_in);
                        /// Constructor that moves rule_in rvalue
                        CA(std::vector<int>&& rule_in, int rad_in, int stat_in);


    virtual void        print()     = 0;

    virtual void        generate()  = 0;

protected:
    int                 mDim;

    std::vector<int>    mRule;
    double              mRuleSize;

    int                 mStates;
    int                 mRadius;
    int                 mNeighbrs;
};



#endif //ca_hpp
