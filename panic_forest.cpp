#include "panic_forest.hpp"
#include <cmath>

// Player Implementation
Player::Player(Tyra::Engine* t_engine) : engine(t_engine) {
    position = Tyra::Vec4(0, 0, 0);
    rotation = 0.0f;
    currentOutfit = PlayerOutfit::PoloShirt;

    // Carregando modelos do Blender
    // Certifique-se de que os arquivos existam na pasta res/models/
    Tyra::ObjLoaderOptions options;
    options.scale = 1.0f;

    modelPolo = new Tyra::StaticModel(t_engine->renderer);
    modelPolo->loadObj("res/models/personagem_polo.obj", options);

    modelJacket = new Tyra::StaticModel(t_engine->renderer);
    modelJacket->loadObj("res/models/personagem_casaco.obj", options);
}

Player::~Player() {
    delete modelPolo;
    delete modelJacket;
}

void Player::update(const Tyra::Pad& t_pad, const Tyra::Camera& t_camera) {
    // Controles Estilo Tank (RE4)
    // Analógico Esquerdo: X para rotação, Y para movimento
    float joyX = t_pad.getLeftJoyX();
    float joyY = t_pad.getLeftJoyY();

    if (joyX < 100) rotation += 0.05f;
    else if (joyX > 150) rotation -= 0.05f;
    
    float speed = 0.2f;
    if (joyY < 100) { // Frente
        position.x += sin(rotation) * speed;
        position.z += cos(rotation) * speed;
    } else if (joyY > 150) { // Trás
        position.x -= sin(rotation) * speed;
        position.z -= cos(rotation) * speed;
    }
}

void Player::render(Tyra::Renderer* t_renderer) {
    Tyra::M4x4 modelMatrix;
    modelMatrix.identity();
    modelMatrix.translate(position);
    modelMatrix.rotateY(rotation);

    // Renderiza o modelo do Blender correspondente ao visual atual
    if (currentOutfit == PlayerOutfit::PoloShirt) {
        t_renderer->renderer3d.drawStatic(modelPolo, modelMatrix);
    } else {
        t_renderer->renderer3d.drawStatic(modelJacket, modelMatrix);
    }

    // O "Boneco de Palito" foi removido e substituído pelo carregamento 3D real!
}

// Camera Implementation
Camera::Camera(Tyra::Engine* t_engine) : engine(t_engine) {}

void Camera::update(const Tyra::Pad& t_pad, const Player& t_player) {
    // Lógica Over-the-shoulder (RE4)
    Tyra::Vec4 playerPos = t_player.getPosition();
    
    // Posicionamento relativo ao jogador
    float camDist = 4.0f;
    float camHeight = 2.2f;
    float offsetRight = 0.8f;

    Tyra::Vec4 camPos;
    camPos.x = playerPos.x - sin(0) * camDist + offsetRight;
    camPos.y = playerPos.y + camHeight;
    camPos.z = playerPos.z - cos(0) * camDist;

    camera.setPosition(camPos);
    camera.setLookAt(playerPos + Tyra::Vec4(0, 1.5f, 0)); // Foca na altura do ombro/cabeça
}

// Forest Implementation
Forest::Forest(Tyra::Engine* t_engine) : engine(t_engine) {}

void Forest::draw(Tyra::Renderer* t_renderer) {
    Tyra::M4x4 model;

    // CHÃO (Plano escuro e vasto)
    model.identity();
    model.scale(Tyra::Vec4(100.0f, 0.1f, 100.0f));
    t_renderer->renderer3d.drawCube(model);

    // ÁRVORES (Troncos simples espalhados pela floresta)
    for(int i = -5; i <= 5; i++) {
        for(int j = -5; j <= 5; j++) {
            if (i == 0 && j == 0) continue; // Área livre ao redor do jogador
            
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
    // Configurações de atmosfera inicial
    engine->renderer.setClearScreenColor(Tyra::Color(5, 5, 5)); // Fundo quase preto para névoa

    // Configuração da Névoa (Fog) - Essencial para o clima de terror do PS2
    engine->renderer.renderer3d.setFogColor(Tyra::Color(10, 10, 15)); // Névoa azulada/cinza
    engine->renderer.renderer3d.setFogNear(10.0f);  // Onde a névoa começa
    engine->renderer.renderer3d.setFogFar(40.0f);   // Onde tudo fica oculto
}

void PanicForestGame::loop() {
    auto& pad = engine->pad;
    
    // Evento Único: Encontrar a Mochila e Vestir o Casaco (Pressione Triângulo para simular)
    if (pad.getClicked().Triangle) {
        if (player->getOutfit() == PlayerOutfit::PoloShirt) {
            player->setOutfit(PlayerOutfit::JacketAndCap);
            // Uma vez que vestiu o casaco, a lógica de alternar é removida 
            // ou bloqueada na narrativa real do jogo.
        }
    }

    player->update(pad, camera->getCamera());
    camera->update(pad, *player);
    
    engine->renderer.beginFrame();
    forest->draw(&engine->renderer);
    player->render(&engine->renderer);
    engine->renderer.endFrame();
}
