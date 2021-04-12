#ifndef ca2d_hpp
#define ca2d_hpp


#include <vector>


#include "CA.hpp"



class CA2d : public CA
{
public:
    enum Start
    {
        Random,
        Middle,
        Corner
    };


public:
                        CA2d(unsigned int rad_in,
                             unsigned int stat_in,
                             std::vector<int> const& rule);

    void                initialize(unsigned int size_in, Start t0);
    void                initialize(std::vector<std::vector<int> > const& t0);
    void                initialize(std::vector<std::vector<int> >&& t0);

    virtual void        generate()  = 0;

    std::vector<std::vector<int> >
                        getData();
    void                print();
    std::string         str();

protected:
    int                 mDim;
    std::vector<int>    mData;

    int                 mRadius;

    Start               mStart;
};



#endif // ca2d_hpp
