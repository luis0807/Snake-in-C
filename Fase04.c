#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // Biblioteca para usar _getch(), _kbhit() e _sleep()

#define LARGURA 20
#define ALTURA 10

// Estrutura para representar um ponto no mapa
typedef struct
{
    int x, y; // Coordenadas (x, y)
} Ponto;

// Estrutura para representar a cobra
typedef struct
{
    Ponto corpo[100]; // Lista de pontos que formam o corpo
    int tamanho;      // Tamanho atual da cobra
    char direcao;     // Direcao atual ('w', 'a', 's', 'd')
} Cobra;

//Estrutura para representar o login e a Maior Pontuacao;
typedef struct
{
    char nome[50];
    int maiorPontuacao;
} Jogador;

// Inicializa o jogo, definindo a posicao inicial da cobra e da fruta
void inicializar_jogo(Cobra *cobra, Ponto *fruta)
{
    cobra->tamanho = 1;                                 // Tamanho inicial da cobra
    cobra->corpo[0] = (Ponto){LARGURA / 2, ALTURA / 2}; // Comeca no centro
    cobra->direcao = 'd';                               // Comeca indo para a direita

    srand(time(NULL));                                                       // Inicializa o gerador de numeros aleatorios
    *fruta = (Ponto){rand() % (LARGURA - 2) + 1, rand() % (ALTURA - 2) + 1}; // Posiciona a fruta
}

// Desenha o mapa, a cobra e a fruta na tela
void desenhar_jogo(Cobra *cobra, Ponto *fruta, int pontuacao)
{
    int x ,y, i;
    system("cls");// Limpa a tela (use "clear" em sistemas Unix)
    printf("Pontuacao: %d\n", pontuacao);
    for (y = 0; y < ALTURA; y++)
    {
        for (x = 0; x < LARGURA; x++)
        {
            if (x == 0 || x == LARGURA - 1 || y == 0 || y == ALTURA - 1)
                printf("%c", 219); // Paredes
            else if (x == fruta->x && y == fruta->y)
                printf("%c", 254); // Fruta
            else
            {
                // Verifica se o ponto pertence ao corpo da cobra
                int parte_da_cobra = 0;
                for (i = 0; i < cobra->tamanho; i++)
                {
                    if (cobra->corpo[i].x == x && cobra->corpo[i].y == y)
                    {
                        printf("%c", 178); // Desenha o corpo da cobra
                        parte_da_cobra = 1;
                        break;
                    }
                }
                if (!parte_da_cobra)
                    printf(" "); // Espaco vazio
            }
        }
        printf("\n");
    }
}

// Move a cobra na direcao atual
void mover_cobra(Cobra *cobra)
{
    // Move cada parte do corpo para a posicao da parte anterior
    int i;
    for (i = cobra->tamanho - 1; i > 0; i--)
        cobra->corpo[i] = cobra->corpo[i - 1];

    // Move a cabeca da cobra na direcao atual
    if (cobra->direcao == 'w')
        cobra->corpo[0].y--; // Para cima
    else if (cobra->direcao == 'a')
        cobra->corpo[0].x--; // Para a esquerda
    else if (cobra->direcao == 's')
        cobra->corpo[0].y++; // Para baixo
    else if (cobra->direcao == 'd')
        cobra->corpo[0].x++; // Para a direita

    // Permite que a cobra atravesse as paredes e apareca do outro lado
    if (cobra->corpo[0].x <= 0)
        cobra->corpo[0].x = LARGURA - 2;
    if (cobra->corpo[0].x >= LARGURA - 1)
        cobra->corpo[0].x = 1;
    if (cobra->corpo[0].y <= 0)
        cobra->corpo[0].y = ALTURA - 2;
    if (cobra->corpo[0].y >= ALTURA - 1)
        cobra->corpo[0].y = 1;
}

// Verifica se a cobra colidiu consigo mesma ou comeu a fruta
int verificar_colisao(Cobra *cobra, Ponto *fruta, int *pontuacao)
{
    // Verifica colisao com o proprio corpo
    int i;
    for (i = 1; i < cobra->tamanho; i++)
    {
        if (cobra->corpo[0].x == cobra->corpo[i].x && cobra->corpo[0].y == cobra->corpo[i].y)
            return 1; // Jogo termina
    }

    // Verifica se comeu a fruta
    if (cobra->corpo[0].x == fruta->x && cobra->corpo[0].y == fruta->y)
    {
    	
        cobra->tamanho++; // Aumenta o tamanho da cobra
        // Posiciona a nova fruta, garantindo que nao esteja dentro da cobra
        (*pontuacao)++; // Uma fruta == mais 1 Ponto;
        do
        {
            fruta->x = rand() % (LARGURA - 2) + 1;
            fruta->y = rand() % (ALTURA - 2) + 1;
        } while (cobra->corpo[0].x == fruta->x && cobra->corpo[0].y == fruta->y);
    }
    return 0; // Sem colisoes
}

// Altera a direcao da cobra com base na tecla pressionada
void mudar_direcao(Cobra *cobra, char tecla)
{
    // Evita que a cobra se mova na direcao oposta a atual
    if ((tecla == 'w' && cobra->direcao != 's') ||
        (tecla == 'a' && cobra->direcao != 'd') ||
        (tecla == 's' && cobra->direcao != 'w') ||
        (tecla == 'd' && cobra->direcao != 'a'))
        cobra->direcao = tecla;
}

//Abre o Arquivo .txt e salva a maior Pontuacao do Login;
void salvar_maior_pontuacao(Jogador *jogador)
{
    FILE *arquivo = fopen("recordefase4.txt", "w");
    if (arquivo)
    {
        fprintf(arquivo, "%s %d\n", jogador->nome, jogador->maiorPontuacao);
        fclose(arquivo);
    }
}

//Abre o Arquivo para mostrar a maior Pontuacao;
void carregar_maior_pontuacao(Jogador *jogador) // Função para acessar o arquivo do maior recorde;
{
    FILE *arquivo = fopen("recordefase4.txt", "r");
    if (arquivo)
    {
        fscanf(arquivo, "%s %d", jogador->nome, &jogador->maiorPontuacao);
        fclose(arquivo);
    }
    else
    {
        strcpy(jogador->nome, "Fulano");
        jogador->maiorPontuacao = 0;
    }
}

// Funcao principal
int main()
{
    Cobra cobra;
    Ponto fruta;
    Jogador jogador;
    int pontuacao = 0, jogo_terminado = 0;
    char iniciar_jogo;
    inicializar_jogo(&cobra, &fruta); // Configuracoes iniciais

    printf("Iniciar Jogo -> 'S'");
    printf("\nSair do Jogo -> Pressione qualquer tecla");
    
    iniciar_jogo = _getch();
    if (iniciar_jogo == 'S' || iniciar_jogo == 's')
    {
    	carregar_maior_pontuacao(&jogador);

    	printf("\nBem-vindo ao jogo da Cobrinha!\n");
    	printf("Maior pontuacao: %s: %d\n", jogador.nome, jogador.maiorPontuacao);
    	printf("Login: ");
    	scanf("%s", jogador.nome);

        while (!jogo_terminado)
        {
            desenhar_jogo(&cobra, &fruta, pontuacao); // Mostra o estado atual do jogo
            if (_kbhit())
                mudar_direcao(&cobra, _getch());                // Captura entrada do jogador
            mover_cobra(&cobra);                                // Move a cobra
            jogo_terminado = verificar_colisao(&cobra, &fruta, &pontuacao); // Verifica colisoes
            _sleep(60);                                        // Pausa para ajustar a velocidade do jogo
        }
    }

     printf("\nFim de Jogo!\n");
    if (pontuacao > jogador.maiorPontuacao)
    {
        jogador.maiorPontuacao = pontuacao;
        salvar_maior_pontuacao(&jogador);
        printf("\nNovo recorde!\n");
    }
    
    return 0;
}
