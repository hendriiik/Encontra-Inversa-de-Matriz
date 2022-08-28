/*
HENDRIK KEES KOPPE
GRR20203941
TRABALHO 1 ICC
*/

#ifndef LIB_VET_E_MAT
#define LIB_VET_E_MAT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "funcoes_parametros.h"

typedef struct matriz{
    int tam; //tamanho matriz
    double **mat;  //matriz em si
}matriz;


typedef struct vetor{
    int tam;    //tamanho vet
    double *vet;    //vetor em si
}vetor ;

vetor * aloca_vetor(int tam);
//funcao que aloca um vetor de tamanho tam

void desaloca_vetor(vetor *v);
//funcao que desaloca um vetor

matriz * aloca_matriz(int tam);
//funcao que aloca uma matriz de tamanho tam*tam

void desaloca_matriz(matriz *m);
//funcao que libera a matriz alocada dinamicamente

vetor* pega_coluna(matriz *m,int col);
//cria um vetor e nele separa a coluna col da matriz m

void imprime_matriz_quadrada(matriz *m, FILE *arq);
//funcao que imprime uma matriz m

matriz * cria_matriz_random(dados *d,char *argv[]);
//funcao que aloca e cria matriz aleatoria

matriz * le_e_cria_matriz(dados *d,char *argv[]);
//funcao que aloca, le e cria uma matriz

matriz * cria_identidade(int tam);
//funcao que aloca e cria uma matriz identidade de tamanho tam*tam

void copia_matriz(matriz *m,matriz *copia);
//copia a matriz m em copia

matriz * multiplica_matrizes_quadradas(matriz *a, matriz *b);
//multiplica matrizes quadradas

matriz * subtrai_matrizes_quadradas(matriz *a, matriz *b);
//funcao que subtrai a matriz b de a, devolvendo a resposta em result

void insere_coluna_na_matriz(matriz *m, vetor *v, int coluna);
//funcao que insere o vetor v como a coluna "coluna" da matriz m

void soma_matrizes_quadradas(matriz *a, matriz*b);
//funcao que soma as matrizes quadradas a e b, e coloca o resultado em a

void troca_linhas(matriz *m, matriz *identidade, int l1, int l2);
//funcao que troca as linhas das linhas l1 e l2 nas matrizes m e identidade

double determinante(matriz *m);
//funcao que descobre o determinante da matriz pelo metodo dos cofatores e devolve se o determinate eh diferente de 0

int tem_determinante(double det);
//funcao que descobre o determinante da matriz pelo metodo dos cofatores e devolve se a matriz tem determinante

double cofator(matriz *m, int linha, int coluna);
//funcao que calcula o cofator de uma matriz, eh chamado pela funcao determinante


#endif