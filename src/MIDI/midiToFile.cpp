#include "../../include/MIDI/midiToFile.hpp"
#include "../../utilities.hpp"


MidiToFile::MidiToFile():
    mTrack(0), mChannel(0), mInstr(1), mPosition(0)
{
    mMidifile       = new smf::MidiFile;
    mMidifile->addTimbre(mTrack, 0, mChannel, mInstr);
    //  Ticks per quarter note
    mTPQ            = mMidifile->getTPQ();
}


void MidiToFile::drawData(std::vector<int> data_in)
{
    std::vector<int> keys(ca_to_midi_note(data_in));
    std::vector<int> vel(ca_to_velocity(data_in));
    int end;

    for(int i = 0; i < data_in.size(); i++)
    {
        end         = mPosition + mTPQ/4;

        mMidifile->addNoteOn(mTrack, mPosition, mChannel, keys[i], vel[i]);
        mMidifile->addNoteOff(mTrack, end, mChannel, keys[i]);
        mPosition   = end;
    }
}


void MidiToFile::saveFile(std::string fn_in)
{
    std::string filename = fn_in + ".mid";
//    mMidifile->sortTracks();
    mMidifile->write(filename);
}


void MidiToFile::newSheet()
{
    if(mMidifile != NULL)
        delete mMidifile;

    mMidifile       = new smf::MidiFile;
    mMidifile->addTimbre(mTrack, 0, mChannel, mInstr);
    //  Ticks per quarter note (DOES IT CHANGE?)
    mTPQ            = mMidifile->getTPQ();
    mPosition       = 0;
}
