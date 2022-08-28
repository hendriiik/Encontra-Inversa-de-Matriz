/*
HENDRIK KEES KOPPE
GRR20203941
TRABALHO 1 ICC
*/

#ifndef FUNCOES_PARAMETROS
#define FUNCOES_PARAMETROS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct dados{
    int entrada;  //posicao da entrada (-e) em argv
    int saida; //posicao da saida (-s) em argv
    int dimensao_random; //posicao de -r em argv, se existir
    int iteracoes; //posicao de -i em argv
}dados;

void procura_entrada(dados *d, int argc, char *argv[]);
//funcao que encontra qual sera o arquivo input

void procura_saida(dados *d, int argc, char *argv[]);
//funcao que encontra qual sera o arquivo output

void procura_dimensao_random(dados *d, int argc, char *argv[]);
//funcao que encontra qual sera o tamanho da matriz aleatorizada

void procura_iteracoes(dados *d, int argc, char *argv[]);
//funcao que encontra qual sera o numero de iteracoes esperado

dados * le_parametros(dados *d,int argc,char *argv[] );
//le todos os parametros inseridos, retornando uma struct com a posicao deles em argv

FILE * define_saida(dados *d,int argc,char *argv[]);
//funcao que define onde sera impressa a saida

int define_iteracoes(dados *d, int argc, char *argv[]);
//funcao que le e devolve a quantidade de iteracoes desejadas pelo usuario

#endif