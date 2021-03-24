a.out:
	g++ --std=c++11 sources/CA/CA.cpp \
					sources/CA/CA1d.cpp \
					sources/CA/TotalisticCA.cpp \
					sources/MIDI/MIDIout.cpp \
					utilities.cpp \
					main.cpp \
					-lrtmidi -pthread
