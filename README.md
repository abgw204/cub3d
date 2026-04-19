# Cub3D

Cub3D é um projeto desenvolvido em **C** inspirado em *Wolfenstein 3D*, utilizando a técnica de **raycasting** para renderizar um ambiente 3D a partir de mapas 2D.  
O objetivo é explorar conceitos de gráficos, estruturas de dados, networking e programação de baixo nível em tempo real.
Este projeto faz parte do currículo da 42 Rio.

---

## Funcionalidades
- Renderização 3D baseada em **raycasting**.  
- Movimentação do jogador em primeira pessoa.
- Sistema de colisão contra paredes.  
- Leitura de mapas a partir de arquivos `.cub`.  
- Suporte a texturas e sprites.
- Renderização em tempo real com atualizações de FPS.  
- Servidor **multiplayer online via UDP**.  

---

## Tecnologias e Conceitos
- **Linguagem C**  
- **Raycasting** para renderização 3D simplificada  
- **Manipulação de imagens** e buffers de tela  
- **Estruturas de dados** aplicadas a jogos  
- **Eventos de teclado e mouse**  
- **Programação de redes (UDP)** para suporte online 

---

## Como executar
1. Clone o repositório:
   ```bash
   git clone https://github.com/abgw204/cub3d.git
   cd cub3d
 2. Compile o client (raylib):
   ```bash
    make rl
 3. Execute o jogo passando um mapa `.cub` e os argumentos de rede:
   ```bash
    ./cub3d_rl <MAPA.cub> <PLAYER_ID> <SERVER_IP> [PORTA]

## raylib

O client usa **raylib** como backend gráfico.

- Build do raylib (opcional): `make raylib` (usa `pkg-config raylib` se estiver instalado; senão compila o submodule)
- Build do client: `make rl`

As dependências de desktop Linux (X11) e o passo a passo estão em `docs/raylib.md`.

## Servidor

- Build do servidor: `make server`
- Executar: `./server_cub3d [PORTA]`

## Principais Aprendizados

Durante o desenvolvimento deste projeto, foram consolidados os seguintes conhecimentos:

- **Fundamentos de gráficos 2D/3D**, incluindo algoritmos de **raycasting**
- **Manipulação de eventos** e **renderização em tempo real**
- **Introdução à programação de redes** utilizando **sockets UDP**
- **Multi-threading** para **rendenização** mais rápida (mais fps)

## 👤 Autores

- **Vinicius Fidelis**
- **Gabriel Salgado**
