set (SRC
    App/Application.cpp
    App/State.cpp
    App/StateStack.cpp
    App/Visualizer.cpp
    App/VisualizerState.cpp
    CA/CA.cpp
    CA/CA1d.cpp
    CA/CA2d.cpp
    Data/DataAnalyzer.cpp
#    MIDI/MIDIout.cpp
    MIDI/midiToFile.cpp
    utilities.cpp
)

add_library(src ${SRC})

# anybody linking to MathFunctions needs to include the current source directory
# except MathFunctions itself
target_include_directories(src
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
            )
