file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(Engine ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(Engine
    PRIVATE
        ${CMAKE_SOURCE_DIR}/external/box2d/include
        ${CMAKE_SOURCE_DIR}/external/freetype/include
        ${CMAKE_SOURCE_DIR}/external/SOIL/include
        ${CMAKE_SOURCE_DIR}/external/FMOD/api/core/include
        ${CMAKE_SOURCE_DIR}/external/FMOD/api/studio/include
    PUBLIC
        ${CMAKE_SOURCE_DIR}/external/SDL/include
        ${CMAKE_SOURCE_DIR}/external/glew/include
)

if(WIN32)
    SET(LIB_PATH "lib/win/x64")
elseif(APPLE)
    SET(LIB_PATH "lib/mac")
endif()

target_link_directories(Engine
    PUBLIC
        ${CMAKE_SOURCE_DIR}/external/box2d/${LIB_PATH}
        ${CMAKE_SOURCE_DIR}/external/freetype/${LIB_PATH}
        ${CMAKE_SOURCE_DIR}/external/SOIL/${LIB_PATH}
        ${CMAKE_SOURCE_DIR}/external/FMOD/api/studio/${LIB_PATH}
        ${CMAKE_SOURCE_DIR}/external/FMOD/api/core/${LIB_PATH}
        ${CMAKE_SOURCE_DIR}/external/glew/${LIB_PATH}
        ${CMAKE_SOURCE_DIR}/external/SDL/${LIB_PATH}
)

target_link_libraries(Engine PRIVATE
    SDL2
    box2d
    freetype
    SOIL
)

if(WIN32)
    target_link_libraries(Engine PRIVATE
        SDL2main
        glew32
        fmodstudio_vc
        fmod_vc
        opengl32
    )
elseif(APPLE)
    target_link_libraries(Engine PRIVATE
        GLEW
        fmodstudio
        fmod
        "-framework OpenGL"
        "-framework Cocoa"
    )
endif()

if(WIN32)
    set_property(TARGET Engine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()
