#include "../../include/Data/DataAnalyzer.hpp"


std::vector<int> counter(std::vector<int> data_in)
{
    std::vector<int> data_out;

    for(auto& i : data_in)
    {
        while((i + 1) > data_out.size())
            data_out.push_back(0);
        data_out[i]++;
    }
    return data_out;
}


std::vector<std::vector<int> > jumps(std::vector<int> data_in)
{
    std::vector<std::vector<int> > data_out;

    for(int i = 0; i < data_in.size(); i++)
    {
        while((data_in[i] + 1) > data_out.size())
            data_out.push_back({});
        data_out[data_in[i]].push_back(i);
    }
    for(int i = 0; i < data_out.size(); i++)
    {
        for(int j = (data_out[i].size() - 1); j >= 1; j--)
            data_out[i][j] = data_out[i][j] - data_out[i][j-1];
    }
    return data_out;
}
