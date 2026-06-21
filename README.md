# Pânico na Floresta: Sobrevivência (Protótipo PS2)

Este é um protótipo de Survival Horror para PlayStation 2 inspirado em Resident Evil 4 e Silent Hill.

## Funcionalidades
- Controles Tank (estilo clássico).
- Câmera Over-the-shoulder (estilo RE4).
- Sistema de Névoa (Fog) para atmosfera.
- Cenário de Floresta procedimental.

## Como Compilar
Este projeto utiliza o **Tyra Engine**. A compilação é feita automaticamente via GitHub Actions sempre que um novo commit é feito.

### Estrutura do Projeto
- `main.cpp`: Ponto de entrada do jogo.
- `panic_forest.cpp` / `.hpp`: Lógica principal do jogo, jogador e ambiente.
- `Makefile`: Instruções de compilação para o compilador do PS2.
- `.github/workflows/build.yml`: Configuração da automação de build.

## Créditos
Desenvolvido como um protótipo de Survival Horror para PS2.
