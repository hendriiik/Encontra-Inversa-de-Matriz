/*
HENDRIK KEES KOPPE
GRR20203941
TRABALHO 1 ICC
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "lib_vet_e_mat.h"
#include "funcoes_parametros.h"
#include "funcoes_principais.h"


int main (int argc, char *argv[]){
    srand(20221);

    FILE *arq_saida;
    matriz *inversa,*m;
    dados *d=malloc(sizeof(dados));
    double tempo_lu, tempo_iter, tempo_residuo;
    int iteracoes;


    d=le_parametros(d,argc,argv);

    arq_saida=define_saida(d,argc,argv);
    iteracoes=define_iteracoes(d,argc,argv);

    if(d->dimensao_random==-1)
        m=le_e_cria_matriz(d,argv);

    else
        m=cria_matriz_random(d,argv);


    if (!tem_determinante(determinante(m))){
        fprintf(stderr,"ERRO! Matriz não inversivel!\n");
        exit(1);
    }

    inversa=fatoracao_lu(m,&tempo_lu,&tempo_iter,&tempo_residuo,arq_saida,iteracoes);

    fprintf(arq_saida,"%i\n",inversa->tam);
    imprime_matriz_quadrada(inversa,arq_saida);

    fprintf(arq_saida,"\n");
    fprintf(arq_saida,"Tempo LU: %.15g\n",tempo_lu);
    fprintf(arq_saida,"Tempo iter: %.15g\n",tempo_iter);
    fprintf(arq_saida,"Tempo residuo: %.15g\n",tempo_residuo);

    desaloca_matriz(inversa);
    desaloca_matriz(m);
    free(d);
}