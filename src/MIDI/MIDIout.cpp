#include "../../include/MIDI/MIDIout.hpp"


#include <chrono>


// Note On : status 144
// Note Off: status 128


MIDIout::MIDIout(int bpm_in):   mBpm(bpm_in),
                                mPeriod(60000.0 / mBpm),
                                mMetronome(false)
{
    try
    {
        mMidiOut = new RtMidiOut();
    } catch(RtMidiError &error)
    {
        error.printMessage();
        // goto cleanup function
    }

    // Check all ports and open user-selected one
    mMidiOut->openPort(portProbing());

    // Program change: 192, 1 (classic piano)
    mMessage.push_back(192);
    mMessage.push_back(1);
    mMidiOut->sendMessage(&mMessage);

    // Control Change: 176, 7, 100 (volume up to 100)
    messageOut(176, 7, 100);
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
        if(!mMetronome)
        {
            mMetronome = true;
            //  Start metronome and detach
            mThreads.push_back(std::thread(&MIDIout::metronome, this));
            mThreads.back().detach();
        }
        //  Start midiout output and wait for completion
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

        std::unique_lock<std::mutex> lk(stateMutex);
        metroCond.wait(lk);
        lk.unlock();

        messageOut(128, temp_note, 40);
    }
}


void MIDIout::pause()
{

}


void MIDIout::stop()
{

}


void MIDIout::metronome()
{
    auto x = std::chrono::steady_clock::now();
    int counter = 0;
    int sixteen = mPeriod/4;
    while(true)
    {
        x += std::chrono::milliseconds(mPeriod);
        std::this_thread::sleep_until(x);

        std::lock_guard<std::mutex> lg(stateMutex);
        metroCond.notify_all();
        //if(!(counter%4))
            std::cout << "\a" << std::flush;
        counter++;
    }
}


int MIDIout::portProbing()
{
    int nPorts = mMidiOut->getPortCount();
    int port_in = 0;
    std::string portName;

    do
    {
        std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
        for (unsigned int i = 0; i<nPorts; i++)
        {
            try
            {
                portName = mMidiOut->getPortName(i);
            }
            catch (RtMidiError &error)
            {
                error.printMessage();
            }
            std::cout << "  Output Port #" << i << ": " << portName << '\n';
        }
        std::cout << "Select the port number:\t";
        std::cin >> port_in;
    } while(port_in >= nPorts);

    return port_in;
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
