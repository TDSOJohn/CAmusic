#include "../../include/MIDI/midiToFile.hpp"
#include "../../utilities.hpp"


MidiToFile::MidiToFile():
    mTrack(0), mChannel(0), mInstr(1)
{
    mMidifile       = new smf::MidiFile;
    mMidifile->addTimbre(mTrack, 0, mChannel, mInstr);
}


void MidiToFile::drawData(std::vector<int> data_in)
{
    std::vector<int> keys(ca_to_midi_note(data_in));
    std::vector<int> vel(ca_to_velocity(data_in));

    int tpq         = mMidifile->getTPQ();
    for(int i = 0; i < data_in.size(); i++)
    {
        int start   = i * tpq;
        int end     = (i + 1) * tpq;

        mMidifile->addNoteOn(mTrack, start, mChannel, keys[i], vel[i]);
        mMidifile->addNoteOff(mTrack, end, mChannel, keys[i]);
    }
}


void MidiToFile::saveFile(std::string fn_in)
{
    std::string filename = fn_in + ".mid";
//    mMidifile->sortTracks();
    mMidifile->write(filename);
}
