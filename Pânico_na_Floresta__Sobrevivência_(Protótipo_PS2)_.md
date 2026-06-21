# Pânico na Floresta: Sobrevivência (Protótipo PS2) - Fase 2

Este projeto é um protótipo de Survival Horror para PlayStation 2, inspirado em Resident Evil 4.

## O que foi implementado nesta fase:

1.  **Boneco de Palito (Protótipo Maligno):** 
    - O jogador agora é representado por um boneco de palito detalhado (cabeça, tronco, braços e pernas).
    - Estrutura pronta para receber animações e modelos reais futuramente.
2.  **Cenário da Floresta:**
    - Implementação de um chão vasto e escuro.
    - Sistema de árvores básicas (troncos) espalhadas para criar obstáculos e profundidade.
3.  **Atmosfera de Terror (Névoa):**
    - Adição de **Fog (Névoa)** técnica: os objetos desaparecem na escuridão à distância, exatamente como nos clássicos do PS2 (Silent Hill, RE4).
    - Configuração de cores escuras para o céu e ambiente.

## Estrutura do Projeto

- `inc/panic_forest.hpp`: Definições das classes `Player`, `Camera`, `Forest` e o núcleo do jogo.
- `src/panic_forest.cpp`: Lógica de movimentação Tank, câmera sobre o ombro, desenho do cenário e névoa.
- `src/main.cpp`: Ponto de entrada.

## Orientações para Integração de Assets

Para evoluir este protótipo para a qualidade final:

1.  **Modelos 3D:**
    - Substitua os cubos do boneco de palito por um arquivo `.obj` (estático) ou `.md2` (animado).
    - No Tyra Engine, você usará `engine->renderer.renderer3d.draw(meuModelo)`.
2.  **Texturas:**
    - Use texturas de 128x128 ou 256x256 em formato PNG para o chão e árvores para economizar VRAM.
3.  **Colisões:**
    - O próximo passo será implementar colisões simples entre o `Player` e os troncos das árvores na classe `Forest`.

## Como Compilar

1. Certifique-se de ter o ambiente **Tyra Engine** configurado.
2. Coloque os arquivos na pasta de exemplos.
3. Use o `Makefile` incluído para gerar o arquivo `.elf`.
4. Teste no emulador **PCSX2**.

---
**Desenvolvido com Manus AI**
