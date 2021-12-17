cmake_minimum_required(VERSION 3.8)

project("Game")

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h)

add_executable(Game ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/external/SDL/include
    ${CMAKE_SOURCE_DIR}/external/box2d/include
    ${CMAKE_SOURCE_DIR}/external/freetype/include
    ${CMAKE_SOURCE_DIR}/external/glew/include
    ${CMAKE_SOURCE_DIR}/external/SOIL/include
    ${CMAKE_SOURCE_DIR}/external/FMOD/api/core/include
    ${CMAKE_SOURCE_DIR}/external/FMOD/api/studio/include
)

target_link_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/external/SDL/lib/x64
    ${CMAKE_SOURCE_DIR}/external/box2d/lib/x64
    ${CMAKE_SOURCE_DIR}/external/freetype/lib/x64
    ${CMAKE_SOURCE_DIR}/external/glew/lib/x64
    ${CMAKE_SOURCE_DIR}/external/SOIL/lib/x64
    ${CMAKE_SOURCE_DIR}/external/FMOD/api/studio/lib/x64
)

target_link_libraries(Game PRIVATE
    SDL2
    box2d
    freetype
    glew32
    SOIL
    fmodstudio_vc
    opengl32
)

target_compile_features(Game PRIVATE cxx_std_17)
