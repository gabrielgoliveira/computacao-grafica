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

void imprimeQuadrado() {
  printf("=============================\n");
  printf("Aresta 1 (%.3f, %.3f)\n", quadrado.lados[0].x, quadrado.lados[0].y);
  printf("Aresta 2 (%.3f, %.3f)\n", quadrado.lados[1].x, quadrado.lados[1].y);
  printf("Aresta 3 (%.3f, %.3f)\n", quadrado.lados[2].x, quadrado.lados[2].y);
  printf("Aresta 4 (%.3f, %.3f)\n", quadrado.lados[3].x, quadrado.lados[3].y);
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
    quadrado.lados[i].y = quadrado.lados[i].x*seno - quadrado.lados[i].y*cosseno;
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
  float grauInicial = 40.0;
  while(1) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.7f, 0.5f, 0.4f);
     
    desenhaQuadrado(quadrado);
    if(quadrado.lados[0].x >= LARGURA_JANELA) {
      sentidoMovimento = -1;
    } else if(quadrado.lados[1].x < -LARGURA_JANELA) {
       sentidoMovimento = 1;
    }
    // transalacao(sentidoMovimento*GRAU_MOVIMENTO);
    rotacao(grauInicial);
    grauInicial += 1;
    if(grauInicial >= 360) grauInicial = 45;
    imprimeQuadrado();
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