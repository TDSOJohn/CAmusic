#ifndef ca_hpp
#define ca_hpp


#include <vector>
#include <string>



class CA
{
public:
                        /// Constructor that copies rule_in lvalue or rvalue
                        CA( unsigned int stat_in,
                            unsigned int rad_in,
                            unsigned int neigh_in,
                            double rule_size_in,
                            std::vector<int> const& rule_in = {});

    virtual void        generate()  = 0;

    virtual std::string str()       = 0;

protected:
    std::vector<int>    mRule;
    double              mRuleSize;

    unsigned int        mStates;
    int                 mRadius;
    unsigned int        mNeighbrs;
};



#endif //ca_hpp
