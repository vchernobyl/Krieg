cmake_minimum_required(VERSION 3.21)

project("Game")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(app)

#if(WIN32)
#    set_property(TARGET ${PROJECT_NAME} PROPERTY
#        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#    )
#
#    set_property(TARGET ${PROJECT_NAME} PROPERTY
#        MSVC_RUNTIME_LIBRARY "MultiThreaded"
#    )
#elseif(APPLE)
#    set_target_properties(${PROJECT_NAME} PROPERTIES
#        XCODE_GENERATE_SCHEME TRUE
#        XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#    )
#endif()
