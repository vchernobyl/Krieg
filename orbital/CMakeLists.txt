add_executable(Orbital
    Main.cpp
    OrbitalGame.cpp
    Player.cpp
    Orbit.cpp
)

target_link_libraries(Orbital PRIVATE Engine)

if(WIN32)
    set_property(TARGET Orbital PROPERTY
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    set_property(TARGET Orbital PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded"
    )
elseif(APPLE)
    set_target_properties(Orbital PROPERTIES
        XCODE_GENERATE_SCHEME TRUE
        XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()
