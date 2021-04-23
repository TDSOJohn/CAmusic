caMusic - C++ Cellular Automata to media library
================================================

Download with:
```bash
git clone https://github.com/TDSOJohn/caMusic
```

compile with:
```bash
make
```

clean with:
```bash
make clean
```

Dependencies:
-------------

<a href="https://github.com/thestk/rtmidi"> RtMidi </a>

<a href="https://github.com/craigsapp/midifile"> MidiFile </a>


usage:
------
```bash
make lib
g++ -L. -lca --std=c++11 automatic/crawler.cpp  -pthread -lrtmidi -lmidifile -lncurses -Lmidifile/lib
```
