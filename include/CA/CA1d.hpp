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
                        CA1d(unsigned int rad_in = 1,
                             unsigned int stat_in = 2,
                             double rule_size_in = 8,
                             std::vector<int> const& rule_in = {});


    void                initialize(unsigned int size_in, Start t0);
    void                initialize(std::vector<int> const& t0);
    void                initialize(std::vector<int>&& t0);

    virtual void        generate()  = 0;

    std::vector<int>    getData();
    std::string         str();

    friend std::ostream& operator<<(std::ostream& os, const CA1d& ca_out);

protected:
    int                 mDim;
    std::vector<int>    mData;

    Start               mStart;
};



#endif //ca1d_hpp
