#include <iostream>
#include <vector>
#include <algorithm>

#include "include/Data/DataAnalyzer.hpp"


int main()
{
    srand(time(NULL));
    std::vector<int> data = {7,6,4,0,5,2,4,6,2,6,7,7,6,4,1,2,1,1,5};

    std::cout << "DATA:\n";
    for(int i = 0; i < 20; i++)
    {
        data.push_back(rand()%8);
        std::cout << data[i] << "\t";
    }
    std::cout << "\nEND_DATA\n\n";

    int result(harmony(data));
    float entr = entropy(data);
    std::vector<int> compressed = compressor(data);
    int result_c(harmony(compressed));

    std::cout << "\nCompressed array:\n";
    for(auto& i : compressed)
        std::cout << i << "\t";

    std::cout << "\n" << result  << "\t" << result_c << "\n";
    std::cout << entr << "\n\n";

    return 0;
}
