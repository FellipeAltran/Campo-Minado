#include <stdio.h>
#include <stdlib.h>


void printaTab (int bombas[][5], int tam, int clicados[][5], int resultante[][5]);
int receberCordenada (int clicados[][5],int matriz[][5]);
void calculaResultante (int bombas[][5], int resultante[][5]);
void clicar (int matriz[][5], int i, int j, int matriz2[][5]);


int main()
{
    int tam=5;
    int bombas[][5]= {{0,0,1,0,0},
        {1,0,0,1,0},
        {0,0,0,1,0},
        {0,1,0,0,1},
        {1,0,0,1,0}
    };

    int clicados[5][5];
    int resultante[5][5];

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            clicados[i][j]=0;
        }
    }

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            resultante[i][j]=0;
        }
    }
    calculaResultante(bombas,resultante);
    do
    {
        system("cls");
        fflush(stdin);

        printaTab(bombas,tam,clicados,resultante);

    }
    while(receberCordenada(clicados,resultante));

    return 0;
}

void printaTab (int bombas[][5], int tam, int clicados[][5], int resultante[][5])
{
    printf("   ");
    for (int i=1; i<=5; i++)
    {
        printf(" %d", i);
    }
    printf("\n\n");

    for(int i=0; i<tam; i++)
    {
        printf("%c  ", 'A'+i);
        printf("|");
        for(int j=0; j<tam; j++)
        {
            if (j>0)
            {
                printf(" ");
            }
            if (clicados[i][j]==0)
            {
                printf("#");
            }
            else if (resultante[i][j]>=0)
            {
                printf("%d", resultante[i][j]);
            }
            else
                printf("*");


        }
        printf("|");
        printf("\n");
    }
}

int receberCordenada (int clicados[][5],int matriz[][5])
{

    char linhaCodificada;
    int coluna, linha;

    printf("\nDigite as cordenadas: ");
    scanf("%c%d", &linhaCodificada,&coluna);
    fflush(stdin);

    linha = linhaCodificada-'A';
    coluna = coluna - 1;

    clicar(clicados,linha,coluna,matriz);

    if (matriz[linha][coluna]==-1){
        printf("perdeu otario\n");
        return 0;
    }

    return 1;

}

void calculaResultante (int bombas[][5], int resultante[][5])
{
    for (int i=0; i<5; i++)
    {
        for (int j=0; j<5; j++)
        {

            if (i>0)
            {
                resultante[i][j]+=bombas[i-1][j];
                if (j>0)
                    resultante[i][j]+=bombas[i-1][j-1];
                if (j<4)
                    resultante[i][j]+=bombas[i-1][j+1];
            }
            if (i<4)
            {
                resultante[i][j]+=bombas[i+1][j];
                if (j<4)
                    resultante[i][j]+=bombas[i+1][j+1];
                if (j>0)
                    resultante[i][j]+=bombas[i+1][j-1];
            }
            if (j>0)
                resultante[i][j]+=bombas[i][j-1];
            if (j<4)
                resultante[i][j]+=bombas[i][j+1];

            if (bombas[i][j]==1)
            {
                resultante[i][j]=-1;
            }

        }

    }
}

void clicar (int matriz[][5], int i, int j, int matriz2[][5])
{
    if (matriz[i][j]==1)
    {
        return;
    }
    matriz[i][j]=1;

    if (matriz2[i][j] == 0)
    {
        if (i>0)
        {
            clicar(matriz, i-1, j, matriz2);
            if (j>0)
                clicar(matriz, i-1,j-1,matriz2);
            if (j<4)
                clicar(matriz, i-1,j+1,matriz2);
        }
        if (i<4)
        {
            clicar(matriz, i+1,j,matriz2);
            if (j<4)
                clicar(matriz, i+1,j+1,matriz2);
            if (j>0)
                clicar(matriz, i+1,j-1,matriz2);
        }
        if (j>0)
            clicar(matriz, i,j-1,matriz2);
        if (j<4)
            clicar(matriz, i,j+1,matriz2);

    }
}

