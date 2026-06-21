#ifndef PANIC_FOREST_HPP
#define PANIC_FOREST_HPP

#include <tyra>

enum class PlayerOutfit {
    PoloShirt,    // Visual inicial (Camisa Bege)
    JacketAndCap  // Visual após o acidente (Casaco Preto e Boné)
};

class Player {
public:
    Player(Tyra::Engine* t_engine);
    ~Player();
    void update(const Tyra::Pad& t_pad, const Tyra::Camera& t_camera);
    void render(Tyra::Renderer* t_renderer);
    Tyra::Vec4 getPosition() const { return position; }
    
    void setOutfit(PlayerOutfit t_outfit) { currentOutfit = t_outfit; }
    PlayerOutfit getOutfit() const { return currentOutfit; }

private:
    Tyra::Engine* engine;
    Tyra::Vec4 position;
    float rotation;
    PlayerOutfit currentOutfit;

    // Novos membros para modelos 3D (Blender)
    Tyra::StaticModel* modelPolo;
    Tyra::StaticModel* modelJacket;
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