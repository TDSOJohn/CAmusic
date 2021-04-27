#include <vector>
#include <string>

#include "../../midifile/include/MidiFile.h"



class MidiToFile
{
public:
                        MidiToFile();

    void                drawData(std::vector<int> data_in, int octave);

    void                saveFile(std::string fn_in);
    void                newFile();

private:
    smf::MidiFile       *mMidifile;
    int                 mTrack;
    int                 mChannel;
    int                 mInstr;
    int                 mTPQ;

    int                 mPosition;

private:
    void                noteOut(int note, int velocity, int start, int end);
    void                drawLine(std::vector<int> note_in);
    void                drawLine(std::vector<int> note_in, std::vector<int> vel_in);
};
