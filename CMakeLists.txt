cmake_minimum_required(VERSION 3.21)

project("Game")

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/external/SDL/include
    ${CMAKE_SOURCE_DIR}/external/box2d/include
    ${CMAKE_SOURCE_DIR}/external/freetype/include
    ${CMAKE_SOURCE_DIR}/external/glew/include
    ${CMAKE_SOURCE_DIR}/external/SOIL/include
    ${CMAKE_SOURCE_DIR}/external/FMOD/api/core/include
    ${CMAKE_SOURCE_DIR}/external/FMOD/api/studio/include
)

if(WIN32)
    SET(LIB_PATH "lib/win/x64")
elseif(APPLE)
    SET(LIB_PATH "lib/mac")
endif()

target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/external/SDL/${LIB_PATH}
    ${CMAKE_SOURCE_DIR}/external/box2d/${LIB_PATH}
    ${CMAKE_SOURCE_DIR}/external/freetype/${LIB_PATH}
    ${CMAKE_SOURCE_DIR}/external/glew/${LIB_PATH}
    ${CMAKE_SOURCE_DIR}/external/SOIL/${LIB_PATH}
    ${CMAKE_SOURCE_DIR}/external/FMOD/api/studio/${LIB_PATH}
    ${CMAKE_SOURCE_DIR}/external/FMOD/api/core/${LIB_PATH}
)

# Common platform libraries.
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2
    box2d
    freetype
    SOIL
)

# Windows libraries.
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2main
        glew32
        fmodstudio_vc
        fmod_vc
        opengl32
    )
# Mac libraries.
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        GLEW
        fmodstudio
        fmod
        "-framework OpenGL"
        "-framework Cocoa"
    )
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    set_property(TARGET ${PROJECT_NAME} PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded"
    )
elseif(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        XCODE_GENERATE_SCHEME TRUE
        XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

