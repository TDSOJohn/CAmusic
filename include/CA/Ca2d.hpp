#ifndef ca2d_hpp
#define ca2d_hpp


class CA2d : public CA
{
public:
    CA2d(std::vector<int> const& rule, unsigned int states, unsigned int radius);
    CA2d(std::vector<int>&& rule, unsigned int states, unsigned int radius);

protected:
    unsigned int            mRadius;
};



#endif // ca2d_hpp
