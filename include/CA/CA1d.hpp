#ifndef ca1d_hpp
#define ca1d_hpp


#include "CA/CA.hpp"

#include <vector>
#include <string>


class CA1d : public CA
{
public:
    enum Start
    {
        Random,
        Middle,
        Left,
        Other
    };

public:
                        /// Constructor that copies rule_in lvalue or rvalue
                        /// parameters:
                        /// cellular automata type (standard or totalistic),
                        /// radius, number of states,
                        /// std::vector<int> containing the rule
                        CA1d(CA::Type ca_type                = Type::Standard,
                             unsigned int rad_in             = 1,
                             unsigned int stat_in            = 2,
                             std::vector<int> const& rule_in = {});

    void                initialize(unsigned int size_in, Start t0);
    void                initialize(std::vector<int> const& t0);

    void                generate();

    bool                isStatic() const;

    std::vector<int>    getData() const;
    std::string         str() const;

    int getType() {return mType;}
    int getStart() {return mStart;}

    friend std::ostream& operator<<(std::ostream& os, const CA1d& ca_out);

protected:
    int                 mDim;
    std::vector<int>    mData;

    // Might be useless, let's keep it for now and see
    Start               mStart;
};



#endif //ca1d_hpp
