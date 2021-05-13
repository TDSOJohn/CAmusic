caMusic - C++ Cellular Automata to media library
================================================

Download with:
```bash
git clone https://github.com/TDSOJohn/caMusic
```

Compile executable visualizer with:
```bash
make
```

Compile library with:
```bash
make lib
```


Clean with:
```bash
make clean
```

Dependencies:
-------------

<a href="https://github.com/thestk/rtmidi"> RtMidi </a> for MIDI output

<a href="https://github.com/craigsapp/midifile"> MidiFile </a> for MIDI files creation

<a href="https://github.com/marc-q/libbmp"> libbmp </a> for bitmap output

The Visualizer GUI uses <a href="https://invisible-island.net/ncurses/">ncurses</a>. This is not needed by the caMusic library.


usage:
------
```bash
make
./camusic
```
A terminal-based interface will appear.
The following commands are supported: </br>
n - randomly selects a new rule with the set states and radius.</br>
r, m, l - restart simulation using the same rule but with a single 1 cell inside an all 0 array. R puts it at the 0 position, m at the middle of the array and l at the last element (left of the screen).</br>
p - open the preferences panel.



g++ -L. -lca --std=c++11 automatic/crawler.cpp  -pthread -lrtmidi -lmidifile -lncurses -Lmidifile/lib

g++ --std=c++11 try_2.cpp src/Data/DataAnalyzer.cpp -pthread
