#ifndef SNAKE_H
#define SNAKE_H

// Estrutura para representar um ponto no mapa
typedef struct {
    int x, y; // Coordenadas (x, y)
} Ponto;

// Estrutura para representar a cobra
typedef struct {
    Ponto corpo[100]; // Lista de pontos que formam o corpo
    int tamanho;      // Tamanho atual da cobra
    char direcao;     // Dire��o atual ('w', 'a', 's', 'd')
} Cobra;

void inicializar_jogo(Cobra *cobra, Ponto *fruta);
void desenhar_jogo(Cobra *cobra, Ponto *fruta);
void mover_cobra(Cobra *cobra);
int verificar_colisao(Cobra *cobra, Ponto *fruta);
void mudar_direcao(Cobra *cobra, char tecla);

#endif 