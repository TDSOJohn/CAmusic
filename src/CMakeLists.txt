set (SRC
    CA/CA.cpp
    CA/CA1d.cpp
    CA/CA2d.cpp
    Data/DataAnalyzer.cpp
#    MIDI/MIDIout.cpp
    MIDI/midiToFile.cpp
    utilities.cpp
    Visualizer.cpp)

add_library(src ${SRC})

# anybody linking to MathFunctions needs to include the current source directory
# except MathFunctions itself
target_include_directories(src
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
            )
