#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define ALTURA_JANELA 20
#define LARGURA_JANELA 20
#define GRAU_MOVIMENTO 0.01
#define GRAU_ROTACAO 0.01;

typedef struct {
  float x;
  float y;
} Coordenada;

typedef struct {
  Coordenada lados[4];
} Quadrado;

Quadrado quadrado;

void desenhaQuadrado(Quadrado quad) {
  glBegin(GL_QUADS);//comeca a desenhar quadrilatros
    for(int i = 0; i < 4; i++) {
      glVertex2f(quad.lados[i].x, quad.lados[i].y);
    }
  glEnd();
}

void imprimeQuadradoPrintf() {
  printf("=============================\n");
  for(int i = 0; i < 4; i++) printf("Aresta %d (%.3f, %.3f)\n", i+1, quadrado.lados[i].x, quadrado.lados[i].y);
  printf("=============================\n");
}

void transalacao(float valor) {
  for(int i = 0; i < 4; i++) {
    quadrado.lados[i].x += valor;
    quadrado.lados[i].y += valor;
  }  
}

void rotacao(float valor) {
  float seno = sin(valor);
  float cosseno = cos(valor);

  for(int i = 0; i < 4; i++) {
    quadrado.lados[i].x = quadrado.lados[i].x*cosseno - quadrado.lados[i].y*seno;
    quadrado.lados[i].y = quadrado.lados[i].x*seno + quadrado.lados[i].y*cosseno;
  }  
}

void escala(float valor) {
  for(int i = 0; i < 4; i++) {
    quadrado.lados[i].x *= valor;
    quadrado.lados[i].y *= valor;
  }  
}

void init() {
 glClearColor(0,0,0,0);
 gluOrtho2D(-20,20,-20,20);
}

void inicializaQuadrado() {
  quadrado.lados[0].x = 5;
  quadrado.lados[0].y = 5;

  quadrado.lados[1].x = -5;
  quadrado.lados[1].y = 5;

  quadrado.lados[2].x = -5;
  quadrado.lados[2].y = -5;

  quadrado.lados[3].x = 5;
  quadrado.lados[3].y = -5;
}

void display() {
  int sentidoMovimento = 1;
  int sentidoCrescimento = 1;
  int tamInicialQuadrado = 5;
  float grauInicial = 90;
  float grauEscala = 1;
  while(1) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.7f, 0.5f, 0.4f);
     
    desenhaQuadrado(quadrado);

    if(quadrado.lados[0].x >= LARGURA_JANELA) {
      sentidoMovimento = -1;
    } else if(quadrado.lados[1].x < -LARGURA_JANELA) {
       sentidoMovimento = 1;
    }
    if(quadrado.lados[0].x > tamInicialQuadrado*2) {
      sentidoCrescimento = -1;
    } else {
      sentidoCrescimento = 1;
    }
    // transalacao(sentidoMovimento*GRAU_MOVIMENTO);
    // rotacao(grauInicial++);
    printf("Grau Escala : %.2f", grauEscala);
    grauEscala = (grauEscala) + (sentidoCrescimento)*0.00001;
    escala(grauEscala);
    imprimeQuadradoPrintf();
    glFlush();
  }
}

int main(int argc, char ** argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(0,0);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutCreateWindow("Animacao");
  init();
  inicializaQuadrado(); 
  glutDisplayFunc(display); 
  glutMainLoop();
}