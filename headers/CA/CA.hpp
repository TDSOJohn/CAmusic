#ifndef ca_hpp
#define ca_hpp


#include <vector>



class CA
{
public:
                        CA(std::vector<int>& rule_in, int rad_in, int stat_in);
CA(std::vector<int>&& rule_in, int rad_in, in stat_in);


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
