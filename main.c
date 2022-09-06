#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <Windows.h>

int vitoria=0;
int menuCampo ();

void printCampoMinado();
void printGameOver();
void printVictory();
void printaTab (int **clicados, int **resultante, int tam);

int receberCordenada(int **clicados,int **resultante, int tam,int nBombas);
int clicar(int **clicados, int **resultante, int i, int j, int tam);

void zerar(int **matriz, int tam);
void random(int **bombas, int nBombas, int tam);
void calculaResultante(int **resultante,int **bombas, int tam);



int main(){
    setlocale(LC_ALL, "Portuguese");
    do{
    if (menuCampo()==1){
    int tam;
    int nBombas;
    do{
    printf("Digite o tamanho do campo minado[tamXtam]: ");
    scanf("%d", &tam);
    if(tam<=1){
        printf("Tamanho minimo do campo é 2X2!\n");
        system("pause");
    }else{
        break;
    }
    }while(1);
    do{
    printf("Digite a quantidade de bombas: ");
    scanf("%d", &nBombas);
    if(nBombas>=(tam*tam/2)){
        printf("Numero de bombas superior ou igual a 50%% das posições disponiveis!\nNumero maximo de bombas nesse campo %d...\n",(tam*tam)/2-1);
        system("pause");
    }else{
        break;
    }
    }while(1);

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

    random(bombas, nBombas, tam);
    fflush(stdin);

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
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                printf("%d", resultante[i][j]);
                }else if(resultante[i][j]==2){
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
                printf("%d", resultante[i][j]);
                }else if(resultante[i][j]==3){
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE |FOREGROUND_INTENSITY);
                printf("%d", resultante[i][j]);
                }else{
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_INTENSITY);
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

    if((i>=tam||j>=tam)||(i<0||j<0)){
        printf("\nCordenada Invalida!\n");
        system("pause");
        return 1;
    }


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
        vitoria += clicar(clicados,resultante,i,j,tam);
        if(vitoria==(tam*tam-nBombas)){
            system("cls");
            fflush(stdin);
            printVictory();
            printaTab(clicados,resultante,tam);
            printf("\n");
            system("pause");
            system("cls");
            vitoria=0;
            return 0;
        }
        return 1;
    }
}

int clicar(int **clicados, int **resultante, int i, int j, int tam){
    int retorno=0;
    if (clicados[i][j]==1){
        return 0;
    }
    clicados[i][j]=1;
    retorno += 1;
    if (resultante[i][j] == 0){
        if (i>0){
            retorno += clicar(clicados,resultante, i-1, j, tam);
            if (j>0)
                retorno += clicar(clicados,resultante, i-1, j-1, tam);
            if (j<tam-1)
                retorno += clicar(clicados,resultante, i-1, j+1, tam);
        }
        if (i<tam-1){
            retorno += clicar(clicados,resultante, i+1, j, tam);
            if (j<tam-1)
                retorno += clicar(clicados,resultante, i+1, j+1, tam);
            if (j>0)
                retorno += clicar(clicados,resultante, i+1, j-1, tam);
        }
        if (j>0)
            retorno += clicar(clicados,resultante, i, j-1, tam);
        if (j<tam-1)
            retorno += clicar(clicados,resultante, i, j+1, tam);

    }
    return retorno;
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

void random(int **bombas, int nBombas, int tam){
    srand(time(NULL));
    int i;
    int j;
  for(int k=0; k<nBombas;k++){
    i= rand() % (tam);
    j= rand() % (tam);
    if(bombas[i][j]==0){
        bombas[i][j]=1;
    }else{
        k--;
    }
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







