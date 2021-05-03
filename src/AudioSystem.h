class Game;

class AudioSystem {
public:
    AudioSystem(Game* game);
    ~AudioSystem();

    bool Initialize();
    void Shutdown();
    void Update(float deltaTime);
private:
    Game* game;
};
