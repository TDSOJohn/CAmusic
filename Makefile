objects = main.o utilities.o ca.o ca1d.o totalisticca.o bmpgenerator.o

flags = --std=c++11 -c
libs = -pthread -lrtmidi

camusic	: $(objects)
	g++ -o camusic $(objects) $(libs)

main.o : main.cpp headers/CA/CA1d.hpp headers/CA/TotalisticCA.hpp headers/MIDI/MIDIout.hpp headers/BMP/BMPgenerator.hpp utilities.hpp
	g++ $(flags) main.cpp
utilities.o : utilities.cpp utilities.hpp
	g++ $(flags) utilities.cpp
ca.o : sources/CA/CA.cpp headers/CA/CA.hpp
	g++ $(flags) sources/CA/CA.cpp
ca1d.o : sources/CA/CA1d.cpp headers/CA/CA1d.hpp headers/CA/CA.hpp utilities.hpp
	g++ $(flags) sources/CA/CA1d.cpp
totalisticca.o : sources/CA/TotalisticCA.cpp headers/CA/TotalisticCA.hpp headers/CA/CA.hpp utilities.hpp
	g++ $(flags) sources/CA/TotalisticCA.cpp
midiout.o : sources/MIDI/MIDIout.cpp headers/MIDI/MIDIout.hpp
	g++ $(flags) sources/MIDI/MIDIout.cpp
bmpgenerator.o : sources/BMP/BMPgenerator.cpp headers/BMP/BMPgenerator.hpp
	g++ $(flags) sources/BMP/BMPgenerator.cpp


.PHONY : clean
clean :
	rm camusic $(objects)
