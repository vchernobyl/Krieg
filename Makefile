OBJS = src\Main.cpp src\Game.cpp src\Actor.cpp src\Component.cpp src\SpriteComponent.cpp src\AnimSpriteComponent.cpp src\BGSpriteComponent.cpp src\Ship.cpp src\MoveComponent.cpp src\Asteroid.cpp src\Random.cpp src\InputComponent.cpp src\CircleComponent.cpp src\Laser.cpp src\RigidbodyComponent.cpp src\Math.cpp
CC = g++

SDL_PATH = C:\libs\mingw_dev_libs\SDL2
SDL_IMG_PATH = C:\libs\mingw_dev_libs\SDL2_image

INCLUDE_PATHS = -I$(SDL_PATH)\include\SDL2 -I$(SDL_IMG_PATH)\include\SDL2
LIBRARY_PATHS = -L$(SDL_PATH)\lib -L$(SDL_IMG_PATH)\lib

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
COMPILER_FLAGS = -Wall

OBJ_NAME = build\Game.exe
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
