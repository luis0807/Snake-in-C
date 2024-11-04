#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Para usar getch() e kbhit()
#include <time.h>
#include <windows.h> // Para Sleep()

#define LARGURA 60
#define ALTURA 20

// Variáveis globais
int gameOver;
int x, y, frutaX, frutaY, pontuacao;
int caudaX[100], caudaY[100]; // Para armazenar as posições da cauda
int nCauda;                   // Tamanho da cauda
enum eDirecao
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
enum eDirecao dir;

// Função para configurar o jogo
void Setup()
{
    gameOver = 0;
    dir = STOP;
    x = LARGURA / 2;
    y = ALTURA / 2;
    frutaX = rand() % (LARGURA - 2) + 1;
    frutaY = rand() % (ALTURA - 2) + 1;
    pontuacao = 0;
    nCauda = 0;
}

// Função para desenhar o tabuleiro
void Desenhar()
{
    system("cls"); // Limpa a tela no Windows

    // Desenha a parte superior
    for (int i = 0; i < LARGURA; i++)
        printf("%c", 219);
    printf("\n");

    // Desenha as paredes laterais e o conteúdo interno
    for (int i = 0; i < ALTURA - 2; i++)
    {
        for (int j = 0; j < LARGURA; j++)
        {
            if (j == 0 || j == LARGURA - 1)
            {
                printf("%c", 219); // Paredes laterais
            }
            else if (i == y && j == x)
            {
                printf("%c", 178); // Cabeça da cobra
            }
            else if (i == frutaY && j == frutaX)
            {
                printf("%c", 254); // Fruta
            }
            else
            {
                int printCauda = 0;
                for (int k = 0; k < nCauda; k++)
                {
                    if (caudaX[k] == j && caudaY[k] == i)
                    {
                        printf("%c", 178); // Corpo da cobra
                        printCauda = 1;
                    }
                }
                if (!printCauda)
                {
                    printf(" "); // Espaço vazio
                }
            }
        }
        printf("\n");
    }

    // Desenha a parte inferior
    for (int i = 0; i < LARGURA; i++)
        printf("%c", 219);
    printf("\n");

    printf("Pontuação: %d\n", pontuacao);
}

// Função para controlar a entrada de comandos
void Entrada()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = 1; // Sair do jogo
            break;
        }
    }
}

// Função para lógica do jogo
void Logica()
{
    // Movimenta a cauda
    int prevX = caudaX[0];
    int prevY = caudaY[0];
    int prev2X, prev2Y;
    caudaX[0] = x;
    caudaY[0] = y;

    for (int i = 1; i < nCauda; i++)
    {
        prev2X = caudaX[i];
        prev2Y = caudaY[i];
        caudaX[i] = prevX;
        caudaY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Movimenta a cabeça da cobra
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Verifica se a cobra bate nas paredes
    if (x >= LARGURA - 1)
        x = 0;
    else if (x < 0)
        x = LARGURA - 2;
    if (y >= ALTURA - 1)
        y = 0;
    else if (y < 0)
        y = ALTURA - 2;

    // Verifica se a cobra bateu na própria cauda
    for (int i = 0; i < nCauda; i++)
    {
        if (caudaX[i] == x && caudaY[i] == y)
        {
            gameOver = 1;
        }
    }

    // Se a cobra comer a fruta
    if (x == frutaX && y == frutaY)
    {
        pontuacao += 10;
        frutaX = rand() % (LARGURA - 2) + 1;
        frutaY = rand() % (ALTURA - 2) + 1;
        nCauda++;
    }
}

int main()
{
    srand(time(0)); // Inicializa a semente de aleatoriedade
    Setup();

    while (!gameOver)
    {
        Desenhar();
        Entrada();
        Logica();
        Sleep(50); // Retarda o jogo para não ser muito rápido
    }

    printf("Fim de jogo! Sua pontuação final foi: %d\n", pontuacao);

    return 0;
}
