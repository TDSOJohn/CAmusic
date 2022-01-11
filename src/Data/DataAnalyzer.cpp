#include "Data/DataAnalyzer.hpp"

#include <cmath>


struct Group
{
    unsigned int id;
    unsigned int count;
};


std::vector<int> counter(std::vector<int> const& data_in)
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

std::vector<std::vector<int> > jumps(std::vector<int> const& data_in)
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

int harmony(std::vector<int> const& data_in)
{
    //  Final result
    int result_true             = 0;
    //  Partial results array
    std::vector<int> result     = {};
    //  Vector having the group id as entry
    std::vector<int> group      = {};
    //  Keep track of previous start, end and ratio
    int prev_start              = 0;
    int prev_end                = 0;
    float prev_ratio            = 0.f;
    //  Current and previous group, data and pauses
    Group curr_group{0, 0};
    Group prev_group{0, 0};
    unsigned int curr_size      = 0;
    unsigned int prev_size      = 0;
    unsigned int pause_count    = 0;
    //  Groups occurencies counters
    Group groups[3]{{1, 0}, {2, 0}, {3, 0}};

    group = groupMatch(data_in);

    for(int i = 0; i < group.size(); i++)
    {
//        std::cout << "S";
        //  Save starting point
        if(curr_size == 0)
            prev_start = i;

        if(group[i] != 0)
            curr_size++;
        if(group[i] == 1)
            groups[0].count++;
        else if(group[i] == 2)
            groups[1].count++;
        else if(group[i] == 3)
            groups[2].count++;

        //  If updated counter is better than current_group, copy updated into it
        if((group[i] != 0) && (curr_group.count < groups[group[i] - 1].count))
            curr_group = groups[group[i] - 1];

//        std::cout << group[i] << curr_group.id << "\t";
        if(curr_size >= 4)
        {
//            std::cout << "c>4";
            //  Save previous end when reaching the 4-elements group or
            //  when current element is equal to curr_group.id
            //  If current group changes, shit happens fast
            if((group[i] == curr_group.id) || (curr_size == 4))
            {
                float new_prev_ratio = curr_group.count / ((float)curr_size);
                //  If never updated prev_group or if id of current group hasn't changed and ratio is improved
                if(((prev_group.id == 0) || (curr_group.id == prev_group.id)) && (new_prev_ratio >= prev_ratio))
                {
//                    std::cout << "\n";
                    prev_size = curr_size;
                    prev_group = curr_group;
                    prev_end = i;
                    prev_ratio = new_prev_ratio;
                } else
                {
                    i = prev_end;
                    result.push_back(prev_size - prev_group.count);
//                    std::cout << "\nChoosing " << prev_group.id << " with " << result.back() << "____" << prev_size << "\n";
                    curr_group.id = curr_group.count = 0;
                    prev_group = curr_group;
                    for(int j = 0; j < 3; j++)
                        groups[j].count = 0;
                    curr_size = prev_size = 0;
                    prev_ratio = 0;
                }
            }
        }
//        std::cout << "E";
    }
    if(curr_size != 0)
    {
        //  Sure?
        result.push_back(curr_size - curr_group.count);
//        std::cout << "\nChoosing " << curr_group.id << " with " << result.back() << "____" << curr_size << "\n";
//    } else { std::cout << std::endl; }
}
    for(auto& i : result)
    {
        result_true += i;
//        std::cout << i << "+";
    }

    return result_true;
}

float entropy(std::vector<int> const& data_in)
{
    std::vector<int> temp = std::move(counter(data_in));
    float result = 0.f;
//    std::cout << "\nstates: " << temp.size() << std::endl;

    for(auto& i : temp)
    {
        if(i != 0)
        {
            result += (-1.f) * ((float)i / (float)data_in.size()) * log((float)i / (float)data_in.size());
        }
//        std::cout <<  i << "\t" << data_in.size() << "\t" << log((float)i / (float)data_in.size()) << "\n";
    }
    result *= 2.71828;
    result /= (float)temp.size();

    return result;
}

std::vector<int> compressor(std::vector<int> const& data_in)
{
    std::vector<int> result = {};
    int start_note = data_in[0];

    for(auto& i : data_in)
    {
        if(i != start_note)
        {
            result.push_back(start_note);
            start_note = i;
        }
    }
    result.push_back(data_in[data_in.size() - 1]);
    return result;
}

std::vector<int> groupMatch(std::vector<int> const& data_in)
{
    std::vector<int> group = {};

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
                group.push_back(3);
                break;
            case 6:
                group.push_back(2);
                break;
            case 7:
                group.push_back(3);
                break;
            default:
                group.push_back(0);
                break;
        }
    }
/*    std::cout << "\nGrouped array:\n";
    for(auto& i : group)
        std::cout << i << "\t";
    std::cout << "\n\n";
*/    return group;
}
