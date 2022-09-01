#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include <Windows.h>




int menuCampo ();

int receberCordenada (int **clicados,int **resultante, int tam);
void clicar(int **clicados, int **resultante, int i, int j, int tam);
void printaTab (int **clicados, int **resultante, int tam);
void calculaResultante(int **resultante,int **bombas, int tam);
void random(int vi[], int vj[], int nBombas, int tam);
void zerar(int **matriz, int tam);

void preencherBombas(int **bombas, int vi[], int vj[], int nBombas, int tam);

int main()
{
    do{
    if (menuCampo()==1){
    int tam;
    int nBombas;
    printf("Digite o tamanho do campo minado[tamXtam]: ");
    scanf("%d", &tam);
    printf("Digite a quantidade de bombas: ");
    scanf("%d", &nBombas);

    int **bombas;
    bombas = malloc(sizeof(int *)*tam);
    for(int i=0; i<tam; i++){
    bombas[i] = malloc(sizeof(int)*tam);
    }
    int **clicados;
    clicados = malloc(sizeof(int *)*tam);
    for(int i=0; i<tam; i++){
    clicados[i] = malloc(sizeof(int)*tam);
    }
    int **resultante;
    resultante = malloc(sizeof(int *)*tam);
    for(int i=0; i<tam; i++){
    resultante[i] = malloc(sizeof(int)*tam);
    }

    zerar( bombas, tam);
    zerar( clicados, tam);
    zerar( resultante, tam);

    int vi[nBombas], vj[nBombas];
    random(vi,vj, nBombas, tam);
    fflush(stdin);

    preencherBombas(bombas,vi,vj,nBombas,tam);

    calculaResultante(resultante,bombas,tam);
    do
    {
        system("cls");
        fflush(stdin);
        printaTab(clicados,resultante,tam);

    }
    while(receberCordenada(clicados,resultante,tam));
    }else {
        printf("Saiu do jogo !");

        return 0;
    }
    }while(1);


    return 0;
}

void printaTab (int **clicados, int **resultante, int tam){

    printf("   ");
    for (int i=1; i<=tam; i++){
        printf(" %d", i);
    }
    printf("\n\n");

    for(int i=0; i<tam; i++){
        printf("%c  ", 'A'+i);
        printf("|");
        for(int j=0; j<tam; j++){
            if (j>0){
                printf(" ");
            }
            if (clicados[i][j]==0){
                printf("#");
            }else if (resultante[i][j]>=0){
                printf("%d", resultante[i][j]);
            }else{
                printf("*");
            }
        }
        printf("|");
        printf("\n");
    }
}

int receberCordenada (int **clicados,int **resultante, int tam){

    char linhaCodificada;
    int i, j;

    fflush(stdin);
    printf("\nDigite as cordenadas: ");
    scanf("%c%d", &i,&j);
    fflush(stdin);

    i = toupper(i)-'A';
    j = j - 1;

    if (resultante[i][j]==-1){
        system("cls");
        clicados[i][j]=1;
        fflush(stdin);
        printf("Game Over!\n");
        printaTab(clicados,resultante,tam);
        printf("\n");
        system("pause");
        system("cls");
        return 0;
    }

    clicar(clicados,resultante,i,j,tam);
    return 1;

}

void calculaResultante(int **resultante,int **bombas, int tam){
    for (int i=0; i<tam; i++){
        for (int j=0; j<tam; j++){
            if (i>0)
            {
                resultante[i][j]+=bombas[i-1][j];
                if (j>0)
                    resultante[i][j]+=bombas[i-1][j-1];
                if (j<tam-1)
                    resultante[i][j]+=bombas[i-1][j+1];
            }
            if (i<tam-1)
            {
                resultante[i][j]+=bombas[i+1][j];
                if (j<tam-1)
                    resultante[i][j]+=bombas[i+1][j+1];
                if (j>0)
                    resultante[i][j]+=bombas[i+1][j-1];
            }
            if (j>0)
                resultante[i][j]+=bombas[i][j-1];
            if (j<tam-1)
                resultante[i][j]+=bombas[i][j+1];

            if (bombas[i][j]==1)
            {
                resultante[i][j]=-1;
            }
        }
    }
}

void clicar(int **clicados, int **resultante, int i, int j, int tam){
    if (clicados[i][j]==1)
    {
        return;
    }
    clicados[i][j]=1;

    if (resultante[i][j] == 0)
    {
        if (i>0)
        {
            clicar(clicados,resultante, i-1, j, tam);
            if (j>0)
                clicar(clicados,resultante, i-1, j-1, tam);
            if (j<tam-1)
                clicar(clicados,resultante, i-1, j+1, tam);
        }
        if (i<tam-1)
        {
            clicar(clicados,resultante, i+1, j, tam);
            if (j<tam-1)
                clicar(clicados,resultante, i+1, j+1, tam);
            if (j>0)
                clicar(clicados,resultante, i+1, j-1, tam);
        }
        if (j>0)
            clicar(clicados,resultante, i, j-1, tam);
        if (j<tam-1)
            clicar(clicados,resultante, i, j+1, tam);

    }
}

int menuCampo (){

    int resp;

    printf("-------CAMPO MINADO--------\n\n");
    printf("---------------------------\n");
    printf("1-jogar:-------------------\n");
    printf("2-sair: -------------------\n");
    printf("---------------------------\n");

    scanf("%d", &resp);

    return resp;
}

void random(int vi[], int vj[], int nBombas, int tam){
    srand( (unsigned)time(NULL) );
  for(int k=0; k<nBombas;k++){
    vi[k]= rand() % (tam-1);
    vj[k]= rand() % (tam-1);
    for(int n=0; n<k; n++){
        if(vi[k]==vi[n] && vj[k]==vj[n])
        k--;
    }
  }
}

void zerar(int **matriz, int tam){
    for(int i=0; i<tam; i++)
    {
        for(int j=0; j<tam; j++)
        {
            matriz[i][j]=0;
        }
    }
}

void preencherBombas(int **bombas, int vi[], int vj[], int nBombas, int tam){
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            for(int k=0; k<nBombas; k++){
                if(i==vi[k]&&j==vj[k]){
                    bombas[i][j]=1;
                    break;
                }else
                    bombas[i][j]=0;
            }
        }
    }
}
