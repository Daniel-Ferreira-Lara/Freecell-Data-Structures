#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define RED "\e[0;31m\e[47m"
#define GRN "\e[0;32m\e[47m"
#define reset "\e[0m\e[0;30m\e[47m"
enum naipes
{
    copas = 3,
    ouros,
    paus,
    espadas
};
typedef struct no
{
    int card[2];
    struct no *prox;
} tCarta;
tCarta *primMonte = NULL;
tCarta *mesa[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}, *naipe[] = {NULL, NULL, NULL, NULL}, *temp[] = {NULL, NULL, NULL, NULL};
tCarta *moved = NULL; //recent moved card
int end = 0;
void geraBaralho();
void embaralha();
void distribuirMesa();
void print(tCarta *atual);
void imprimir();
void print(tCarta *atual);
int moveDefaultMesa(char inicio[], int limini, tCarta *largada[]);
int moveDefaultNaipe(char inicio[], int limini, tCarta *largada[]);
int moveDefaultTemp(char inicio[], int limini, tCarta *largada[]);
void erros(int retorno, char comeco[], char fim[], char algofim[]);
void destruir(tCarta *algo[], int n);
void destroi();

int main(int argc, char **argv)
{
    system("color F0");
    int op;
    srand(time(NULL));
    geraBaralho();
    embaralha();
    distribuirMesa();
    while (op != 8)
    {
        imprimir();
        printf("(1)Move Mesa-Temp\n(2)Move Mesa-Naipe\n(3)Move Temp-Mesa\n(4)Move Naipe-Temp\n(5)Move Temp-Naipe\n(6)Move Naipe-Mesa\n(7)Move Mesa-Mesa\n(8)Sair\nOpcao: ");
        scanf("%d", &op);
        printf(reset);
        getchar();
        switch (op)
        {
        case 1: //Mesa-Temp
            erros(moveDefaultTemp("a mesa", 7, mesa), "Mesa", "Temporario", "cheio");
            break;
        case 2: //Mesa-Naipe
            erros(moveDefaultNaipe("a mesa", 7, mesa), "Mesa", "Naipe", "sem nada");
            break;
        case 3: //Temp-Mesa
            erros(moveDefaultMesa("o temporario", 3, temp), "Temporario", "Mesa", "sem nada");
            break;
        case 4: //Naipe-Temp
            erros(moveDefaultTemp("o naipe", 7, naipe), "Naipe", "Temporario", "cheio");
            break;
        case 5: //Temp-Naipe
            erros(moveDefaultNaipe("o temporario", 3, temp), "Temporario", "Naipe", "sem nada");
            break;
        case 6: //Naipe-Mesa
            erros(moveDefaultMesa("o naipe", 3, naipe), "Naipe", "Mesa", "vazio");
            break;
        case 7: //Mesa-Mesa
            erros(moveDefaultMesa("a mesa", 7, mesa), "Mesa", "Mesa", "sem nada");
            break;
        case 8: //Saida
            break;
        default:
            printf(RED "Opcao Invalida.\n" reset);
            break;
        }
    }
    destroi();
    system("pause");
    return 0;
}

void geraBaralho()
{
    int i, j;
    tCarta *novo;
    for (i = 0; i < 13; i++)
        for (j = copas; j < espadas + 1; j++)
        {
            novo = (tCarta *)malloc(sizeof(tCarta));
            novo->card[0] = i;
            novo->card[1] = j;
            novo->prox = naipe[j];
            naipe[j] = novo;
        }
}

void embaralha()
{
    srand(time(NULL));
    int i, j, random;
    tCarta *last = NULL;
    for (i = 0; i < 13; i++)
        for (j = copas; j <= espadas; j++)
        {
            random = rand() % 8;
            last = mesa[random];
            mesa[random] = naipe[j];
            naipe[j] = naipe[j]->prox;
            mesa[random]->prox = last;
        }
    j = 0, last = NULL;
    while (true)
    {
        if (mesa[j] == NULL)
        {
            j++;
            if (j > 7)
                break;
        }
        random = rand() % 4;
        last = naipe[random];
        naipe[random] = mesa[j];
        mesa[j] = mesa[j]->prox;
        naipe[random]->prox = last;
    }
}

void distribuirMesa()
{
    srand(time(NULL));
    int i, j = 0, n = 7;
    tCarta *last = NULL;
    while (n--)
        for (i = 0; i < 8; i++)
        {
            if (naipe[j] == NULL)
            {
                j++;
                if (j > 3)
                    break;
            }
            last = mesa[i];
            mesa[i] = naipe[j];
            naipe[j] = naipe[j]->prox;
            mesa[i]->prox = last;
        }
}

void imprimir()
{
    int i;
    tCarta *atual;
    
    //printf("\t\t\t[TEMPORARIO]:\n");
    //printaCartas(atual);
    printf("[TEMPORARIO]:\t\t");
    for (i = 0; i < 4; i++){
		atual = temp[i];
        if (temp[i] != NULL)
            if (atual == moved)
                printf(GRN "%d:[%d%c] " reset, i + 1, temp[i]->card[0] + 1, temp[i]->card[1]);
            else if (temp[i]->card[1] == copas || temp[i]->card[1] == ouros)
                printf(RED "%d:[%d/%c] " reset, i + 1, temp[i]->card[0] + 1, temp[i]->card[1]);
            else
                printf("%d:[%d/%c] ", i + 1, temp[i]->card[0] + 1, temp[i]->card[1]);
        else
            printf("%d:[   ] ", i + 1);
	}
    puts("\n");
    //atual = naipe;
    //printf("\t\t\t[NAIPES]:\n");
    //printaCartas(atual);
    for (i = 0; i < 4; i++)
    {
        printf("[NAIPE]: %d:\t", i + 1);
        atual = naipe[i];
        print(atual);
        puts("");
    }
    puts("");
    for (i = 0; i < 8; i++)
    {
        printf("[MESA] %d:\t", i + 1);
        atual = mesa[i];
        print(atual);
        puts("");
    }
    puts("");
}

void print(tCarta *atual)
{
    while (atual != NULL)
    {
        if (atual != NULL)
            if (atual == moved)
                printf(GRN "[%2d/%c]" reset, atual->card[0] + 1, atual->card[1]);
            else if (atual->card[1] == copas || atual->card[1] == ouros)
                printf(RED "[%2d/%c]" reset, atual->card[0] + 1, atual->card[1]);
            else
                printf("[%2d/%c]", atual->card[0] + 1, atual->card[1]);
        atual = atual->prox;
    }
}

int moveDefaultMesa(char inicio[], int limini, tCarta *largada[])
{
    int ini, fim;
    tCarta *aux;
    printf("digite %s e a mesa: ", inicio);
    scanf("%d %d", &ini, &fim);
    ini--, fim--;
    if (ini > limini || fim > 7)
        return 0;
    else if (largada[ini] == NULL)
        return -1;
    else if (largada[ini]->card[0] != mesa[fim]->card[0] - 1)
        return -3;
    else if ((largada[ini]->card[1] < 5 && mesa[fim]->card[1] < 5) || (largada[ini]->card[1] > 4 && mesa[fim]->card[1] > 4))
        return -3;
    aux = largada[ini];
    largada[ini] = largada[ini]->prox;
    aux->prox = mesa[fim];
    mesa[fim] = aux;
    moved = aux;
    end = fim;
    return 1;
}

int moveDefaultNaipe(char inicio[], int limini, tCarta *largada[])
{
    int ini, fim;
    tCarta *aux;
    printf("digite %s e o naipe: ", inicio);
    scanf("%d %d", &ini, &fim);
    ini--, fim--;
    if (ini > limini || fim > 3)
        return 0;
    else if ((largada[ini] == NULL))
        return -1;
    else if (naipe[fim] == NULL)
    {
        if ((largada[ini]->card[0] != 0))
            return -3;
    }
    else if ((naipe[fim]->card[0] != largada[ini]->card[0] - 1) || (naipe[fim]->card[1] != largada[ini]->card[1]))
        return -3;
    aux = largada[ini];
    largada[ini] = largada[ini]->prox;
    aux->prox = naipe[fim];
    naipe[fim] = aux;
    moved = aux;
    return 1;
}

int moveDefaultTemp(char inicio[], int limini, tCarta *largada[])
{
    int ini, fim;
    tCarta *aux;
    printf("digite %s e o temporario: ", inicio);
    scanf("%d %d", &ini, &fim);
    ini--, fim--;
    if (ini > limini || fim > 3)
        return 0;
    else if (largada[ini] == NULL)
        return -1;
    else if (temp[fim] != NULL)
        return -2;
    aux = largada[ini];
    largada[ini] = largada[ini]->prox;
    aux->prox = temp[fim];
    temp[fim] = aux;
    moved = temp[fim];
    return 1;
}

void erros(int retorno, char comeco[], char fim[], char algofim[])
{
    switch (retorno)
    {
    case 1:
        puts(GRN "\nCarta movida com sucesso :)\n" reset);
        break;
    case 0:
        puts(RED "\nLocais inexistentes\n" reset);
        break;
    case -1:
        printf(RED "\n%s esta sem nada\n" reset, comeco);
        break;
    case -2:
        printf(RED "\n%s esta %s\n" reset, fim, algofim);
        break;
    case -3:
        puts(RED "\nNao eh possivel mover\n" reset);
        break;
    default:
        puts(RED "\nMovimento invalido :/\n" reset);
        break;
    }
}

void destruir(tCarta *algo[], int n)
{
    tCarta *atual, *destroi;
    int i;
    for (i = 0; i < n; i++)
    {
        atual = algo[i];
        while (atual != NULL)
        {
            destroi = atual;
            atual = atual->prox;
            free(destroi);
        }
    }
    free(atual);
}

void destroi()
{
    destruir(naipe, 4);
    destruir(temp, 4);
    destruir(mesa, 8);
}