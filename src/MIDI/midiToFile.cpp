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


void MidiToFile::drawData(std::vector<int> data_in, int octave)
{
    drawLine(ca_to_midi_note(data_in, octave));
}


void MidiToFile::drawChord(std::vector<int> data_in, int states)
{
    int size = data_in.size();
    if(size <= 127)
    {
        for(int i = 0; i < size; i++)
        {
            if(data_in[i] != 0)
            {
//                std::cout << i << "\t" << i + ((127 - size) / 2) << "\t" << data_in[i] * (127 / (states - 1)) << std::endl;
                noteOut (i + ((127 - size) / 2),
                        (data_in[i] * (127 / (states - 1))),
                        mPosition,
                        mPosition + mTPQ);
            }
        }
        mPosition += mTPQ;
    }
    mMidifile->sortTracks();
}


void MidiToFile::saveFile(std::string fn_in)
{
    std::string filename = "results/" + fn_in + ".mid";
//    mMidifile->sortTracks();
    mMidifile->write(filename);
}


void MidiToFile::newFile()
{
    if(mMidifile != NULL)
        delete mMidifile;

    mMidifile       = new smf::MidiFile;
    mMidifile->addTimbre(mTrack, 0, mChannel, mInstr);
    //  Ticks per quarter note (DOES IT MATTER?)
    mTPQ            = mMidifile->getTPQ();
    mPosition       = 0;
}


void MidiToFile::noteOut(int note, int velocity, int start, int end)
{
    if(note != 0)
    {
        mMidifile->addNoteOn(mTrack, start, mChannel, note, velocity);
        mMidifile->addNoteOff(mTrack, end, mChannel, note);
    }
}


void MidiToFile::drawLine(std::vector<int> note_in)
{
    int start       = mPosition;
    int end         = mPosition + (mTPQ / 4);
    int start_note  = note_in[0];

    for(int i = 1; i < note_in.size(); i++)
    {
        if(note_in[i] != start_note)
        {
            noteOut(start_note, 90, start, end);
            start = end;
            end += mTPQ / 4;
            start_note = note_in[i];
        } else
            end += mTPQ / 4;
    }
    noteOut(start_note, 90, start, end);
    mPosition       = end;
}


void MidiToFile::drawLine(std::vector<int> note_in, std::vector<int> vel_in)
{
    int start       = mPosition;
    int end         = mPosition + (mTPQ / 4);
    int start_note  = note_in[0];

    for(int i = 1; i < note_in.size(); i++)
    {
        if(note_in[i] != start_note)
        {
            noteOut(start_note, 90, start, end);
            start = end;
            end += mTPQ / 4;
            start_note = note_in[i];
        } else
            end += mTPQ / 4;
    }
    noteOut(start_note, 90, start, end);
    mPosition       = end;
}
