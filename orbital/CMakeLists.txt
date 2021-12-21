file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(Orbital ${HEADER_FILES} ${SOURCE_FILES})

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
