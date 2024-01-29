## Cross platform 2D game engine.
The project is built using:
- OpenGL - rendering
- SDL2 - window and input handling
- Box2D - physics
- FreeType - font rendering

### Windows
To generate a Visual Studio build, you can run a build generator for your current VS version, for example:
```
cmake -G "Visual Studio 17 2022"
```
### MacOS
Similarly an XCode build can be generated via:
```
cmake -G Xcode
```

### Games
There are currently 2 games that you can play, just select the appropriate launch target in your IDE.

https://github.com/vchernobyl/Krieg/assets/12860313/b6114fab-28f0-4d21-9d37-5094d04299bc

https://github.com/vchernobyl/Krieg/assets/12860313/31f112ca-fdd3-4546-aaf8-e0959e2fd0fb

