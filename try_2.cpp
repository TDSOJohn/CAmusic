#include <iostream>
#include <vector>

#include "include/Data/DataAnalyzer.hpp"



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

/// Result type:
/// every vector is a value, first entry is first position
/// then is difference between nth and (n+1)th position
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


std::vector<int> harmony(std::vector<int> data_in)
{
    std::vector<int> result     = {};
    unsigned int curr_group     = 0;
    unsigned int curr_size      = 0;
    unsigned int g1[4]          = {1, 3, 5, 6};
    unsigned int g2[3]          = {2, 4, 6};
    unsigned int g3[3]          = {2, 5, 7};

    for(auto& i : data_in)
    {
        switch(i)
        {
            case 1:
                result.push_back(1);
                break;
            case 2:
                result.push_back(6);
                break;
            case 3:
                result.push_back(1);
                break;
            case 4:
                result.push_back(2);
                break;
            case 5:
                result.push_back(5);
                break;
            case 6:
                result.push_back(4);
                break;
            case 7:
                result.push_back(3);
                break;
            default:
                result.push_back(0);
                break;
        }
    }
    return result;
}


int main()
{
    srand(time(NULL));
    std::vector<int> data;

    std::cout << "DATA:\n";
    for(int i = 0; i < 20; i++)
    {
        data.push_back(rand()%8);
        std::cout << data[i] << "\t";
    }
    std::cout << "\nEND_DATA\n\n";

    std::vector<int> result(std::move(harmony(data)));

    for(auto& i : result)
    {
        std::cout << i << "\t";
    }
    std::cout << "\n";

    return 0;
}
