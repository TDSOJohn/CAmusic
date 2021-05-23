# PREFIX is environment variable, but if it is not set, then set to default value
ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

# core library object files
coreobjects = utilities.o CA.o CA1d.o CA2d.o
# library object files
lobjects = BMPgenerator.o midiToFile.o DataAnalyzer.o
# standalone executable object files
oobjects = main.o Visualizer.o
# instrument executable object files
iobjects = MIDIout.o

# core headers used to install in prefix/include
coreheaders = utilities.hpp include/CA/CA.hpp include/CA/CA1d.hpp include/CA/CA2d.hpp

# g++ compiler flags (use c++11, no linker)
flags 	= --std=c++11 -c
# libs to use during linking (thread, rtmidi, midifile, ncurses)
libs 	= -pthread -lmidifile -lncurses -lgmp -Lmidifile/lib
ilibs 	= -lrtmidi

objfold = obj

# search for files in these paths
vpath %.hpp include/CA:include/BMP:include/MIDI:include:include/Data
vpath %.cpp src:src/CA:src/BMP:src/MIDI:src/Data

# main target to make
camusic	: $(coreobjects) $(lobjects) $(oobjects)
	g++ -o $@ $^ $(libs)

# single object files to make
main.o : main.cpp
	g++ $(flags) $<
Visualizer.o : Visualizer.cpp Visualizer.hpp CA1d.hpp MIDIout.hpp midiToFile.hpp BMPgenerator.hpp utilities.hpp
	g++ $(flags) $<

utilities.o : utilities.cpp utilities.hpp
	g++ $(flags) $<

CA.o : CA.cpp CA.hpp utilities.hpp
	g++ $(flags) $<
CA1d.o : CA1d.cpp CA1d.hpp CA.hpp utilities.hpp
	g++ $(flags) $<
CA2d.o : CA2d.cpp CA2d.hpp
	g++ $(flags) $<

MIDIout.o : MIDIout.cpp MIDIout.hpp
	g++ $(flags) $<
midiToFile.o : midiToFile.cpp midiToFile.hpp utilities.hpp
	g++ $(flags) $<

BMPgenerator.o : BMPgenerator.cpp BMPgenerator.hpp
	g++ $(flags) $<

DataAnalyzer.o : DataAnalyzer.cpp DataAnalyzer.hpp
	g++ $(flags) $<


lib : $(coreobjects) $(lobjects)
	ar rcs libca.a $^

core : $(coreobjects)
	ar rcs libcacore.a $^

# copy libcacore.a inside prefix/lib and core headers inside prefix/include/cacore
install : core
	install -m 644 libcacore.a $(DESTDIR)$(PREFIX)/lib/
	mkdir $(DESTDIR)$(PREFIX)/include/cacore
	install -m 644 $(coreheaders) $(DESTDIR)$(PREFIX)/include/cacore/


# phony in order to have a clean rm even when some files are missing
.PHONY : clean

clean :
	rm $(coreobjects) $(lobjects) $(oobjects)
