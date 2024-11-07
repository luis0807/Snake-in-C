#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 60
#define HEIGHT 30

//Variaveis globais
int gameOver, FruitX, FruitY;

enum dir
{
    Stop = 0,
    Left,
    Right,
    Up,
    Down
};
enum dir dir;

typedef struct
{
    int x, y;
    int SnakeLen, lenX[100], lenY[100];
} Snake;

Snake snake;

void setup()
{
    gameOver = 0;
    dir = Stop;
    snake.x = HEIGHT / 2;
    snake.y = WIDTH / 2;
    snake.SnakeLen = 0;
    FruitX = rand() % (HEIGHT - 2) + 1;
    FruitY = rand() % (WIDTH - 2) + 1;

}

void menu()
{
    printf("\n--> Iniciar Jogo!");
    printf("\n--> Estatisticas");
}

void drawMap()
{
    system("cls");

    int i, j, x = HEIGHT / 2, y = WIDTH / 2;

    for (i = 0; i < WIDTH; i++) // PARTE SUPERIOR DO MAPA
    {
        printf("%c", 219);
    }

    printf("\n");

    for (i = 0; i < HEIGHT - 2; i++) // PARTE ESQUERDA E DIREITA DO MAPA
    {
        printf("%c", 219);

        for (j = 0; j < WIDTH - 2; j++)
        {
            printf("%c", 176);
        }
        printf("%c\n", 219);
    }

    for (i = 0; i < WIDTH; i++) // PARTE INFERIOR DO MAPA
    {
        printf("%c", 219);
    }
}

int main()
{
    int i, j, FB = 0;

    // FrameBuffer 10 FPS
    while (FB == 0)
    {
        drawMap(i, j);
        Sleep(10);
    }

    return 0;
}