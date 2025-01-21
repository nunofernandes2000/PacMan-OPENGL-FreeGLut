Projeto Pac-Man 3D
Este projeto é uma implementação simples de um jogo inspirado no Pac-Man, desenvolvido em C com a biblioteca GLUT para gráficos 3D. O objetivo do jogo é controlar um boneco que se move num tabuleiro, evitando fantasmas e tentando passar por todas as casas do mapa para ganhar pontos.

Funcionalidades Principais
Mapa Gerado a Partir de Ficheiro: O tabuleiro do jogo é carregado a partir de um ficheiro de texto.

Controlo do Boneco: O jogador controla o boneco usando as setas do teclado.

Fantasmas:

Fantasmas normais que se movem aleatoriamente.

Fantasmas inteligentes que perseguem o jogador.

Sistema de Pontuação: Pontos são ganhos ao passar por casas não visitadas.

Pausa e Reinício: O jogo pode ser pausado (tecla F1) e reiniciado (tecla F2).

Controlo da Câmara: O jogador pode rodar e aproximar/afastar a câmara usando o teclado e o rato.

Requisitos
Bibliotecas:

GLUT (OpenGL Utility Toolkit)

OpenGL

Compilador: GCC ou outro compilador C compatível.

Sistema Operativo: Linux, macOS ou Windows (com configuração adequada para GLUT).

Como Compilar e Executar
Passo 1: Instalar Dependências
Linux (Ubuntu/Debian)
bash
Copy
sudo apt-get install freeglut3 freeglut3-dev
macOS (usando Homebrew)
bash
Copy
brew install freeglut
Windows
Instalar o MinGW e configurar o GLUT manualmente.

Passo 2: Compilar o Projeto
Clone o repositório:

bash
Copy
git clone https://github.com/seu-usuario/pacman-3d.git
cd pacman-3d
Compile o código:

bash
Copy
gcc -o pacman main.c -lGL -lGLU -lglut -lm
Passo 3: Executar o Jogo
Execute o programa com um ficheiro de mapa como argumento:

bash
Copy
./pacman mapa.txt
O ficheiro mapa.txt deve estar no formato esperado pelo jogo (ver secção Formato do Mapa abaixo).

Use as seguintes teclas para controlar o jogo:

Setas: Mover o boneco.

W, A, S, D: Rodar a câmara.

+, -: Aproximar/afastar a câmara.

F1: Pausar o jogo.

F2: Reiniciar o jogo.

Formato do Mapa
O mapa é um ficheiro de texto onde:

1 representa uma casa visitável.

0 representa uma parede ou obstáculo.

Exemplo de mapa (mapa.txt):

Copy
1 1 1 1 1
1 0 0 0 1
1 1 1 1 1
1 0 0 0 1
1 1 1 1 1
Estrutura do Código
main.c: Contém a lógica principal do jogo, incluindo a inicialização, renderização e controlo.

pm-maps.h: Biblioteca para carregar e manipular o mapa.

Funções Principais:

desenhaBoneco(): Desenha o jogador no ecrã.

desenhaFantasma(): Desenha os fantasmas.

atualizarPosicaoBoneco(): Atualiza a posição do boneco.

atualizarPosicaoFantasma(): Atualiza a posição dos fantasmas.

drawRawMap(): Desenha o tabuleiro do jogo.

Contribuições
Contribuições são bem-vindas! Se quiseres melhorar o jogo ou corrigir bugs, segue estes passos:

Faz um fork do repositório.

Cria uma nova branch (git checkout -b minha-feature).

Faz commit das tuas alterações (git commit -m 'Adicionei uma feature').

Faz push para a branch (git push origin minha-feature).

Abre um Pull Request.

Licença
Este projeto está licenciado sob a Licença MIT. Sinta-se à vontade para usar e modificar o código.

Autor
Nuno Fernandes - GitHub

Rafael Carvalho

Agradecimentos
À biblioteca GLUT por fornecer ferramentas para gráficos 3D.

Aos professores e colegas pelo apoio e feedback.

Espero que este README te ajude a apresentar o teu projeto no GitHub! Se precisares de mais alguma coisa, é só avisar. 😊
