#ifndef dataanalyzer_hpp
#define dataanalyzer_hpp

#include <vector>


/// Result type:
/// std::vector with result[value] == (occurrence of value in data_in)
std::vector<int> counter(std::vector<int> data_in);

/// Result type:
/// every vector is a value, first entry is position of first occurrence
/// then is difference between nth and (n+1)th position of occurrence
std::vector<std::vector<int> > jumps(std::vector<int> data_in);


int harmony(std::vector<int> data_in);

/*
class DataAnalyzer
{
public:
                                    DataAnalyzer();
                                    DataAnalyzer(std::vector<std::vector<int> > const& data_in);

    void                            addData(std::vetor<int> const& data_in);
    std::vector<std::vector<int> >  returnData();
};
*/

#endif //dataanalyzer_hpp
