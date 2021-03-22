#include "../headers/MIDIout.hpp"


#include <chrono>


// Note On : status 144
// Note Off: status 128


MIDIout::MIDIout(int bpm_in):   mBpm(bpm_in),
                                mPeriod(60000.0 / mBpm)
{
    mMidiOut = new RtMidiOut();
    unsigned int nPorts = mMidiOut->getPortCount();

    if(nPorts == 0)
    {
        std::cout << "No ports available!\n\n";
        delete mMidiOut;
        // Inserire funzione di cleanup
    } else
    {
        // Open first available port
        mMidiOut->openPort(0);

        // Program change: 192, 1 (classic piano)
        mMessage.push_back(192);
        mMessage.push_back(1);
        mMidiOut->sendMessage(&mMessage);

        // Control Change: 176, 7, 100 (volume up to 100)
        messageOut(176, 7, 100);
    }
}


MIDIout::~MIDIout()
{
    for(int i = 0; i < 127; i++)
        messageOut(128, i, 40);
}


void MIDIout::setPattern(std::vector<int>& notes_in)
{
    scoreMutex.lock();
        mScore      = notes_in;
    scoreMutex.unlock();
}


void MIDIout::setPattern(std::vector<int>& notes_in, std::vector<int>& vel_in)
{
    scoreMutex.lock();
        mScore      = notes_in;
        mVelocity   = vel_in;
    scoreMutex.unlock();
}


void MIDIout::setState(State s_in)
{
    if(s_in == State::Play)
    {
        mThreads.push_back(std::thread(&MIDIout::play, this));
        mThreads.back().join();
    }
}


void MIDIout::play()
{
    int score_dim = 1;
    int temp_note = 0;
    int temp_vel = 90;

    for(int i = 0; i < score_dim; i++)
    {
        scoreMutex.lock();
            score_dim = mScore.size();
            temp_note = mScore[i];
            if(mVelocity.size() == mScore.size())
                temp_vel = mVelocity[i];
            else
                temp_vel = 90;
        scoreMutex.unlock();

        if(temp_note != 0)
            messageOut(144, temp_note, temp_vel);
        std::this_thread::sleep_for(std::chrono::milliseconds(mPeriod));
        messageOut(128, temp_note, 40);
    }
}


void MIDIout::pause()
{

}


void MIDIout::stop()
{

}


void MIDIout::portProbing()
{

}


void MIDIout::messageOut(   unsigned short status,
                            unsigned short data1,
                            unsigned short data2)
{
    while(mMessage.size() < 3)
        mMessage.push_back(0);

    mMessage[0] = status;
    mMessage[1] = data1;
    mMessage[2] = data2;

    mMidiOut->sendMessage(&mMessage);
}

/*
for(int i = 0; i < 20; i++)
{
    note = rand()%20 + 45;
    messageOut(144, note, 90);
    std::cout << "\t\t" << note << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    messageOut(128, note, 40);
}
*/
