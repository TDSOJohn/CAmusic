#ifndef ca_hpp
#define ca_hpp


#include <vector>
#include <string>



class CA
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
                        CA(std::vector<int> const& rule_in, int rad_in, int stat_in);
                        /// Constructor that moves rule_in rvalue
                        CA(std::vector<int>&& rule_in, int rad_in, int stat_in);

    void                initialize(int size_in, Start t0);
    void                initialize(std::vector<int> const& t0);
    void                initialize(std::vector<int>&& t0);

    virtual void        generate()  = 0;

    std::vector<int>    getData();
    void                print();
    std::string         str();

protected:
    int                 mDim;
    std::vector<int>    mData;

    std::vector<int>    mRule;
    double              mRuleSize;

    int                 mStates;
    int                 mRadius;
    int                 mNeighbrs;

    Start               mStart;
};



#endif //ca_hpp
