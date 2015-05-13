#include <iostream>
using namespace std;

#define GAP_VALUE -2
#define MATCH_VALUE 1
#define MISMATCH_VALUE -1

#define UP 0
#define DIAGONAL 1
#define LEFT 2
#define DIRECTION int


char s[] = "eAAAC"; //5 + \nul
char t[] = "eAGC"; //4 + \null
#define M 5
#define N 4

//char s[] = "0ATACTACGGAGGG"; //14 + \nul
//char t[] = "0GAACGTAGGCGTAT"; //15 + \null
//#define M 14
//#define N 15
int a[M][N];

int calculateAlignment (int i, int j);
char* printPath(int i, int j);
DIRECTION walkOverTable(int i, int j);
void getPathS(int i, int j);
void getPath(int i, int j);
void printRecursiveT (int i, int j);
void printRestOfT (int j);
void printRecursiveS(int i, int j);
void printRestOfS (int i);
void printS(int i, int j);
void printT(int i, int j);
int main(){

    //Init with 0 (Local Algorithm) first column and row
    for (int i = 0; i < M ; ++i) a[i] [0] = 0;
    for (int j = 0; j < N; ++j) a[0] [j] = 0;

    for (int i = 1; i < M; ++i) {

        for (int j = 1; j < N; ++j) {
            a[i][j] = calculateAlignment(i,j);

        }

    }

    //output matrix
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    //Find best alignment
    int row_of_best_alignment = 0;
    int column_of_best_alignment = 0;
    int best_value = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            row_of_best_alignment = (best_value < a[i][j])? i : row_of_best_alignment;
            column_of_best_alignment = (best_value < a[i][j])? j : column_of_best_alignment;
            best_value = best_value < a[i][j]? a[i][j] : best_value;
        }

    }
    cout <<"Best value = " << best_value << endl <<"Row =" << row_of_best_alignment << " Column =" << column_of_best_alignment << endl;
    //getPath(3,1);
    printS(2,1);
    printT(2,1);
    return 0;

}

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

void getPathS(int i, int j){
    int max = (M+N);
    char* pathT = (char*) malloc(sizeof(char) * max);

    int lineT = i;
    pathT[i] = t[j];

    for (int k = j; k > 0 ; k--) {
        DIRECTION dir = walkOverTable(lineT,k);
        if (dir == UP) lineT--;
        else if(dir == DIAGONAL) pathT[k-1] = t[k];
        else if(dir == LEFT) pathT[k-1] = '_';

    }
    //Preenche a parte da direita de pathT[j]
    for (int l = j; l < N -1; ++l) {
        pathT[l] = t[l];
        printf("%c",pathT[l]);
    }
    cout << endl;
    int m = 0;

    while (pathT[m] != '\0'){
        printf("%c",pathT[m]);
        m++;
    }
    cout << endl;

}

void getPath(int i, int j){
    int max = (M+N);
    char* pathT = (char*) malloc(sizeof(char) * max);

    int lineT = i;
    pathT[i] = t[j];

    for (int k = j; k > 0 ; k--) {
        DIRECTION dir = walkOverTable(lineT,k);
        if (dir == UP) lineT--;
        else if(dir == DIAGONAL) {
            pathT[k] = t[k];
            lineT--;
        }
        else if(dir == LEFT) pathT[k] = '_';

    }
    //Preenche os _ a esquerda, subir as linhas
    for (int n = lineT; n == 0 ; --n) {
        pathT[n] = '_';

    }
    int p=0;
    //Preenche a parte da direita de pathT[j]
    for (int l = j; l < N -1; ++l) {
        pathT[i+p] = t[l];
        p++;
        //printf("%c",pathT[l]);
    }
    cout << endl;
    int m = 0;

    while (pathT[m] != '\0'){
        printf("%c",pathT[m]);
        m++;
    }
    cout << endl;

}



DIRECTION walkOverTable(int i, int j){
    //Check in counter-clock wise
    if(a[i][j] == (a[i-1][j] + GAP_VALUE)) return UP;
    if(a[i][j] == (a[i-1][j-1] + MATCH_VALUE )) return DIAGONAL;
    if(a[i][j] == (a[i-1][j-1] + MISMATCH_VALUE ))return DIAGONAL;
    if(a[i][j] == (a[i][j-1] + GAP_VALUE)) return LEFT;
    else return DIAGONAL;

}


void printT(int i,int j){
    printRecursiveT(i,j);
    printRestOfT(j);
}
void printS(int i,int j){
    printRecursiveS(i,j);
    printRestOfS(i);
}

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
        int dir = walkOverTable(i, j);
        //cout << i << " " << j << endl;
        if (dir == DIAGONAL) {
            printRecursiveT(i - 1, j - 1);
            printf("%c", t[j]);
        }
        else if (dir == UP) printRecursiveT(i - 1, j);
        else printRecursiveT(i, j - 1);
    }
}
void printRestOfT (int j){
    j++;
    while (t[j] != '\0'){
        printf("%c",t[j]);
        j++;
    }
    cout << endl;

}

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
        int dir = walkOverTable(i, j);
        cout << i << " " << j << " dir:" << dir<< endl;
        if (dir == DIAGONAL) {
            printRecursiveS(i - 1, j - 1);
            printf("%c", s[i]);
        }
        else if (dir == UP){
            printRecursiveS(i - 1, j);
        }
        else printRecursiveS(i, j - 1);
    }
}
void printRestOfS (int i){
    i++;
    while (s[i] != '\0'){
        printf("%c",s[i]);
        i++;
    }
    cout << endl;

}