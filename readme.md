caMusic - C++ Cellular Automata to media library
================================================

Download with:
```bash
git clone https://github.com/TDSOJohn/CAmusic --recurse-submodules
```

Compile executable visualizer with:
```bash
cmake -S . -B build
cmake --build build
```

This creates a camusic executable inside the ```build/``` directory


Dependencies:
-------------

<a href="https://github.com/thestk/rtmidi"> RtMidi </a> for MIDI output

<a href="https://github.com/craigsapp/midifile"> MidiFile </a> for MIDI files creation

<a href="https://github.com/TDSOJohn/Engine"> Engine </a> as GUI / Engine.

usage:
------
```bash
./camusic
```
