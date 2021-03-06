#ifndef dataanalyzer_hpp
#define dataanalyzer_hpp

#include <vector>


/// Result type:
/// std::vector with result[value] == (occurrence of value in data_in)
std::vector<int> counter(std::vector<int> const& data_in);

/// Result type:
/// every vector is a value, first entry is position of first occurrence
/// then is difference between nth and (n+1)th position of occurrence
std::vector<std::vector<int> > const& jumps(std::vector<int> data_in);

/// Result type:
/// int rappresenting the sum of all notes
/// in every group of 8 not belonging to the chord
int harmony(std::vector<int> const& data_in);

/// Result type:
/// float rappresenting diversity, with 0 being static and 1 being chaos
float entropy(std::vector<int> const& data_in);

/// Result type:
/// vector without adjacent same-value cells
std::vector<int> compressor(std::vector<int> const& data_in);

/// Result type:
/// vector with every value changed to the group it belongs to
std::vector<int> groupMatch(std::vector<int> const& data_in);

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
