# library object files
lobjects = utilities.o CA.o CA1d.o BMPgenerator.o midiToFile.o DataAnalyzer.o Visualizer.o
# standalone executable object files
oobjects = main.o
# instrument executable object files
iobjects = MIDIout.o


# g++ compiler flags (no linker, use c++11)
flags 	= --std=c++11 -c
# libs to use during linking (thread, rtmidi, midifile, ncurses)
libs 	= -pthread -lmidifile -lncurses -Lmidifile/lib
ilibs = -lrtmidi

# search for files in these paths
vpath %.hpp include/CA:include/BMP:include/MIDI:include:include/Data
vpath %.cpp src:src/CA:src/BMP:src/MIDI:src/Data

# main target to make
camusic	: $(lobjects) $(oobjects)
	g++ -o camusic $(lobjects) $(oobjects) $(libs)

# single object files to make
main.o : main.cpp
	g++ $(flags) main.cpp
Visualizer.o : Visualizer.cpp Visualizer.hpp CA1d.hpp MIDIout.hpp midiToFile.hpp BMPgenerator.hpp utilities.hpp
	g++ $(flags) src/Visualizer.cpp

utilities.o : utilities.cpp utilities.hpp
	g++ $(flags) utilities.cpp

CA.o : CA.cpp CA.hpp
	g++ $(flags) src/CA/CA.cpp
CA1d.o : CA1d.hpp CA1d.cpp CA.hpp
	g++ $(flags) src/CA/CA1d.cpp

MIDIout.o : MIDIout.cpp MIDIout.hpp
	g++ $(flags) src/MIDI/MIDIout.cpp
midiToFile.o : midiToFile.cpp midiToFile.hpp
	g++ $(flags) src/MIDI/midiToFile.cpp

BMPgenerator.o : BMPgenerator.cpp BMPgenerator.hpp
	g++ $(flags) src/BMP/BMPgenerator.cpp

DataAnalyzer.o : DataAnalyzer.cpp DataAnalyzer.hpp
	g++ $(flags) src/Data/DataAnalyzer.cpp


lib : $(lobjects)
	ar rcs libca.a $(lobjects)


# phony in order to have a clean rm even when some files are missing
.PHONY : clean

clean :
	rm $(lobjects) $(oobjects)
