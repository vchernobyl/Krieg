OBJS = src\Main.cpp src\Game.cpp src\Actor.cpp src\Component.cpp src\SpriteComponent.cpp src\AnimSpriteComponent.cpp src\Random.cpp src\Math.cpp src\Hero.cpp src\MoveComponent.cpp src\InputSystem.cpp src\JumpComponent.cpp src\IdleState.cpp src\RunningState.cpp src\JumpingState.cpp src\Camera.cpp src\ColliderComponent.cpp src\BoxColliderComponent.cpp src\PhysicsWorld.cpp src\TileMap.cpp src\pugixml.cpp src\DebugRenderer.cpp src\Collisions.cpp src\Player.cpp

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
