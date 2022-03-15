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

    enum Neighborhood
    {
        Moore,
        VonNeumann
    };

public:
                        CA2d(CA::Type type_in,
                            int rad_in = 1,
                            int stat_in = 2,
                            std::vector<int> const& rule = {});

    void                initialize(int size_x_in, int size_y_in, Start t0);
    void                initialize(std::vector<std::vector<int> > const& t0);

    void                setNeighborhoodType(Neighborhood n_in);
    void                generate();

    std::vector<std::vector<int> > getData() { return mData; }

    void                print();

    std::string         str() const;

    friend std::ostream& operator<<(std::ostream& os, const CA2d& ca_out);

protected:
    int                 mDimX;
    int                 mDimY;
    std::vector<std::vector<int> >
                        mData;

    Start               mStart;
    Neighborhood        mNeighborhood;
};

/*

r = 1
n = 5
k = 2

totalistic: sum total is 0 to 5 => total rules = 2^5 = 32

standard:

*/

#endif // ca2d_hpp
