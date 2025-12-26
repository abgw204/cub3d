# 🎮 Cub3D

Cub3D é um projeto desenvolvido em **C** inspirado em *Wolfenstein 3D*, utilizando a técnica de **raycasting** para renderizar um ambiente 3D a partir de mapas 2D.  
O objetivo é explorar conceitos de gráficos, estruturas de dados e programação de baixo nível em tempo real.  
Este projeto faz parte do currículo da 42 Rio.

---

## ✨ Funcionalidades
- Renderização 3D baseada em **raycasting**.  
- Movimentação do jogador em primeira pessoa.  
- Sistema de colisão contra paredes.  
- Leitura de mapas a partir de arquivos `.cub`.  
- Suporte a texturas em paredes, chão e teto.  
- Renderização em tempo real com atualizações de FPS.  
- Versão em desenvolvimento com suporte a **multiplayer online via UDP**.  

---

## 🛠️ Tecnologias e Conceitos
- **Linguagem C**  
- **Raycasting** para renderização 3D simplificada  
- **Manipulação de imagens** e buffers de tela  
- **Estruturas de dados** aplicadas a jogos  
- **Eventos de teclado e mouse**  
- **Programação de redes (UDP)** para suporte online (em andamento)  

---

## 🚀 Como executar
1. Clone o repositório:
   ```bash
   git clone https://github.com/abgw204/cub3d.git
   cd cub3d
2. Compile o projeto:
   ```bash
   make
3. Execute o jogo passando um mapa .cub:
   ```bash
   ./cub3d maps/mapa.cub

## 📚 Principais Aprendizados

Durante o desenvolvimento deste projeto, foram consolidados os seguintes conhecimentos:

- **Fundamentos de gráficos 2D/3D**, incluindo algoritmos de **raycasting**
- **Manipulação de eventos** e **renderização em tempo real**
- **Organização modular de código em C** aplicada ao desenvolvimento de jogos
- **Introdução à programação de redes** utilizando **sockets UDP**
- **Estruturas de dados** aplicadas ao **parsing** e ao **game loop**

---

## 📌 Roadmap — Próximas Implementações

Funcionalidades planejadas para evoluir o projeto:

- Suporte a **sprites** (objetos no cenário)
- Sistema de **iluminação e sombras simples**
- **Multiplayer completo** via **UDP**
- Sistema de **menu inicial** e **HUD**
- **Ferramenta de criação de mapas**

---

## 👤 Autores

- **Vinicius Fidelis**
- **Gabriel Salgado**
