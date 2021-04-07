# object files
objects = main.o utilities.o ca.o ca1d.o ca1dgen.o ca1dtot.o bmpgenerator.o midiout.o miditofile.o

# g++ compiler flags (no linker, use c++11)
flags 	= --std=c++11 -c
# libs to use during linking (thread library, rtmidi library, midifile library)
libs 	= -pthread -lrtmidi -lmidifile -Lmidifile/lib

# search for files in these paths
vpath %.hpp include/CA:include/BMP:include/MIDI
vpath %.cpp src/CA:src/BMP:src/MIDI

# main target to make
camusic	: $(objects)
	g++ -o camusic $(objects) $(libs)

# single object files to make
main.o : main.cpp CA1d.hpp CA1dgen.hpp CA1dtot.hpp MIDIout.hpp midiToFile.hpp BMPgenerator.hpp utilities.hpp
	g++ $(flags) main.cpp
utilities.o : utilities.cpp utilities.hpp
	g++ $(flags) utilities.cpp

ca.o : CA.cpp CA.hpp
	g++ $(flags) src/CA/CA.cpp
ca1d.o : CA1d.hpp CA1d.cpp CA.hpp
	g++ $(flags) src/CA/CA1d.cpp
ca1dgen.o : CA1dgen.cpp CA1dgen.hpp CA.hpp utilities.hpp
	g++ $(flags) src/CA/CA1dgen.cpp
ca1dtot.o : CA1dtot.cpp CA1dtot.hpp CA.hpp utilities.hpp
	g++ $(flags) src/CA/CA1dtot.cpp

midiout.o : MIDIout.cpp MIDIout.hpp
	g++ $(flags) src/MIDI/MIDIout.cpp
miditofile.o : midiToFile.cpp midiToFile.hpp
	g++ $(flags) src/MIDI/midiToFile.cpp

bmpgenerator.o : BMPgenerator.cpp BMPgenerator.hpp
	g++ $(flags) src/BMP/BMPgenerator.cpp

# phony in order to have a clean rm even when some files are missing
.PHONY : clean
clean :
	rm camusic $(objects)




#	g++ try.cpp --std=c++11 -lmidifile -Lmidifile/lib
