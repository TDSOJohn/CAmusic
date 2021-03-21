#ifndef midiout_hpp
#define midiout_hpp


#include <iostream>
#include <cstdlib>
#include <vector>
#include <thread>
#include <mutex>


#include <RtMidi.h>



class MIDIout
{
public:
    enum State
    {
        Play,
        Pause,
        Stop
    };

                                MIDIout(int bpm_in = 120);

    void                        setPattern( std::vector<int>& notes_in);
    void                        setPattern( std::vector<int>& notes_in,
                                            std::vector<int>& vel_in);

    void                        setState(State s_in);

private:
    std::vector<std::thread>    mThreads;
    std::mutex                  scoreMutex;

    RtMidiOut                   *mMidiOut;
    std::vector<unsigned char>  mMessage;
    std::vector<int>            mScore;
    std::vector<int>            mVelocity;

    int                         mBpm;
    int                         mPeriod;

private:
    void                        play();
    void                        pause();
    void                        stop();

    void                        portProbing();
    void                        messageOut( unsigned short status,
                                            unsigned short data1,
                                            unsigned short data2);
};


#endif //midiout_hpp
