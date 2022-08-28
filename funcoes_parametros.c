/*
HENDRIK KEES KOPPE
GRR20203941
TRABALHO 1 ICC
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "funcoes_parametros.h"


void procura_entrada(dados *d, int argc, char *argv[]){
//funcao que encontra qual sera o arquivo input
    int entrada,achou;

    entrada=0;
    achou=0;

    while ((entrada<(argc-1)) && (achou != 1)){
        if ((strcmp(argv[entrada],"-e") == 0)){
            d->entrada=entrada+1;
            achou=1;
        }
        entrada++;
    }

    if (achou == 0)
        d->entrada=-1;
        //se nao existe, entrada vale -1
}


void procura_saida(dados *d, int argc, char *argv[]){
//funcao que encontra qual sera o arquivo output
    int saida,achou;

    saida=0;
    achou=0;

    while ((saida<(argc-1)) && (achou != 1)){
        if ((strcmp(argv[saida],"-s") == 0)){
            d->saida=saida+1;
            achou=1;
        }
        saida++;
    }

    if (achou == 0)
        d->saida=-1;
        //se nao existe, saida vale -1
}

void procura_dimensao_random(dados *d, int argc, char *argv[]){
//funcao que encontra qual sera o tamanho da matriz aleatorizada
    int dimensao,achou;

    dimensao=0;
    achou=0;

    while ((dimensao<(argc-1)) && (achou != 1)){
        if ((strcmp(argv[dimensao],"-r") == 0)){
            d->dimensao_random=dimensao+1;
            achou=1;
        }
        dimensao++;
    }

    if (achou == 0)
        d->dimensao_random=-1;
        //se nao existe, nao é randomico, e vale -1
}

void procura_iteracoes(dados *d, int argc, char *argv[]){
//funcao que encontra qual sera o numero de iteracoes esperado
    int iteracoes,achou;

    iteracoes=0;
    achou=0;

    while ((iteracoes<(argc-1)) && (achou != 1)){
        if ((strcmp(argv[iteracoes],"-i") == 0)){
            d->iteracoes=iteracoes+1;
            achou=1;
        }
        iteracoes++;
    }

    if (achou == 0){
        d->iteracoes=-1;
        //se nao achou, iteracoes vale -1
    }
}


dados * le_parametros(dados *d,int argc,char *argv[] ){
//le todos os parametros inseridos, retornando uma struct com a posicao deles em argv


    procura_entrada(d,argc,argv);
    procura_saida(d,argc,argv);
    procura_dimensao_random(d,argc,argv);
    procura_iteracoes(d,argc,argv);

    if (d->dimensao_random != -1){
        d->entrada=-1;
        //se ele quer random, ignora a entrada se existir
    } 

    if(d->iteracoes== -1){
        fprintf(stderr,"ERRO! O numero de iteracoes nao pode ser zero\n");
        exit(1);
    }

    return d;
}

FILE * define_saida(dados *d,int argc,char *argv[]){
//funcao que define onde sera impressa a saida
    FILE *arq;

    if(d->saida != -1)
        arq = fopen(argv[d->saida], "w");
        //arquivo dado pelo usuario

    else
        arq=stdout;
        //entrada padrao

    return arq; 
}

int define_iteracoes(dados *d, int argc, char *argv[]){
//funcao que le e devolve a quantidade de iteracoes desejadas pelo usuario
    int iter;

    if(d->iteracoes == -1){
        fprintf(stderr,"Erro!Insira a quantidade de iteracoes");
        exit(1);
    }

    else{
        iter=atoi(argv[d->iteracoes]);

        if(iter<=0){
            fprintf(stderr,"Erro! Insira uma quantidade de iteracoes validas");
            exit(1);
        }
    }

    return iter;
}
