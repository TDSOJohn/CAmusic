#include <iostream>

int main()
{
    int size_x = 7;
    int size_y = 4;

    srand(3);

    int **mBuffer;
    mBuffer = new int*[size_x];
    for(int i = 0; i < size_x; i++)
        mBuffer[i] = new int[size_y];

    for(int i = 0; i < size_x; i++)
    {
        for(int j = 0; j < size_y; j++)
            mBuffer[i][j] = rand()%4;
    }

    for(int i = 0; i < size_y; i++)
    {
        for(int j = 0; j < size_x; j++)
            std::cout << mBuffer[j][i];
        std::cout << std::endl;
    }
    return 0;
}
