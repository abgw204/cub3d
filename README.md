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
   git clone https://github.com/vinionix/cub3d.git
   cd cub3d
Compile o projeto:

bash
make
Execute o jogo passando um mapa .cub:

bash
./cub3d maps/mapa.cub
📚 Aprendizados principais
Fundamentos de gráficos 2D/3D e algoritmos de raycasting.

Manipulação de eventos e renderização em tempo real.

Organização modular de código em C para jogos.

Introdução à programação de redes com sockets UDP.

Estruturas de dados aplicadas a parsing e game loop.

📌 Roadmap (futuras implementações)
 Suporte a sprites (objetos no cenário).

 Iluminação e sombras simples.

 Multiplayer completo via UDP.

 Sistema de menu inicial e HUD.

 Ferramenta de criação de mapas.

👤 Autores
[Vinicius Fidelis].
[Gabriel Salgado].
