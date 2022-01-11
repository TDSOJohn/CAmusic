#ifndef midiout_hpp
#define midiout_hpp

#include <cstdlib>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

//  Linux version
#if defined(__LINUX__) || defined(__LINUX) || defined(LINUX)
    #include "rtmidi/RtMidi.h"
#elif __APPLE__
//  macOS version
    #include <RtMidi.h>
#endif


class MIDIout
{
public:
    enum State
    {
        Play,
        Pause,
        Stop
    };
                                /// Constructor
                                MIDIout(int bpm_in = 480);
                                /// MIDIout is non-copyable
                                MIDIout(MIDIout const&) = delete;
                                MIDIout& operator=(MIDIout const&) = delete;

                                ~MIDIout();

    void                        setPattern( std::vector<int> const& notes_in);
    void                        setPattern( std::vector<int> const& notes_in,
                                            std::vector<int> const& vel_in);

    void                        setState(State s_in);


private:
    //  Is this a good way of doing things? tons of mutexes?
    std::vector<std::thread>    mThreads;
    std::mutex                  scoreMutex;
    std::mutex                  stateMutex;
    std::condition_variable     metroCond;

    RtMidiOut                   *mMidiOut;
    std::vector<unsigned char>  mMessage;
    std::vector<int>            mScore;
    std::vector<int>            mVelocity;

    int                         mBpm;
    const int                   mPeriod;

    bool                        mMetronome;

private:
    void                        play();
    void                        pause();
    void                        stop();

    void                        metronome();

    int                         portProbing();
    void                        messageOut( unsigned short status,
                                            unsigned short data1,
                                            unsigned short data2);
};


#endif //midiout_hpp
