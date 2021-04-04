#include <vector>
#include <string>

#include "../../midifile/include/MidiFile.h"



class MidiToFile
{
public:
                        MidiToFile();

    void                drawData(std::vector<int> data_in);
    void                saveFile(std::string fn_in);

private:
    smf::MidiFile       *mMidifile;
    int                 mTrack;
    int                 mChannel;
    int                 mInstr;
    int                 mTPQ;

    int                 mPosition;
};
