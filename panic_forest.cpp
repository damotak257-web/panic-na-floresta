#include "panic_forest.hpp"
#include <cmath>

// Player Implementation
Player::Player(Tyra::Engine* t_engine) : engine(t_engine) {
    position = Tyra::Vec4(0, 0, 0);
    rotation = 0.0f;
}

Player::~Player() {}

void Player::update(const Tyra::Pad& t_pad, const Tyra::Camera& t_camera) {
    // Controles Estilo Tank (RE4)
    const auto& leftJoy = t_pad.getLeftJoy();
    
    if (leftJoy.x < 100) rotation += 0.05f;
    else if (leftJoy.x > 150) rotation -= 0.05f;

    float speed = 0.2f;
    if (leftJoy.y < 100) { // Frente
        position.x += sin(rotation) * speed;
        position.z += cos(rotation) * speed;
    } else if (leftJoy.y > 150) { // Trás
        position.x -= sin(rotation) * speed;
        position.z -= cos(rotation) * speed;
    }
}

void Player::render(Tyra::Renderer* t_renderer) {
    Tyra::M4x4 modelMatrix;
    modelMatrix.identity();
    modelMatrix.translate(position);
    modelMatrix.rotateY(rotation);
    
    // Desenha o Boneco de Palito (Simplificado com Cubos para o protótipo)
    // Cabeça
    Tyra::M4x4 headPart = modelMatrix;
    headPart.translate(Tyra::Vec4(0, 1.8f, 0));
    headPart.scale(Tyra::Vec4(0.3f, 0.3f, 0.3f));
    t_renderer->renderer3d.drawCube(headPart);

    // Tronco
    Tyra::M4x4 bodyPart = modelMatrix;
    bodyPart.translate(Tyra::Vec4(0, 1.0f, 0));
    bodyPart.scale(Tyra::Vec4(0.4f, 0.8f, 0.2f));
    t_renderer->renderer3d.drawCube(bodyPart);
}

// Camera Implementation
Camera::Camera(Tyra::Engine* t_engine) : engine(t_engine) {}

void Camera::update(const Tyra::Pad& t_pad, const Player& t_player) {
    // Lógica Over-the-shoulder (RE4)
    float camDist = 5.0f;
    float camHeight = 2.5f;
    float theta = t_player.rotation;

    Tyra::Vec4 playerPos = t_player.position;
    Tyra::Vec4 camPos;
    camPos.x = playerPos.x - sin(theta) * camDist;
    camPos.y = playerPos.y + camHeight;
    camPos.z = playerPos.z - cos(theta) * camDist;

    camera.setPosition(camPos);
    camera.setLookAt(playerPos + Tyra::Vec4(0, 1.5f, 0));
}

// Forest Implementation
Forest::Forest(Tyra::Engine* t_engine) : engine(t_engine) {}

void Forest::draw(Tyra::Renderer* t_renderer) {
    Tyra::M4x4 model;

    // CHÃO
    model.identity();
    model.scale(Tyra::Vec4(100.0f, 0.1f, 100.0f));
    t_renderer->renderer3d.drawCube(model);

    // ÁRVORES (Troncos espalhados)
    for(int i = -5; i <= 5; i++) {
        for(int j = -5; j <= 5; j++) {
            if (i == 0 && j == 0) continue;
            model.identity();
            model.translate(Tyra::Vec4(i * 10.0f, 5.0f, j * 10.0f));
            model.scale(Tyra::Vec4(0.5f, 10.0f, 0.5f));
            t_renderer->renderer3d.drawCube(model);
        }
    }
}

// Game Implementation
PanicForestGame::PanicForestGame(Tyra::Engine* t_engine) : engine(t_engine) {
    player = new Player(t_engine);
    camera = new Camera(t_engine);
    forest = new Forest(t_engine);
}

PanicForestGame::~PanicForestGame() {
    delete player;
    delete camera;
    delete forest;
}

void PanicForestGame::init() {
    engine->renderer.setClearScreenColor(Tyra::Color(5, 5, 5));

    // Configuração da Névoa (Fog)
    engine->renderer.renderer3d.setFogColor(Tyra::Color(10, 10, 15));
    engine->renderer.renderer3d.setFogNear(10.0f);
    engine->renderer.renderer3d.setFogFar(40.0f);
}

void PanicForestGame::loop() {
    auto& pad = engine->pad;
    player->update(pad, camera->getCamera());
    camera->update(pad, *player);

    engine->renderer.beginFrame();
    forest->draw(&engine->renderer);
    player->render(&engine->renderer);
    engine->renderer.endFrame();
}
