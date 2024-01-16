#include "cobra.h"
//Rafael Carvalho Avidago Geraldo
typedef struct
{
    char nome[100];
    int pontos;
} Jogador;

void fazfruta(int x, int y, int girar)
{
    cor(20, 29, 23);
    rotacao(x + 10, y + 10, girar);             // <--- faz a fruta girar
    desenha_retangulo(x, y, TAM_SEGMENTO, TAM_SEGMENTO);
}

void desenhaScore(Cobra *cobra)
{
    int score = cobra->tamanho - 1;
    cor(20, 29, 23);
    fonte("assets/nokiafc22.ttf", 40);           // <--- Escolhe a fonte
    desenha_texto(50, 900, "pontos: %d", score); // <--- Desenha o texto na posição (x, y) = (50, 50)
}

void criaRank(Jogador rank[]){
    FILE *arq;
    int i;
    int result;
    arq = fopen("rank.txt", "wt");  // <--- Cria um arquivo texto para gravação
    for (i = 0; i<5;i++)
    {
      result = fprintf(arq,"%s %d\n", rank[i].nome, rank[i].pontos, i);  					  
      if (result == EOF)		    
	    printf("Erro na Gravacao\n");
    }
  fclose(arq);
    for (int i = 0; i < 5; i++){
        printf("%s %d\n", rank[i].nome, rank[i].pontos);
    }
}


int main()
{
    bool auxfruta = false, gameOver = false, game = false, menu = true;
    int x, y, girar = 0, velocidade, organizaRank = 0, organizaRankAux = 0;
    char organizaRankAuxNome[100];
    Cobra *cobra = cria_cobra();
    Jogador jogadores[5];

    printf("Digite seu nome para comecar o jogo: ");
    scanf("%s", &jogadores[5].nome);

    abre_janela(1280, 960);
    toca_som_em_loop("assets/gameMusic.mp3");
    // ==================================================RANK
    FILE *rank;
    // Abre um arquivo TEXTO para LEITURA
    rank = fopen("rank.txt", "a+");
    while (!feof(rank))
    {
        // Lê uma linha (inclusive com o '\n')
        for (int i = 0; i < 5; i++)
        {
            fscanf(rank, "%s %d\n", &jogadores[i].nome, &jogadores[i].pontos);
        }
    }
    fclose(rank);


    while (janela_esta_aberta())
    {
        if (gameOver == true)
        {
            if (organizaRank == 0)
            {   
                organizaRank = 1;
                int result;
                jogadores[5].pontos = cobra->tamanho - 1;
                for (int i = 0; i < 6; i++)
                {
                    for (int j = i + 1; j < 6; j++)
                    {
                        if (jogadores[i].pontos < jogadores[j].pontos)
                        {
                            organizaRankAux = jogadores[i].pontos;
                            jogadores[i].pontos = jogadores[j].pontos;
                            jogadores[j].pontos = organizaRankAux;
                            strcpy(organizaRankAuxNome, jogadores[i].nome);
                            strcpy(jogadores[i].nome, jogadores[j].nome);
                            strcpy(jogadores[j].nome, organizaRankAuxNome);
                        }
                    }
                }
                criaRank(jogadores);
            }
            desenha_imagem(640, 480, "assets/gameOver.png");
            cor(20, 29, 23);
                fonte("assets/nokiafc22.ttf", 40);           // <--- Escolhe a fonte
                desenha_texto(250, 255, "%s %d", jogadores[0].nome, jogadores[0].pontos); 
                desenha_texto(250, 305, "%s %d", jogadores[1].nome, jogadores[1].pontos); 
                desenha_texto(250, 355, "%s %d", jogadores[2].nome, jogadores[2].pontos); 
                desenha_texto(250, 405, "%s %d", jogadores[3].nome, jogadores[3].pontos); 
                desenha_texto(250, 455, "%s %d", jogadores[4].nome, jogadores[4].pontos); 

            if (tecla_pressionada(ESPACO))
            {
                game = true;
                gameOver = false;
                cobra = cria_cobra();
            }
        }
        if (menu == true)
        {
            desenha_imagem(640, 480, "assets/menu.png");
            if (botao_mouse_acabou_de_ser_apertado(BOTAO_ESQUERDO) == true && mouse_x > 180 && mouse_x < 420 && mouse_y > 583 && mouse_y < 680)
            {
                menu = false;
                game = true;
                velocidade = 1;
            }
            if (botao_mouse_acabou_de_ser_apertado(BOTAO_ESQUERDO) == true && mouse_x > 470 && mouse_x < 757 && mouse_y > 583 && mouse_y < 680)
            {
                menu = false;
                game = true;
                velocidade = 2;
            }
            if (botao_mouse_acabou_de_ser_apertado(BOTAO_ESQUERDO) == true && mouse_x > 814 && mouse_x < 1084 && mouse_y > 583 && mouse_y < 680)
            {
                menu = false;
                game = true;
                velocidade = 3;
            }
        }

        if (game == true)
        {
            organizaRank = 0;
            desenha_imagem(640, 480, "assets/background.png");
            desenha_cobra(cobra);
            desenhaScore(cobra);


            // colisoes
            // colisao cobra parede
            if (cobra->segmentos[0].x > 1279 || cobra->segmentos[0].x < 0 || cobra->segmentos[0].y > 959 || cobra->segmentos[0].y < 0)
            {
                // deu game over
                toca_som("assets/jump.wav");
                game = false;
                gameOver = true;
            }
            // colisao cobra cobra
            for (int i = 1; i < cobra->tamanho; i++)
            {
                if (cobra->segmentos[0].x == cobra->segmentos[i].x && cobra->segmentos[0].y == cobra->segmentos[i].y)
                {
                    toca_som("assets/jump.wav");
                    game = false;
                    gameOver = true;
                }
            }

             for (int z = 0; z < velocidade; z++){
            // colisao cobra e fruta
                if (cobra->segmentos[0].x == x && cobra->segmentos[0].y == y){
                    toca_som("assets/jump.wav");
                    cobra->tamanho += 1;
                    auxfruta = false;
                }
                    atualiza_cobra(cobra);
            }

            //spawn fruta
            if (auxfruta == false)
            {
                x = (rand() % 64) * 20;
                y = (rand() % 48) * 20;
                auxfruta = true;
            }
            fazfruta(x, y, girar);
            girar += 45;

            //movimentacao na main
            if (tecla_acabou_de_ser_apertada(CIMA) && cobra->direcao != BAIXO)
                cobra->direcao = CIMA;
            if (tecla_acabou_de_ser_apertada(BAIXO) && cobra->direcao != CIMA)
                cobra->direcao = BAIXO;
            if (tecla_acabou_de_ser_apertada(ESQUERDA) && cobra->direcao != DIREITA)
                cobra->direcao = ESQUERDA;
            if (tecla_acabou_de_ser_apertada(DIREITA) && cobra->direcao != ESQUERDA)
                cobra->direcao = DIREITA;
            int i = 0;
            while (i < 100000000)
            {
                i++;
            }
        }
    }

    fecha_janela();
}