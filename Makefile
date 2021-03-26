INCL = 	headers/CA/CA.hpp headers/CA/CA1d.hpp headers/CA/TotalisticCA.hpp \
		headers/MIDI/MIDIout.hpp

OBJ	=	sources/CA/CA.cpp \
		sources/CA/CA1d.cpp \
		sources/CA/TotalisticCA.cpp \
		sources/MIDI/MIDIout.cpp

UTIL =	utilities.cpp utilities.hpp

LIBS =	-lrtmidi -pthread

a.out: $(INCL) $(OBJ) $(UTIL) main.cpp
	g++ --std=c++11 $(OBJ) utilities.cpp main.cpp $(LIBS)
