/*
Nuno Fernandes - 21635
Rafael Carvalho - 21986
*/

#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "pm-maps.h"
#include <math.h>
#include <time.h>


#define TIME 50
#define NCubos 2

GLfloat vertices[][3] = { {-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0} };

GLfloat normals[][3] = { {-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0} };

GLfloat colors[][3] = { {0.0,0.0,0.0},{1.0,0.0,0.0},
{1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0},
{1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0} };




/*---------------Estrutura Fantasma-------------------*/

// Definição da estrutura para os fantasmas
struct fantasma {
	float x;
	float y;
	float xFinal;
	float yFinal;
	float velocidade;
	int tipo; // 0 para fantasma normal, 1 para fantasma inteligente
};


struct fantasma* fantasmas = NULL;

int nFantasmas; // Número de fantasmas

/*---------------Estrutura Fantasma-------------------*/


/*---------------Variaveis globais para o estado do jogo-------------------*/
int pontuacao = 0;
int jogoPausado = 0;
int jogoTerminado = 0;
/*---------------Variaveis globais para o estado do jogo-------------------*/

// Variaveis Globais

float distCamara = 3.0;
float dDistCamara = 0.2;
float Longitude = 0;
float Latitude = 0;
float dAlfa = 2;
float xRato, yRato;   // guarda a ultima posicao do rato (para calcular o deslocamento na Lat. e Long.)
float angRato = 0.25;  // precisao do rato: numero de angulos por pixel.

float bonecoX = 0.0; // PosbonecoX
float bonecoY = 0.0; // PosbonecoY


float bonecoXFinal = 0.0;
float bonecoYFinal = 0.0;
float velocidade = 5.0; // Velocidade de movimento do Boneco



float MAX_LONGITUDE = 90.0; // para a direita
float MIN_LONGITUDE = -90.0; // para a esquerda
float MAX_LATITUDE = 90.0; // para  cima
float MIN_LATITUDE = -90.0; // para baixo



struct cubo {
	float theta[3];
	float escala;
	float xCubo;
	float yCubo;
	float v;
};

struct cubo cubos[NCubos];
int selectedCubo = 0;
float v = 0.5;				// velocity (units/second)

float internalPos = 0.0;
float internalVel = 2.0;

// PACMAN - MAP (change the viewer position)
static GLdouble viewer[] = { 1.0, -2.0, 3.0 }; /* initial viewer location */

char** map = NULL;



/*---------------Funcoes de mensagens no ecra-------------------*/
// Funcao para mostrar a pontuação na tela
void mostrarPontuacao() {
	char scoreStr[50];
	sprintf(scoreStr, "Pontos Ganhos: %d", pontuacao);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-0.9, 2.0);
	for (char* c = scoreStr; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

//Mostra no ecrã quando o jogo está no modo pausa
void mostrarMensagemPausa() {
	if (jogoPausado) {
		char pauseStr[] = "Jogo em Pausa [Prime a tecla F1 novamente para continuar a jogar]";
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(-2.5, 1.5);
		for (char* c = pauseStr; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
	}
}

// Função para mostrar os no lado direito superior o F1 e F2
void mostrarControles() {
	char pauseStr[] = "F1 para pausar";
	char exitStr[] = "F2 para reniciar o jogo";
	glColor3f(1.0, 1.0, 1.0);

	// F1 - PAUSA
	glRasterPos2f(2.7, 2.55);
	for (char* c = pauseStr; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}

	// F2 - SAIR
	glRasterPos2f(2.7, 1.90);
	for (char* c = exitStr; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

/*----------------------FIM-Funcoes das mensagens imprimidas no ecra------*/


void polygon(int a, int b, int c, int d)
{

	/* draw a polygon via list of vertices */

	glBegin(GL_POLYGON);
		//glColor3fv(colors[a]);
		glNormal3fv(normals[a]);
		glVertex3fv(vertices[a]);
		//glColor3fv(colors[b]);
		glNormal3fv(normals[b]);
		glVertex3fv(vertices[b]);
		//glColor3fv(colors[c]);
		glNormal3fv(normals[c]);
		glVertex3fv(vertices[c]);
		//glColor3fv(colors[d]);
		glNormal3fv(normals[d]);
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube(void)
{

	/* map vertices to faces */

	glColor3fv(colors[1]);
	polygon(0, 3, 2, 1);
	glColor3fv(colors[2]);
	polygon(2, 3, 7, 6);
	glColor3fv(colors[3]);
	polygon(0, 4, 7, 3);
	glColor3fv(colors[4]);
	polygon(1, 2, 6, 5);
	glColor3fv(colors[5]);
	polygon(4, 5, 6, 7);
	glColor3fv(colors[7]);
	polygon(0, 1, 5, 4);
}

void colorMAP(void)
{
	/* map vertices to faces */
	glColor3f(1.0, 1.0, 1.0); // Branco
	polygon(0, 3, 2, 1);
	glColor3f(0.0, 0.0, 0.0); // Preto
	polygon(2, 3, 7, 6);
	glColor3f(0.0, 0.0, 0.0); // Preto
	polygon(0, 4, 7, 3);
	glColor3f(0.0, 0.0, 0.0); // Preto
	polygon(1, 2, 6, 5);
	glColor3f(1.0, 1.0, 1.0); // Branco
	polygon(4, 5, 6, 7);
	glColor3f(0.0, 0.0, 0.0); // Preto
	polygon(0, 1, 5, 4);
}

void colorBody(void)
{
	/* map vertices to faces */
	glColor3f(0.0, 0.0, 1.0); // Azul
	polygon(0, 3, 2, 1);
	glColor3f(0.0, 0.0, 1.0); // Azul
	polygon(2, 3, 7, 6);
	glColor3f(0.0, 0.0, 1.0); // Azul
	polygon(0, 4, 7, 3);
	glColor3f(0.0, 0.0, 1.0); // Azul
	polygon(1, 2, 6, 5);
	glColor3f(0.0, 0.0, 1.0); // Azul
	polygon(4, 5, 6, 7);
	glColor3f(0.0, 0.0, 1.0); // Azul
	polygon(0, 1, 5, 4);
}

void desenhaBoneco() {

	int maxSize = xTabSize() > yTabSize() ? xTabSize() : yTabSize();

	glPushMatrix();

	// Aplica a mesma escala que o mapa
	glScalef(1.0 / maxSize, 1.0 / maxSize, 1.0 / maxSize);

	// Aplica o mesmo deslocamento que o mapa
	glTranslatef(-(xTabSize() - 1), -(yTabSize() - 1), 0.0);

	// Move para a posição do boneco
	glTranslatef(bonecoX, bonecoY, 1.0);


	//Onde mudamos o tamanho do boneco
	glScalef(0.7, 0.5, 0.7);

	glRotatef(90.0, 45.0, 1.0, 0.0);


	// Desenha o boneco

	//cabeça
	glPushMatrix();
	glTranslatef(0.0, 0.5, -0.1);
	glScalef(0.45, 0.3, 0.5);
	colorMAP();
	glPopMatrix();

	// Corpo
	glPushMatrix();
	glTranslatef(0.0, 0.1, 0.0);
	glScalef(0.5, 1.0, 0.5);
	colorBody();
	glPopMatrix();

	// Perna Esquerda
	glPushMatrix();
	glTranslatef(-0.5, -0.50, 0.0); //-0.4
	glRotatef(40 * internalPos, 1, 0, 0);
	glTranslatef(0, -0.50, 0.0); //-0.3
	glScalef(0.15, 0.3, 0.15);
	glRotatef(-90, 0, 1, 0);
	colorBody();
	glPopMatrix();

	// Perna Direita
	glPushMatrix();
	glTranslatef(0.5, -0.50, 0.0);
	glRotatef(-45 * internalPos, 1, 0, 0);
	glTranslatef(0, -0.50, 0.0);
	glScalef(0.15, 0.3, 0.15);
	glRotatef(90, 0, 1, 0);
	colorBody();
	glPopMatrix();

	glPopMatrix();
}

void init() {
	cubos[0].theta[0] = 0.0;
	cubos[0].theta[1] = 0.0;
	cubos[0].theta[2] = 0.0;
	cubos[0].escala = 1.0;
	cubos[0].xCubo = -1.5;
	cubos[0].yCubo = 0.0;
	cubos[0].v = -0.2;

	cubos[1].theta[0] = 0.0;
	cubos[1].theta[1] = 0.0;
	cubos[1].theta[2] = 0.0;
	cubos[1].escala = 1.0;
	cubos[1].xCubo = 1.5;
	cubos[1].yCubo = 0.0;
	cubos[1].v = 0.8;

}

void eixos() {
	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-2, 0, 0);
		glVertex3f(2, 0, 0);

		glVertex3f(2, 0, 0);
		glVertex3f(1.7, 0.3, 0);
		glVertex3f(2, 0, 0);
		glVertex3f(1.7, -0.3, 0);


		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0, -2, 0);
		glVertex3f(0, 2, 0);

		glVertex3f(0, 2, 0);
		glVertex3f(0.3, 1.7, 0);
		glVertex3f(0, 2, 0);
		glVertex3f(-0.3, 1.7, 0);


		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0, 0, -2);
		glVertex3f(0, 0, 2);

		glVertex3f(0, 0, 2);
		glVertex3f(0.3, 0, 1.7);
		glVertex3f(0, 0, 2);
		glVertex3f(-0.3, 0, 1.7);

	glEnd();
}

void updateCubeColor(void)
{
	glColor3f(0.0, 1.0, 0.0); // verde
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
}


/*---------------Funções dos fantasmas-------------------*/
void cuboFantasmas(void)
{
	glColor3f(1.0, 0.0, 1.0); // Rosa
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
}

void cuboFantasmasINTELIGENTE(void)
{
	glColor3f(1.0, 0.0, 0.0); // Vermelho
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
}

// Função para inicializar os fantasmas em posicoes aleatorias
void inicializarFantasmas() {
	int totalFantasmas = numGhosts() + numSmartGhosts();
	fantasmas = (struct fantasma*)malloc(totalFantasmas * sizeof(struct fantasma)); // Alocar memoria para os fantasmas

	srand(time(NULL));
	for (int i = 0; i < totalFantasmas; i++) {
		int x, y;
		// Encontrar uma posicao vazia para o fantasma
		do {
			x = rand() % xTabSize();
			y = rand() % yTabSize();
		} while (map[x][y] != 1 || (x == (int)(bonecoX / 2.0) && y == (int)(bonecoY / 2.0)));

		fantasmas[i].x = x * 2.0;
		fantasmas[i].y = y * 2.0;
		fantasmas[i].xFinal = fantasmas[i].x;
		fantasmas[i].yFinal = fantasmas[i].y;

		if (i < numGhosts()) {
			fantasmas[i].tipo = 0; // Fantasma normal
			fantasmas[i].velocidade = 2.5;
		} else {
			fantasmas[i].tipo = 1; // Fantasma inteligente
			fantasmas[i].velocidade = 3.0;
		}
	}
	nFantasmas = totalFantasmas; // Atualizar o numero de fantasmas
}

// Função para desenhar os fantasmas
void desenhaFantasma(struct fantasma *f) {
	int maxSize = xTabSize() > yTabSize() ? xTabSize() : yTabSize();

	glPushMatrix();

	glScalef(1.0 / maxSize, 1.0 / maxSize, 1.0 / maxSize);
	glTranslatef(-(xTabSize() - 1), -(yTabSize() - 1), 0.0);
	glTranslatef(f->x, f->y, 0.8);

	glScalef(0.5, 0.5, 0.5);
	if (f->tipo == 1) {
		cuboFantasmasINTELIGENTE(); // Azul para fantasmas inteligentes
	} else {
		cuboFantasmas(); // Rosa para fantasmas normais
	}

	glPopMatrix();
}

// Função para atualizar a posição dos fantasmas
void atualizarPosicaoFantasma(struct fantasma *f, float deltaTime) {
	//Move o fantasma para a sua posição alvo atual
    float deltaX = f->xFinal - f->x;
    float deltaY = f->yFinal - f->y;
    float distancia = sqrt(deltaX * deltaX + deltaY * deltaY);
    float maxDistancia = f->velocidade * deltaTime;

    if (distancia > maxDistancia) {
        f->x += (deltaX / distancia) * maxDistancia;
        f->y += (deltaY / distancia) * maxDistancia;
        return;
    }

    //O fantasma chegou a posição alvo, apos isso ele escolhe uma nova direcao
    f->x = f->xFinal;
    f->y = f->yFinal;

	// Os fantasmas inteligentes, escolhem a direcao com base na posicao do jogador
    if (f->tipo == 1) {
        float dx = bonecoX - f->xFinal;
        float dy = bonecoY - f->yFinal;

    	// Determina a direcao principal com base no maior delta
        float step = 2.0;
        float newX = f->xFinal;
        float newY = f->yFinal;


    	//O fantasma tenta mover-se na direcao preferida primeiro
        if (fabs(dx) > fabs(dy)) {
            // Move-se na horizontal
            newX = f->xFinal + (dx > 0 ? step : -step);
            int mapX = (int)(newX / 2.0);
            int mapY = (int)(f->yFinal / 2.0);


        	// Se tiver bloqueado, tenta mover-se na vertical
            if (mapX < 0 || mapX >= xTabSize() || map[mapX][mapY] == 0) {
                newX = f->xFinal;
                newY = f->yFinal + (dy > 0 ? step : -step);
            }
        } else {
            // Move-se na vertical
            newY = f->yFinal + (dy > 0 ? step : -step);
            int mapX = (int)(f->xFinal / 2.0);
            int mapY = (int)(newY / 2.0);

            // Se tiver bloqueado, ele tenta mover-se na horizontal
            if (mapY < 0 || mapY >= yTabSize() || map[mapX][mapY] == 0) {
                newY = f->yFinal;
                newX = f->xFinal + (dx > 0 ? step : -step);
            }
        }


    	//Verifica a posicao final
        int mapX = (int)(newX / 2.0);
        int mapY = (int)(newY / 2.0);


    	// Se ainda estiver bloqueado, tenta mover-se em todas as direcoes
        if (mapX < 0 || mapX >= xTabSize() || mapY < 0 || mapY >= yTabSize() || map[mapX][mapY] == 0) {
        	// Tenta mover-se em todas as posicoes na seguinte ordem: cima, direita, baixo, esquerda
            int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            int found = 0;
        	//tenta mover-se em todas as direcoes na seguinte ordem: cima, direita, baixo, esquerda
            for (int i = 0; i < 4 && !found; i++) {
                newX = f->xFinal + directions[i][0] * step;
                newY = f->yFinal + directions[i][1] * step;
                mapX = (int)(newX / 2.0);
                mapY = (int)(newY / 2.0);
            	// Verifica se a posicao final é valida
                if (mapX >= 0 && mapX < xTabSize() && mapY >= 0 && mapY < yTabSize() &&
                    (map[mapX][mapY] == 1 || map[mapX][mapY] == 2)) {
                    int posicaoOcupada = 0;
                	// Verifica se a posicao final nao esta ocupada por outro fantasma
                    for (int j = 0; j < nFantasmas; j++) {
                        if (fantasmas[j].x == newX && fantasmas[j].y == newY) {
                            posicaoOcupada = 1;
                            break;
                        }
                    }
                	// Se a posicao final nao estiver ocupada, define como encontrada
                    if (!posicaoOcupada) {
                        found = 1;
                    }
                }
            }

            if (!found) {
                return;
            }
        }


    	// Atualiza a posicao final se for valida
        if (mapX >= 0 && mapX < xTabSize() && mapY >= 0 && mapY < yTabSize() &&
            (map[mapX][mapY] == 1 || map[mapX][mapY] == 2)) {
            int posicaoOcupada = 0;
            for (int i = 0; i < nFantasmas; i++) {
                if (fantasmas[i].x == newX && fantasmas[i].y == newY) {
                    posicaoOcupada = 1;
                    break;
                }
            }
            if (!posicaoOcupada) {
                f->xFinal = newX;
                f->yFinal = newY;
            }
        }
    } else {
    	// Movimento normal do fantasma
        int direcao = rand() % 4;
        float newX = f->xFinal;
        float newY = f->yFinal;
        float step = 2.0;

        switch (direcao) {
            case 0: newY += step; break;
            case 1: newY -= step; break;
            case 2: newX -= step; break;
            case 3: newX += step; break;
        }

        int mapX = (int)(newX / 2.0);
        int mapY = (int)(newY / 2.0);

    	//garante que a posicao não esta ocupada
        if (mapX >= 0 && mapX < xTabSize() && mapY >= 0 && mapY < yTabSize() &&
            (map[mapX][mapY] == 1 || map[mapX][mapY] == 2)) {
            int posicaoOcupada = 0;
            for (int i = 0; i < nFantasmas; i++) {
                if (fantasmas[i].x == newX && fantasmas[i].y == newY) {
                    posicaoOcupada = 1;
                    break;
                }
            }
            if (!posicaoOcupada && !(newX == bonecoX && newY == bonecoY)) {
                f->xFinal = newX;
                f->yFinal = newY;
            }
        }
    }
}

// Atualizar a posição de todos os fantasmas
void atualizarPosicoesFantasmas(float deltaTime) {
	for (int i = 0; i < nFantasmas; i++) {
		atualizarPosicaoFantasma(&fantasmas[i], deltaTime);
	}
}

// Desenhar todos os fantasmas
void desenhaFantasmas() {
	for (int i = 0; i < nFantasmas; i++) {
		desenhaFantasma(&fantasmas[i]);
	}
}
/*-----------------------------------------------------*/


// PACMAN - MAP
void drawRawMap(char** m) {
	int i, j;
	int maxSize = xTabSize() > yTabSize() ? xTabSize() : yTabSize();

	glPushMatrix();

	glScalef(1.0 / maxSize, 1.0 / maxSize, 1.0 / maxSize);
	glTranslatef(-(xTabSize() - 1), -(yTabSize() - 1), 0.0);


	for (i = 0; i < xTabSize(); i++)
		for (j = 0; j < yTabSize(); j++) {
			glPushMatrix();
			glTranslatef(i * 2.0, j * 2.0, 0.0);
			glScalef(0.8, 0.8, 0.3);
			if (m[i][j] == 1) {
				colorMAP();
			} else if (m[i][j] == 2) {
				updateCubeColor(); // Alterar a cor do cubo quando valor = 2 (casa visitada)
			}
			glPopMatrix();
		}

	glPopMatrix();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Calcula as coordenadas x, y e z da posição da camera em um sistema de coordenadas esfericas
	float x, y, z;
    x = distCamara * sin(Longitude * 3.14 / 180) * cos(Latitude * 3.14 / 180);
	z = distCamara * cos(Longitude * 3.14 / 180) * cos(Latitude * 3.14 / 180);
	y = distCamara * sin(Latitude * 3.14 / 180);

	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	drawRawMap(map);
	desenhaBoneco();
	desenhaFantasmas();
	mostrarPontuacao();
	mostrarMensagemPausa();
	mostrarControles();

	glFlush();
	glutSwapBuffers();
}


/*--------------------Rato----------------------------*/
// mouse callback
void rato(GLint button, GLint state, GLint x, GLint y)
{
	xRato = x;
	yRato = y;
}

// mouse motion callback
void moveRatoPress(int x, int y)
{
    Longitude += (x - xRato) * angRato;
    Latitude -= (y - yRato) * angRato;
    xRato = x;
    yRato = y;

    // Verificar limites
    if (Longitude >= MAX_LONGITUDE) Longitude = MAX_LONGITUDE;
    if (Longitude < MIN_LONGITUDE) Longitude = MIN_LONGITUDE;
    if (Latitude >= MAX_LATITUDE) Latitude = MAX_LATITUDE;
    if (Latitude < MIN_LATITUDE) Latitude = MIN_LATITUDE;

    printf("R(Lon,Lat)=(%6.2f,%6.2f)\n", Longitude, Latitude);

    glutPostRedisplay();
}

/*-----------------------------------------------------*/

/*-------------------Funções do Boneco--------------------------*/

void encontrarPosicaoInicialBoneco() {
	for (int i = 0; i < xTabSize(); i++) {
		for (int j = 0; j < yTabSize(); j++) {
			if (map[i][j] == 1) {
				// Definir posicao
				// Multiplicamos por 2.0 porque cada quadrado esta com uma distancia de 2 unidades
				bonecoX = i * 2.0;
				bonecoY = j * 2.0;
				bonecoXFinal = bonecoX;
				bonecoYFinal = bonecoY;
				return;
			}
		}
	}
}
void atualizarPosicaoBoneco(float deltaTime) {
	float deltaX = bonecoXFinal - bonecoX;
	float deltaY = bonecoYFinal - bonecoY;

	float distancia = sqrt(deltaX * deltaX + deltaY * deltaY);
	float maxDistancia = velocidade * deltaTime;

	if (distancia > maxDistancia) {
		bonecoX += (deltaX / distancia) * maxDistancia;
		bonecoY += (deltaY / distancia) * maxDistancia;
	} else {
		bonecoX = bonecoXFinal;
		bonecoY = bonecoYFinal;

		// Converte as coordenadas do mundo para indices do mapa
		int mapX = (int)(bonecoX / 2.0);
		int mapY = (int)(bonecoY / 2.0);

		// Muda a cor da casa para indicar que foi visitada (2 - Casa visitada, ao passar incrementa a pontuacao)
		if (map[mapX][mapY] == 1) {
			map[mapX][mapY] = 2;
			pontuacao++;
		}
	}
}

/*-----------------------------------------------------*/

// Função para reiniciar o jogo
void reiniciarJogo() {
	// Recarregar o mapa inicial
	carregarMapaInicial();

	// Redefinir os cubos com valor 2 para 1
	for (int i = 0; i < xTabSize(); i++) {
		for (int j = 0; j < yTabSize(); j++) {
			if (map[i][j] == 2) {
				map[i][j] = 1;
			}
		}
	}

	// Retorna a posição inicial do boneco
	encontrarPosicaoInicialBoneco();

	// Inicializar os fantasmas
	inicializarFantasmas();

	// Redefinir variáveis globais
	pontuacao = 0;
	jogoPausado = 0;
	jogoTerminado = 0;
}

// Função para verificar se o jogador tocou em um fantasma
int jogadorTocouFantasma() {
	for (int i = 0; i < nFantasmas; i++) {
		if ((bonecoX - fantasmas[i].x < 1.0 && bonecoX - fantasmas[i].x > -1.0) &&
			(bonecoY - fantasmas[i].y < 1.0 && bonecoY - fantasmas[i].y > -1.0)) {
			return 1;
			}
	}
	return 0;
}

// Função para verificar se o jogador passou por todas as casas do tabuleiro
int jogadorGanhou() {
	for (int i = 0; i < xTabSize(); i++) {
		for (int j = 0; j < yTabSize(); j++) {
			if (map[i][j] == 1) {
				return 0;
			}
		}
	}
	return 1;
}

/* Funções jogo*/
// Função para pausar o jogo
void pausarJogo() {
	jogoPausado = !jogoPausado;
}

// Função para abortar e reiniciar o jogo
void RestarGame() {
	reiniciarJogo();
	pontuacao = 0;
	jogoPausado = 0;
	jogoTerminado = 0;
}
/*------------*/

void update(int value) {

	//garante que o jogo enquanto estiver em pausa ou terminado nao atualize
	if (jogoPausado || jogoTerminado) {
		glutTimerFunc(TIME, update, TIME);
		return;
	}

	float deltaTime = TIME / 1000.0; // Converter TIME para segundos

	internalPos += internalVel * deltaTime;

	if (internalPos >= 1.0) {
		internalVel *= -1;
		internalPos = 1.0;
	}

	if (internalPos <= -1.0) {
		internalVel *= -1;
		internalPos = -1.0;
	}

	atualizarPosicaoBoneco(deltaTime); // Atualizar a posicao do boneco
	atualizarPosicoesFantasmas(deltaTime); // Atualizar a posicao dos fantasmas

	/*--Mensagem a dizer se ganhou ou perdeu*/
	if (jogadorTocouFantasma()) {
		printf("Perdeu!\n");
		jogoTerminado = 1;
		reiniciarJogo();
	} else if (jogadorGanhou()) {
		printf("Ganhou!\n");
		jogoTerminado = 1;
		reiniciarJogo();
	}
	/*--Mensagem a dizer se ganhou ou perdeu*/



	glutPostRedisplay();
	glutTimerFunc(TIME, update, TIME);
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, 2.0, 20.0);
	else
		glFrustum(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, 2.0, 20.0);
	/* gluPerspective(45.0, w / h, -10.0, 10.0); */

	glMatrixMode(GL_MODELVIEW);
}


/*--------------------teclado-------------------------*/

void teclasEspeciais(int key, int x, int y) {
	if (key == GLUT_KEY_F1) {
		pausarJogo();
	} else if (key == GLUT_KEY_F2) {
        RestarGame();
	} else {
		if (!jogoPausado && !jogoTerminado) {
			float newX = bonecoXFinal;
			float newY = bonecoYFinal;
			float step = 2.0;

			switch (key) {
				case GLUT_KEY_UP:
					newY += step;
				break;
				case GLUT_KEY_DOWN:
					newY -= step;
				break;
				case GLUT_KEY_LEFT:
					newX -= step;
				break;
				case GLUT_KEY_RIGHT:
					newX += step;
				break;
			}

			int mapX = (int)(newX / 2.0);
			int mapY = (int)(newY / 2.0);

			if (mapX >= 0 && mapX < xTabSize() && mapY >= 0 && mapY < yTabSize() && (map[mapX][mapY] == 1 || map[mapX][mapY] == 2)) {
				bonecoXFinal = newX;
				bonecoYFinal = newY;
			}
		}
	}

	glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y) {
    if (!jogoPausado && !jogoTerminado) {
        switch (key) {
            case 'a': // Roda para a esquerda
                Longitude -= dAlfa;
                if (Longitude < MIN_LONGITUDE) Longitude = MIN_LONGITUDE;
                break;
            case 'd': // Roda para a direita
                Longitude += dAlfa;
                if (Longitude > MAX_LONGITUDE) Longitude = MAX_LONGITUDE;
                break;
            case 'w': // Roda para cima
                Latitude += dAlfa;
                if (Latitude > MAX_LATITUDE) Latitude = MAX_LATITUDE;
                break;
            case 's': // Roda para baixo
                Latitude -= dAlfa;
                if (Latitude < MIN_LATITUDE) Latitude = MIN_LATITUDE;
                break;
            case '+': // Aproxima do tabuleiro
                distCamara -= dDistCamara;
                if (distCamara < 1.0) distCamara = 1.0;
                break;
            case '-': // Afasta-se do tabuleiro
                distCamara += dDistCamara;
                break;
        }
        glutPostRedisplay();
    }
}

/*-----------------------------------------------------*/



void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(1280, 720);
	glutCreateWindow("Pac-Man");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	
	glutSpecialFunc(teclasEspeciais);
	glutKeyboardFunc(teclado);
	glutMouseFunc(rato);
	glutMotionFunc(moveRatoPress);
	
	glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
	
	init();


	// PACMAN - MAP
	if (argc <= 1) {        // checking if the user give the map file
		printf("Please run as:\n");
		printf("%s <map file>", argv[0]);
		exit(0);
	}
	printf("Reading map...\n");
	openMapsFile(argv[1]);       // Opem map file 
	map = nextMap();             // read the first map from file
	printMap();                  // print the map to the console

	encontrarPosicaoInicialBoneco();
	encontrarPosicaoInicialBoneco();

	nFantasmas = numGhosts(); // Obter o número de fantasmas do ficheiro
	inicializarFantasmas();


	glutTimerFunc(TIME, update, TIME);

	glutMainLoop();
}