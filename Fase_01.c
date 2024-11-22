#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // Biblioteca para usar _getch()

#define LARGURA 20
#define ALTURA 10

// Estrutura para representar um ponto no mapa
typedef struct {
    int x, y; // Coordenadas (x, y)
} Ponto;

// Estrutura para representar a cobra
typedef struct {
    Ponto corpo[100]; // Lista de pontos que formam o corpo
    int tamanho;      // Tamanho atual da cobra
    char direcao;     // Direção atual ('w', 'a', 's', 'd')
} Cobra;

// Inicializa o jogo, definindo a posição inicial da cobra e da fruta
void inicializar_jogo(Cobra *cobra, Ponto *fruta) {
    cobra->tamanho = 1; // Tamanho inicial da cobra
    cobra->corpo[0] = (Ponto){LARGURA / 2, ALTURA / 2}; // Começa no centro
    cobra->direcao = 'd'; // Começa indo para a direita

    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    *fruta = (Ponto){rand() % (LARGURA - 2) + 1, rand() % (ALTURA - 2) + 1}; // Posiciona a fruta
}

// Desenha o mapa, a cobra e a fruta na tela
void desenhar_jogo(Cobra *cobra, Ponto *fruta) {
    system("cls"); // Limpa a tela (use "clear" em sistemas Unix)

    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            if (x == 0 || x == LARGURA - 1 || y == 0 || y == ALTURA - 1)
                printf("%c",219); // Paredes
            else if (x == fruta->x && y == fruta->y)
                printf("*"); // Fruta
            else {
                // Verifica se o ponto pertence ao corpo da cobra
                int parte_da_cobra = 0;
                for (int i = 0; i < cobra->tamanho; i++) {
                    if (cobra->corpo[i].x == x && cobra->corpo[i].y == y) {
                        printf("O"); // Desenha o corpo da cobra
                        parte_da_cobra = 1;
                        break;
                    }
                }
                if (!parte_da_cobra) printf(" "); // Espaço vazio
            }
        }
        printf("\n");
    }
}

// Move a cobra na direção atual
void mover_cobra(Cobra *cobra) {
    // Move cada parte do corpo para a posição da parte anterior
    for (int i = cobra->tamanho - 1; i > 0; i--)
        cobra->corpo[i] = cobra->corpo[i - 1];

    // Move a cabeça da cobra na direção atual
    if (cobra->direcao == 'w') cobra->corpo[0].y--; // Para cima
    else if (cobra->direcao == 'a') cobra->corpo[0].x--; // Para a esquerda
    else if (cobra->direcao == 's') cobra->corpo[0].y++; // Para baixo
    else if (cobra->direcao == 'd') cobra->corpo[0].x++; // Para a direita

    // Permite que a cobra atravesse as paredes e apareça do outro lado
    if (cobra->corpo[0].x <= 0) cobra->corpo[0].x = LARGURA - 2;
    if (cobra->corpo[0].x >= LARGURA - 1) cobra->corpo[0].x = 1;
    if (cobra->corpo[0].y <= 0) cobra->corpo[0].y = ALTURA - 2;
    if (cobra->corpo[0].y >= ALTURA - 1) cobra->corpo[0].y = 1;
}

// Verifica se a cobra colidiu consigo mesma ou comeu a fruta
int verificar_colisao(Cobra *cobra, Ponto *fruta) {
    // Verifica colisão com o próprio corpo
    for (int i = 1; i < cobra->tamanho; i++) {
        if (cobra->corpo[0].x == cobra->corpo[i].x && cobra->corpo[0].y == cobra->corpo[i].y)
            return 1; // Jogo termina
    }

    // Verifica se comeu a fruta
    if (cobra->corpo[0].x == fruta->x && cobra->corpo[0].y == fruta->y) {
        cobra->tamanho++; // Aumenta o tamanho da cobra
        // Posiciona a nova fruta, garantindo que não esteja dentro da cobra
        do {
            fruta->x = rand() % (LARGURA - 2) + 1;
            fruta->y = rand() % (ALTURA - 2) + 1;
        } while (cobra->corpo[0].x == fruta->x && cobra->corpo[0].y == fruta->y);
    }
    return 0; // Sem colisões
}

// Altera a direção da cobra com base na tecla pressionada
void mudar_direcao(Cobra *cobra, char tecla) {
    // Evita que a cobra se mova na direção oposta à atual
    if ((tecla == 'w' && cobra->direcao != 's') ||
        (tecla == 'a' && cobra->direcao != 'd') ||
        (tecla == 's' && cobra->direcao != 'w') ||
        (tecla == 'd' && cobra->direcao != 'a'))
        cobra->direcao = tecla;
}

// Função principal
int main() {
    Cobra cobra;
    Ponto fruta;
    int jogo_terminado = 0;

    inicializar_jogo(&cobra, &fruta); // Configurações iniciais

    while (!jogo_terminado) {
        desenhar_jogo(&cobra, &fruta); // Mostra o estado atual do jogo
        if (_kbhit()) mudar_direcao(&cobra, _getch()); // Captura entrada do jogador
        mover_cobra(&cobra); // Move a cobra
        jogo_terminado = verificar_colisao(&cobra, &fruta); // Verifica colisões
        _sleep(200); // Pausa para ajustar a velocidade do jogo
    }

    printf("Fim de Jogo!\n");
    return 0;
}
