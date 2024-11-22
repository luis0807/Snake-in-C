#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h> // Biblioteca para usar _getch()
#include "Snake.h"

#define LARGURA 20
#define ALTURA 10

// Fun��o principal
int main() {
    Cobra cobra;
    Ponto fruta;
    int jogo_terminado = 0;

    inicializar_jogo(&cobra, &fruta); // Configura��es iniciais

    while (!jogo_terminado) {
        desenhar_jogo(&cobra, &fruta); // Mostra o estado atual do jogo
        if (_kbhit()) mudar_direcao(&cobra, _getch()); // Captura entrada do jogador
        mover_cobra(&cobra); // Move a cobra
        jogo_terminado = verificar_colisao(&cobra, &fruta); // Verifica colis�es
        Sleep(100); // Pausa para ajustar a velocidade do jogo
    }

    printf("Fim de Jogo!\n");
    return 0;
}

