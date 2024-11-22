#include "Snake.h"

// Inicializa o jogo, definindo a posi��o inicial da cobra e da fruta
void inicializar_jogo(Cobra *cobra, Ponto *fruta) {
    cobra->tamanho = 1; // Tamanho inicial da cobra
    cobra->corpo[0] = (Ponto){LARGURA / 2, ALTURA / 2}; // Come�a no centro
    cobra->direcao = 'd'; // Come�a indo para a direita

    srand(time(NULL)); // Inicializa o gerador de n�meros aleat�rios
    *fruta = (Ponto){rand() % (LARGURA - 2) + 1, rand() % (ALTURA - 2) + 1}; // Posiciona a fruta
}

// Desenha o mapa, a cobra e a fruta na tela
void desenhar_jogo(Cobra *cobra, Ponto *fruta) {
    system("cls"); // Limpa a tela (use "clear" em sistemas Unix)
	int x, y, i;
    for (y = 0; y < ALTURA; y++) {
        for (x = 0; x < LARGURA; x++) {
            if (x == 0 || x == LARGURA - 1 || y == 0 || y == ALTURA - 1)
                printf("#"); // Paredes
            else if (x == fruta->x && y == fruta->y)
                printf("*"); // Fruta
            else {
                // Verifica se o ponto pertence ao corpo da cobra
                int parte_da_cobra = 0;
                for (i = 0; i < cobra->tamanho; i++) {
                    if (cobra->corpo[i].x == x && cobra->corpo[i].y == y) {
                        printf("O"); // Desenha o corpo da cobra
                        parte_da_cobra = 1;
                        break;
                    }
                }
                if (!parte_da_cobra) printf(" "); // Espa�o vazio
            }
        }
        printf("\n");
    }
}

// Move a cobra na dire��o atual
void mover_cobra(Cobra *cobra) {
    // Move cada parte do corpo para a posi��o da parte anterior
    int i;
    for (i = cobra->tamanho - 1; i > 0; i--)
        cobra->corpo[i] = cobra->corpo[i - 1];

    // Move a cabe�a da cobra na dire��o atual
    if (cobra->direcao == 'w') cobra->corpo[0].y--; // Para cima
    else if (cobra->direcao == 'a') cobra->corpo[0].x--; // Para a esquerda
    else if (cobra->direcao == 's') cobra->corpo[0].y++; // Para baixo
    else if (cobra->direcao == 'd') cobra->corpo[0].x++; // Para a direita

    // Permite que a cobra atravesse as paredes e apare�a do outro lado
    if (cobra->corpo[0].x <= 0) cobra->corpo[0].x = LARGURA - 2;
    if (cobra->corpo[0].x >= LARGURA - 1) cobra->corpo[0].x = 1;
    if (cobra->corpo[0].y <= 0) cobra->corpo[0].y = ALTURA - 2;
    if (cobra->corpo[0].y >= ALTURA - 1) cobra->corpo[0].y = 1;
}

// Verifica se a cobra colidiu consigo mesma ou comeu a fruta
int verificar_colisao(Cobra *cobra, Ponto *fruta) {
    // Verifica colis�o com o pr�prio corpo
    int i;
    for (i = 1; i < cobra->tamanho; i++) {
        if (cobra->corpo[0].x == cobra->corpo[i].x && cobra->corpo[0].y == cobra->corpo[i].y)
            return 1; // Jogo termina
    }

    // Verifica se comeu a fruta
    if (cobra->corpo[0].x == fruta->x && cobra->corpo[0].y == fruta->y) {
        cobra->tamanho++; // Aumenta o tamanho da cobra
        // Posiciona a nova fruta, garantindo que n�o esteja dentro da cobra
        do {
            fruta->x = rand() % (LARGURA - 2) + 1;
            fruta->y = rand() % (ALTURA - 2) + 1;
        } while (cobra->corpo[0].x == fruta->x && cobra->corpo[0].y == fruta->y);
    }
    return 0; // Sem colis�es
}

// Altera a dire��o da cobra com base na tecla pressionada
void mudar_direcao(Cobra *cobra, char tecla) {
    // Evita que a cobra se mova na dire��o oposta � atual
    if ((tecla == 'w' && cobra->direcao != 's') ||
        (tecla == 'a' && cobra->direcao != 'd') ||
        (tecla == 's' && cobra->direcao != 'w') ||
        (tecla == 'd' && cobra->direcao != 'a'))
        cobra->direcao = tecla;
}