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
                        CA2d(CA::Type type_in,
                            int rad_in = 1,
                            int stat_in = 2,
                            std::vector<int> const& rule = {});

    void                initialize(int size_x_in, int size_y_in, Start t0);
    void                initialize(std::vector<std::vector<int> > const& t0);

    void                generate();

    std::vector<std::vector<int> >
                        getData();
    void                print();
    std::string         str();

protected:
    int                 mDimX;
    int                 mDimY;
    std::vector<std::vector<int> >
                        mData;

    Start               mStart;
};



#endif // ca2d_hpp
