#ifndef PANIC_FOREST_HPP
#define PANIC_FOREST_HPP

#include <tyra>

class Player {
public:
    Player(Tyra::Engine* t_engine);
    ~Player();
    void update(const Tyra::Pad& t_pad, const Tyra::Camera& t_camera);
    void render(Tyra::Renderer* t_renderer);
    Tyra::Vec4 getPosition() { return position; }
    float rotation;
    Tyra::Vec4 position;
private:
    Tyra::Engine* engine;
};

class Camera {
public:
    Camera(Tyra::Engine* t_engine);
    void update(const Tyra::Pad& t_pad, const Player& t_player);
    Tyra::Camera& getCamera() { return camera; }
private:
    Tyra::Engine* engine;
    Tyra::Camera camera;
};

class Forest {
public:
    Forest(Tyra::Engine* t_engine);
    void draw(Tyra::Renderer* t_renderer);
private:
    Tyra::Engine* engine;
};

class PanicForestGame : public Tyra::Game {
public:
    PanicForestGame(Tyra::Engine* t_engine);
    ~PanicForestGame();
    void init();
    void loop();
private:
    Tyra::Engine* engine;
    Player* player;
    Camera* camera;
    Forest* forest;
};

#endif
