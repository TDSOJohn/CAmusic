#include "../../include/Data/DataAnalyzer.hpp"

#include <iostream>

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


int harmony(std::vector<int> data_in)
{
    int result_true             = 0;
    std::vector<int> result     = {};
    std::vector<int> group      = {};
    unsigned int curr_group     = 0;
    unsigned int curr_size      = 0;
    unsigned int g1[4]          = {1, 3, 5, 6};
    unsigned int g2[3]          = {2, 4, 6};
    unsigned int g3[3]          = {2, 5, 7};
    unsigned int pause_count    = 0;
    unsigned int g1_count       = 0;
    unsigned int g2_count       = 0;
    unsigned int g3_count       = 0;

    for(auto& i : data_in)
    {
        switch(i)
        {
            case 1:
                group.push_back(1);
                break;
            case 2:
                group.push_back(3);
                break;
            case 3:
                group.push_back(1);
                break;
            case 4:
                group.push_back(2);
                break;
            case 5:
                group.push_back(2);
                break;
            case 6:
                group.push_back(1);
                break;
            case 7:
                group.push_back(3);
                break;
            default:
                group.push_back(0);
                break;
        }
    }
//    std::cout << "\nSingle Line: ";
    for(auto& i : group)
    {
        if(curr_size < 8)
        {

            if(i != 0)
                curr_size++;
            if(i == 1)
                g1_count++;
            else if(i == 2)
                g2_count++;
            else if(i == 3)
                g3_count++;
        }
        if(curr_size >= 8)
        {
            result.push_back(curr_size - (std::max(g1_count, std::max(g2_count, g3_count))));
//            std::cout << result.back() << "____";
            curr_size = g1_count = g2_count = g3_count = 0;
        }
    }
//    std::cout << "\n";
    if(curr_size != 0)
        result.push_back(curr_size - (std::max(g1_count, std::max(g2_count, g3_count))));
        curr_size = g1_count = g2_count = g3_count = 0;
    for(auto& i : result)
        result_true += i;

    return result_true;
}
