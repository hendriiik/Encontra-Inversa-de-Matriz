/*
HENDRIK KEES KOPPE
GRR20203941
TRABALHO 1 ICC
*/

#ifndef FUNCOES_PRINCIPAIS
#define FUNCOES_PRINCIPAIS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lib_vet_e_mat.h"
#include "funcoes_parametros.h"
#include "utils.h"

double norma_l2(matriz *m,double *tempo_norma);
//funcao que calcula a norma l2

int encontra_maior_da_coluna(matriz *m, int lin_e_col_pivo);
//compara o pivo da coluna lin_e_col_pivo com os elementos abaixo dele e devolve o indice do maior

void pivoteamento(matriz *m, matriz *identidade);
/*realiza o pivoteamento e atualiza as matrizes m e identidade
obs: durante o refinamento essa funcao tambem eh usada,
mas ao inves da identidade usa-se a matriz de residuos */

void encontra_lu(matriz *l, matriz *u,double *tempo_lu);
//encontra as matrizes l e u, tomando u inicialmente como uma copia da matriz original

matriz * encontra_a_inversa(matriz *l, matriz *u, matriz *identidade);
//matriz que encontra a inversa da matriz pelas matrizes l,u e identidade pivoteada

matriz *refinamento(matriz *m,matriz *l,matriz *u, matriz *inversa, matriz *identidade,int iteracoes,double *tempo_iter, double *tempo_residuo,FILE *arq);
//funcao que realiza o refinamento

matriz * fatoracao_lu(matriz *m, double *tempo_lu, double *tempo_iter, double *tempo_residuo,FILE *arq,int iteracoes);
//funcao que realiza a fatoracao lu e chama o refinamento

#endif