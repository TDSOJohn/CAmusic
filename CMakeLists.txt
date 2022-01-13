cmake_minimum_required(VERSION 3.15)

project(camusic VERSION 1.0)

# set c++17 standard, require it and only allow the --std=c++17 flag
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)
message(${CMAKE_BUILD_TYPE})

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug
    CACHE STRING
      "Choose the type of build (Debug or Release)"
      FORCE
    )
endif()

# Generate config.h with version number and CMAKE_BUILD_TYPE
# configure_file(config.h.in config.h)

message(${CMAKE_HOST_SYSTEM_NAME})

# Find SFML shared libraries
find_package(SFML 2.5
    COMPONENTS
    system window graphics REQUIRED
    )

# Platform check: better use CMAKE_HOST_SYSTEM_NAME
# Linux version
if(LINUX)
    include_directories(SFML/include)
# Might not be the best option, but works on mac
elseif(APPLE)
    include_directories("/usr/local/include/")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Resources")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/externals/engine/include")

add_subdirectory(src)
list(APPEND EXTRA_LIBS src)

# Compile executable
if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_executable(camusic src/main.cpp)
elseif(${CMAKE_BUILD_TYPE} MATCHES Release)
    # Create .app bundle
    if(APPLE)
        message("Building .app!")
        add_executable(camusic MACOSX_BUNDLE src/main.cpp)
        # Create Info.plist file
        set_target_properties(camusic PROPERTIES
            BUNDLE True
            MACOSX_BUNDLE_GUI_IDENTIFIER giovannibasso.camusic
            MACOSX_BUNDLE_BUNDLE_NAME camusic
            MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/customtemplate.plist.in
        )
        # Copy Resources folder
        file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Resources/" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/build/window.app/Contents/Resources/")
        # Link CoreServices framework
        target_link_libraries(camusic "-framework CoreServices")
        # copy SFML frameworks
    endif()
endif()


target_link_libraries(camusic src)
target_link_libraries(camusic "${CMAKE_CURRENT_SOURCE_DIR}/externals/engine/build/libengine.a")
# Link executable to required SFML libraries
target_link_libraries(camusic sfml-graphics sfml-audio sfml-network sfml-window sfml-system)
target_link_libraries(camusic "${CMAKE_CURRENT_SOURCE_DIR}/midifile/lib/libmidifile.a")

# add the binary tree directory to the list of paths to search for include files
target_include_directories(camusic PUBLIC
                           "${PROJECT_BINARY_DIR}/include"
                           )
