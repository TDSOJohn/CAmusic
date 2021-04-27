#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../include/CA/CA1d.hpp"

#include "../include/MIDI/midiToFile.hpp"
#include "../include/BMP/BMPgenerator.hpp"
#include "../include/Data/DataAnalyzer.hpp"





class Analyzer
{
public:
    Analyzer() {}

    void run()
    {
        int r;

        for(int i = 0; i < 1000; i++)
        {
//            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%5000));
            newCA();
            newBMP();
            newMTF();
            r = generate(1, 1);
            if(r < 102)
            {
                std::cout << "Found!" << std::endl;
                save(r);
                std::cout << "\a" << std::flush;
            }
        }
    }


private:
    void newCA()
    {
        if(ca1d != NULL)
        {
            delete ca1d;
            ca1d = NULL;
        }

        ca1d = new CA1d(mType, radius, states);
        ca1d->initialize(size_x, start);
    }

    void newBMP()
    {
        if(bmp_p != NULL)
        {
            delete bmp_p;
            bmp_p = NULL;
        }
        bmp_p = new BMPgenerator(size_x * scaling, size_y * scaling, scaling);
    }


    void newMTF()
    {
        if(mtf_p != NULL)
        {
            delete mtf_p;
        }
        mtf_p = new MidiToFile();
    }


    float generate(bool bmp, bool mtf)
    {
        float result    = 0;
        float e         = 0;
        if(bmp)
        {
            bmp_p->newFile(0);
            bmp_p->drawData(ca1d->getData(), 0, states);
        }
        if(mtf)
        {
            mtf_p->newFile();
            mtf_p->drawData(ca1d->getData(), 3);
        }

        for(int i = 1; i < size_y; i++)
        {
            ca1d->generate();
            if(bmp)
                bmp_p->drawData(ca1d->getData(), i, states);
            if(mtf)
                mtf_p->drawData(ca1d->getData(), 3);
            if(i >= 64)
            {
                float h = harmony(ca1d->getData());
                e       += entropy(ca1d->getData());
                result  += h;
//                std::cout << h << "\t" << e << "\t" << result << "--||--";
            }
        }
        e /= (size_y - 64);
//        std::cout << e << std::endl;

        if(e < 0.3)
        {
            std::cout << "\nENTROPY TOO LOW\n\n";
            return 999;
        }
        return result;
    }

    // 64 * (80 - 64) = 16^2 * 4 = 1024

    void save(int r_in)
    {
        std::string name = "results/h_" + std::to_string(r_in);
        name += ca1d->str();
//        std::cout <<  "\n" << name << "\n";
        mtf_p->saveFile(name);
        //  CHANGE TO SAVEFILE()
        bmp_p->saveFile(name);
    }

private:
    int                                 states = 8;
    int                                 radius = 2;

    //  Used for screen output
    unsigned int                        size_x = 64;
    unsigned int                        size_y = 80;

    CA1d::Start                         start = CA1d::Start::Random;
    CA1d::Type                          mType = CA1d::Type::Totalistic;
    int                                 scaling = 20;

    CA1d*                               ca1d = NULL;

    BMPgenerator*                       bmp_p = NULL;
    MidiToFile*                         mtf_p = NULL;
};


int main()
{
    srand(time(NULL));
    std::vector<std::thread> mThreads;
    std::vector<Analyzer> mAnal;
    const unsigned int conc(std::thread::hardware_concurrency());


    for(int i = 0; i < conc; i++)
    {
        mAnal.push_back(Analyzer());
        mThreads.push_back(std::thread(&Analyzer::run, mAnal[i]));
        mThreads[i].detach();
    }

    std::this_thread::sleep_for(std::chrono::seconds(60));

    return 0;
}
