#ifndef ca_hpp
#define ca_hpp


#include <vector>
#include <string>


class CA
{
public:
    enum Type
    {
        Standard,
        Totalistic
    };

public:
                        /// Constructor that copies rule_in lvalue or rvalue
                        CA( Type type_in,
                            unsigned int stat_in,
                            unsigned int rad_in,
                            unsigned int neigh_in,
                            double rule_size_in,
                            std::vector<int> const& rule_in = {});

    virtual void        generate()  = 0;


    void                setRule(std::vector<int> const& rule_in);
    void                setRule(const long long int rule_in);
    std::vector<int>    getRule() const { return mRule; }

    unsigned int        getStates() const { return mStates; }

    unsigned int        getRadius() const { return mRadius; }

    void                setNeighborhood(int n_in) { mNeighbrs = n_in; }

    std::string         getRuleString() const;

    virtual std::string str() const = 0;

protected:
    Type                mType;

    std::vector<int>    mRule;
    double              mRuleSize;

    unsigned int        mStates;
    int                 mRadius;
    unsigned int        mNeighbrs;
};



#endif //ca_hpp
