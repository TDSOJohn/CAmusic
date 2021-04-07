#ifndef ca_hpp
#define ca_hpp


#include <vector>
#include <string>



class CA
{
public:
                        /// Constructor that copies rule_in lvalue or rvalue
                        CA(std::vector<int> const& rule_in, int stat_in);
                        /// Constructor that moves rule_in rvalue
                        CA(std::vector<int>&& rule_in, int stat_in);

    virtual void        generate()  = 0;

    virtual void        print()     = 0;
    virtual std::string str()       = 0;

protected:
    std::vector<int>    mRule;
    double              mRuleSize;

    unsigned int        mStates;
    unsigned int        mNeighbrs;
};



#endif //ca_hpp
