#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include <Windows.h>


void printCampoMinado();
void printGameOver();
void printVictory();

int menuCampo ();

int receberCordenada (int **clicados,int **resultante, int tam,int nBombas);
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
    while(receberCordenada(clicados,resultante,tam,nBombas));
    }else {
        printf("Saiu do jogo !");
        return 0;
    }
    }while(1);


    return 0;
}

void printaTab (int **clicados, int **resultante, int tam){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    printf("   ");
    for (int i=0; i<tam; i++){
        printf(" %c", 'A'+i);
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
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printf("#");
            }else if(resultante[i][j]>=0){
                if(resultante[i][j]==0){
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printf("%d", resultante[i][j]);
                }else if(resultante[i][j]==1){
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                printf("%d", resultante[i][j]);
                }else if(resultante[i][j]==2){
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("%d", resultante[i][j]);
                }else if(resultante[i][j]==3){
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                printf("%d", resultante[i][j]);
                }else{
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                printf("%d", resultante[i][j]);
                }
            }else{
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                printf("*");
            }
        }
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf("|");
        printf("\n");
    }
}

int receberCordenada (int **clicados,int **resultante, int tam, int nBombas){

    char linhaCodificada;
    int i, j;


    fflush(stdin);
    printf("\nDigite as cordenadas[LinhaColuna]: ");
    scanf("%c%c", &i,&j);
    fflush(stdin);

    i = toupper(i)-'A';
    j = toupper(j)-'A';

    if(resultante[i][j]==-1){
        system("cls");
        clicados[i][j]=1;
        fflush(stdin);
        printGameOver();
        printaTab(clicados,resultante,tam);
        printf("\n");
        system("pause");
        system("cls");
        return 0;
    }else{
        clicar(clicados,resultante,i,j,tam);
        int vitoria=0;
        for(int i=0; i<tam; i++){
            for(int j=0; j<tam; j++){
                vitoria += clicados[i][j];
            }
        }
        if(vitoria==(tam*tam-nBombas)){
            system("cls");
            fflush(stdin);
            printVictory();
            printaTab(clicados,resultante,tam);
            printf("\n");
            system("pause");
            system("cls");
            return 0;
        }
        return 1;
    }
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
    setlocale(LC_ALL, "Portuguese");
    int resp;
    printCampoMinado();
    printf(R"EOF(|    _          _                                 ___      ___        _          |
|   / | ___  _ | | ___  __ _  __ _  _ _          |_  )___ / __| __ _ (_) _ _     |
|   | ||___|| || |/ _ \/ _` |/ _` || '_|          / /|___|\__ \/ _` || || '_|    |
|   |_|      \__/ \___/\__, |\__,_||_|           /___|    |___/\__,_||_||_|      |
|_______________________|___/____________________________________________________|)EOF");
printf("\nDigite a opção desejada: ");
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

void printCampoMinado(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf(R"EOF( ________________________________________________________________________________
|   ____                                  __  __  _                    _         |
|  / ___| __ _  _ __ ___   _ __    ___   |  \/  |(_) _ __    __ _   __| |  ___   |
| | |    / _` || '_ ` _ \ | '_ \  / _ \  | |\/| || || '_ \  / _` | / _` | / _ \  |
| | |___| (_| || | | | | || |_) || (_) | | |  | || || | | || (_| || (_| || (_) | |
|  \____|\__,_||_| |_| |_|| .__/  \___/  |_|  |_||_||_| |_| \__,_| \__,_| \___/  |
|_________________________|_|____________________________________________________|)EOF");
    SetConsoleTextAttribute(hConsole, saved_attributes);
printf("\n");

}

void printGameOver(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf(R"EOF(   ____                               ___                     _
  / ___|  __ _  _ __ ___    ___      / _ \ __   __ ___  _ __ | |
 | |  _  / _` || '_ ` _ \  / _ \    | | | |\ \ / // _ \| '__|| |
 | |_| || (_| || | | | | ||  __/    | |_| | \ V /|  __/| |   |_|
  \____| \__,_||_| |_| |_| \___|     \___/   \_/  \___||_|   (_)
                                                                )EOF");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf("\n");
}

void printVictory(){
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
printf(R"EOF( __     __  _          _                            _
 \ \   / / (_)   ___  | |_    ___    _ __   _   _  | |
  \ \ / /  | |  / __| | __|  / _ \  | '__| | | | | | |
   \ V /   | | | (__  | |_  | (_) | | |    | |_| | |_|
    \_/    |_|  \___|  \__|  \___/  |_|     \__, | (_)
                                            |___/     )EOF");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf("\n");
}

