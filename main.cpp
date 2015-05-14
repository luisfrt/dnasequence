//Luís Felipe Rabello Taveira
//Alexandre Lucchesi de Alencar

#include <iostream>
using namespace std;

//To change how the score works, just look at the calculateAlignment function
#define GAP_VALUE -2
#define MATCH_VALUE 1
#define MISMATCH_VALUE -1

#define UP 0
#define DIAGONAL 1
#define LEFT 2
#define DIRECTION int

//Directive to choose the input
#define INPUT 2

#if INPUT == 1
//input 1 - Exemplo da apostila (página 7/11)
char s[] = "eAAAC"; //5 + \nul
char t[] = "eAGC"; //4 + \null
#define M 5
#define N 4

#elif INPUT == 2
//input 2 - Exercicio da Lista 7
char s[] = "0ATACTACGGAGGG"; //14 + \nul
char t[] = "0GAACGTAGGCGTAT"; //15 + \null
#define M 14
#define N 15

#endif

int a[M][N];

int calculateAlignment (int i, int j);
DIRECTION walkOverTable(int i, int j);
void printRecursiveT (int i, int j);
void printRestOfT (int j);
void printRecursiveS(int i, int j);
void printRestOfS (int i);
void printLCSS (int i, int j);
void printLCST (int i, int j);
void printS(int i, int j);
void printT(int i, int j);

int main(){
    //Print Sequences
    cout <<"Sequence S = ";
    for (int k = 1; k < M; ++k) cout<<s[k];
    cout <<"\tSize = "<< M << endl;

    cout << "Sequence T = ";
    for (int k = 1; k < N; ++k) cout<<t[k];
    cout <<"\tSize = "<< N << endl;

    cout << endl;
    //Init with 0 (Local Algorithm) first column and row
    for (int i = 0; i < M ; ++i) a[i] [0] = 0;
    for (int j = 0; j < N; ++j) a[0] [j] = 0;

    //Calculate Matrix
    for (int i = 1; i < M; ++i)
        for (int j = 1; j < N; ++j)
            //Calcula o score de cada posição
            a[i][j] = calculateAlignment(i,j);

    //Print Matrix
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) cout << a[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    //Find best alignment
    int best_value = 0;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            best_value = best_value < a[i][j]? a[i][j] : best_value;

    int total_alignments = 0;
    //Find other alignments
    for (int other_good_values = best_value; other_good_values > 0; other_good_values--) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (a[i][j] == other_good_values) {
                    cout << "Score: " << other_good_values << " - Position in Table: a[" << i << "][" << j << "]" <<
                                                              endl;
                    //Imprime a string S desse alinhamento (score)
                    printS(i, j);
                    //Imprime a string T desse alinhamento (score)
                    printT(i, j);
                    //Imprime apenas o alinhamento local de S de acordo com o algoritmo do Cormen 3rd Edition
                    cout << "Local Alignment for S: ";
                    printLCSS (i, j);
                    cout<< endl;
                    //Imprime apenas o alinhamento local de T de acordo com o algoritmo do Cormen 3rd Edition
                    cout << "Local Alignment for T: ";
                    printLCST (i, j);
                    cout << endl << endl;
                    total_alignments++;

                }
            }
        }
    }
    cout << endl;
    cout << "\tAmount of local alignments found: " << total_alignments <<endl;
    //cout <<"Best value = " << best_value << endl <<"Row =" << row_of_best_alignment << " Column =" << column_of_best_alignment << endl;

    return 0;

}
//Função que preenche a matriz, calculando o score para cada posição.
int calculateAlignment (int i, int j){
    int max = 0;
    int upper_value_in_matrix = a[i][j-1] + GAP_VALUE;
    int lower_value_in_matrix = a[i-1][j] + GAP_VALUE;
    int pij = (s[i] == t[j])? MATCH_VALUE : MISMATCH_VALUE;
    int diagonal_value_in_matrix = a[i-1][j-1] + pij;

    max = (upper_value_in_matrix > max)? upper_value_in_matrix : max;
    max = (lower_value_in_matrix > max)? lower_value_in_matrix : max;
    max = (diagonal_value_in_matrix > max)? diagonal_value_in_matrix : max;

    return max;
}

//Algoritmo que substitui a criação de uma tabela específica para armazenar as setas.
//Ele recupera a "seta" fazendo uma checagem no sentido anti-horário.
DIRECTION walkOverTable(int i, int j){
    //Check in counter-clock wise
    if(a[i][j] == (a[i-1][j] + GAP_VALUE)) return UP;
    if(a[i][j] == (a[i-1][j-1] + MATCH_VALUE )) return DIAGONAL;
    if(a[i][j] == (a[i-1][j-1] + MISMATCH_VALUE ))return DIAGONAL;
    if(a[i][j] == (a[i][j-1] + GAP_VALUE)) return LEFT;
    else return DIAGONAL;

}

//Imprime a sequencia T que possui o score na posição a[i][j]
void printT(int i,int j){
    printRecursiveT(i,j);
    printRestOfT(j);
}
//Imprime a sequencia S que possui o score na posição a[i][j]
void printS(int i,int j){
    printRecursiveS(i,j);
    printRestOfS(i);
}
//Algoritmo para percorer a matriz pelas "setinhas" e imprimir a string t de acordo com as regras das setas
void printRecursiveT (int i, int j){
    if (i == 0 && j==0) return;
    if (i > 0 && j == 0) {
        printRecursiveT(i-1,j);
        printf("_");
    }
    else if (i == 0 && j > 0) {
        printRecursiveT(i,j-1);
        printf("%c", t[j]);
        //printf("_");
    }
    else {
        //Pega a direção da seta naquela posição da matriz.
        int dir = walkOverTable(i, j);
        //cout << i << " " << j << endl;
        if (dir == DIAGONAL) {
            printRecursiveT(i - 1, j - 1);
            printf("%c", t[j]);
        }
        else if (dir == UP) {
            printRecursiveT(i - 1, j);
            printf("_");
        }
        else printRecursiveT(i, j - 1);
    }
}
//Imprime a parte da direita da string T, sendo que a parte da esquerda
// foi impressa pelo algoritmo recursivo printRecursiveT
void printRestOfT (int j){
    j++;
    while (t[j] != '\0'){
        printf("%c",t[j]);
        j++;
    }
    cout << endl;

}
//Algoritmo para percorer a matriz pelas "setinhas" e imprimir a string s de acordo com as regras das setas
void printRecursiveS (int i, int j){
    if (i == 0 && j==0) return;
    if (i > 0 && j == 0) {
        printRecursiveS(i-1,j);
        printf("%c", s[i]);
        //printf("_");
    }
    else if (i == 0 && j > 0) {
        printRecursiveS(i,j-1);
        printf("_");
    }
    else {
        //Pega a direção da seta naquela posição da matriz.
        int dir = walkOverTable(i, j);
        //Se a seta apontar para a diagonal
        if (dir == DIAGONAL) {
            printRecursiveS(i - 1, j - 1);
            printf("%c", s[i]);
        }
        //Se a seta apontar para cima
        else if (dir == UP)printRecursiveS(i - 1, j);
        //Se a seta apontar para esquerda
        else{
            printRecursiveS(i, j - 1);
            printf("_");
        }
    }
}
//Imprime a parte da direita da string S, sendo que a parte da esquerda
// foi impressa pelo algoritmo recursivo printRecursiveS
void printRestOfS (int i){
    i++;
    while (s[i] != '\0'){
        printf("%c",s[i]);
        i++;
    }
    cout << endl;

}
//Recursive Algorithm to print Longest Common Subsequence taken from Cormen 3rd Edition
void printLCSS (int i, int j){
    if (i == 0 || j==0) return;
    int dir = walkOverTable(i, j);
    if (dir == DIAGONAL) {
        printLCSS(i - 1, j - 1);
        printf("%c", s[i]);
    }
    else if (dir == UP)printLCSS(i - 1, j);

    else printLCSS(i, j - 1);
}
//Recursive Algorithm to print Longest Common Subsequence taken from Cormen 3rd Edition
void printLCST (int i, int j){
    if (i == 0 || j==0) return;
    int dir = walkOverTable(i, j);
    if (dir == DIAGONAL) {
        printLCST(i - 1, j - 1);
        printf("%c", t[j]);
    }
    else if (dir == UP)printLCST(i - 1, j);

    else printLCST(i, j - 1);
}