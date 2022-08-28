/*
HENDRIK KEES KOPPE
GRR20203941
TRABALHO 1 ICC
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lib_vet_e_mat.h"


vetor * aloca_vetor(int tam){
//funcao que aloca um vetor de tamanho tam
    int i;
    vetor *v;

    if(!(v=malloc(sizeof(vetor)))){
        fprintf(stderr,"ERRO na alocacao do vetor");
        exit(1);
    }

    else{
        v->tam=tam;
        v->vet= malloc (v->tam*sizeof (double)) ;
    }

    return v;
}

void desaloca_vetor(vetor *v){
//funcao que desaloca um vetor
    int i;

    //for(i=0;i<v->tam;i++){
        free (v->vet);
    //}
    free(v);
}

matriz * aloca_matriz(int tam){
//funcao que aloca uma matriz de tamanho tam*tam
    int i;
    matriz *m;

    if(!(m=malloc(sizeof(matriz)))){
        fprintf(stderr,"ERRO na alocacao da matriz");
        exit(1);
    }

    else{

        m->tam=tam;
        m->mat = malloc (m->tam * sizeof (double*)) ;
        // aloca cada uma das linhas
        for (i=0; i < m->tam; i++)
            m->mat[i] = malloc (m->tam * sizeof (double)) ;

    }

    return m;
}

void desaloca_matriz(matriz *m){
//funcao que libera a matriz alocada dinamicamente
    int i;

    for (i=0; i < m->tam; i++)
        free (m->mat[i]) ;
            free (m->mat) ;

    free(m);
}



vetor* pega_coluna(matriz *m,int col){
//cria um vetor e nele separa a coluna col da matriz m
    int i;
    vetor *aux;

    aux=aloca_vetor(m->tam);

    for(i=0;i<aux->tam;i++){
        aux->vet[i]=m->mat[i][col];
    }

    return aux;
}



void imprime_matriz_quadrada(matriz *m, FILE *arq){
//funcao que imprime uma matriz m
    int i,j;

    for(i=0;i<m->tam;i++){
        for(j=0;j<m->tam;j++){
            fprintf(arq,"%.15g ",m->mat[i][j]);
        }
        fprintf(arq,"\n");
    }
}

matriz * cria_matriz_random(dados *d,char *argv[]){
//funcao que aloca e cria matriz aleatoria

    matriz *m;
    int i,j,tam;

    tam=atoi(argv[d->dimensao_random]);


    m=aloca_matriz(tam);

    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            m->mat[i][j] = rand()*((double)100000 / (double)RAND_MAX);;
        }
    }

    return m;
}

matriz * le_e_cria_matriz(dados *d,char *argv[]){
//funcao que aloca, le e cria uma matriz

    FILE *arq;

    int i, j, tam;
    matriz *m;
    
    if(d->entrada==-1){
        arq=stdin;
    }

    else{
        arq = fopen(argv[d->entrada], "rb");

        if (!arq){
            fprintf(stderr,"Erro! O arquivo nao existe!");
            exit(1);
            //caso o arquivo nao exista, devolve erro
        }
    }

    fscanf(arq,"%i",&tam);

    m=aloca_matriz(tam);

    for(i=0;i<m->tam;i++){
        for(j=0;j<m->tam;j++){
                fscanf(arq,"%lf",&m->mat[i][j]);
            }
        }

    return m;
        
}



matriz * cria_identidade(int tam){
//funcao que aloca e cria uma matriz identidade de tamanho tam*tam
    int i,j;
    matriz *identidade;

    identidade=aloca_matriz(tam);

    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            if (i==j)
            //se linhas = colunas, recebe 1
                identidade->mat[i][j]=1.0f;

            else
            //senao recebe 0
                identidade->mat[i][j]=0.0f;
        }
    }
    return identidade;
}


void copia_matriz(matriz *m,matriz *copia){
//copia a matriz m em copia
    int i,j;

    copia->tam=m->tam;

    for(i=0;i<m->tam;i++){
        for(j=0;j<m->tam;j++){
            copia->mat[i][j]=m->mat[i][j];
        }
    }
}


matriz * multiplica_matrizes_quadradas(matriz *a, matriz *b){
//multiplica matrizes quadradas
    int i,j,k;

    matriz *result;

    if(a->tam == b->tam){
        result=aloca_matriz(a->tam);

        for(i=0;i<a->tam;i++){
            for(j=0;j<a->tam;j++){

                result->mat[i][j]=0;

                for(k=0;k<a->tam;k++){
                    result->mat[i][j]+=a->mat[i][k]*b->mat[k][j];
                }
            }
        }

        return result;

    }
    
    else{
        fprintf(stderr,"Erro! Matrizes de tamanhos diferentes");
    }
}


matriz * subtrai_matrizes_quadradas(matriz *a, matriz *b){
//funcao que subtrai a matriz b de a, devolvendo a resposta em result
    int i,j;

    matriz *result;

    if(a->tam == b->tam){
        result=aloca_matriz(a->tam);

        for(i=0;i<a->tam;i++){
            for(j=0;j<a->tam;j++){
                result->mat[i][j]=a->mat[i][j]-b->mat[i][j];
            }
        }

        return result;
    }


    else{
        fprintf(stderr,"Erro!Subtracao de matrizes de tamanho diferente\n");
    }
}

void insere_coluna_na_matriz(matriz *m, vetor *v, int coluna){
//funcao que insere o vetor v como a coluna "coluna" da matriz m
    int i;

    for(i=0;i<v->tam;i++){
        m->mat[i][coluna]=v->vet[i];
    }
}

void soma_matrizes_quadradas(matriz *a, matriz*b){
//funcao que soma as matrizes quadradas a e b, e coloca o resultado em a

    int i,j;

    for(i=0;i<a->tam;i++){
        for(j=0;j<a->tam;j++){
            a->mat[i][j]+=b->mat[i][j];
        }
    }
}



void troca_linhas(matriz *m, matriz *identidade, int l1, int l2){
//funcao que troca as linhas das linhas l1 e l2 nas matrizes m e identidade
    int j,aux_id;
    double aux_m;

    for(j=0;j<m->tam;j++){

        aux_m=m->mat[l1][j];
        m->mat[l1][j]=m->mat[l2][j];
        m->mat[l2][j]=aux_m;

        aux_id=identidade->mat[l1][j];
        identidade->mat[l1][j]=identidade->mat[l2][j];
        identidade->mat[l2][j]=aux_id;
    }

}

double determinante(matriz *m){
//funcao que descobre o determinante da matriz pelo metodo dos cofatores e devolve se o determinate eh diferente de 0
    int j;
    double det;

    det = 0.0f;
   
    if (m->tam == 1) {
      det = m->mat[0][0];
    } 
   
    else {
        for (j=0;j< m->tam; j++) {
            det=det + m->mat[0][j] * cofator(m, 0, j);
        }
    }

    return det;
}

int tem_determinante(double det){
//funcao que descobre o determinante da matriz pelo metodo dos cofatores e devolve se o determinate eh diferente de 0
    if(det<0.001 && det>-0.001)
        //consideramos o determinante zero
        return 0;

    return 1;
}

 
double cofator(matriz *m, int linha, int coluna){
//funcao que calcula o cofator de uma matriz, eh chamado pela funcao determinante
    matriz  *submatriz;

    int i,j,x,y,novo_tam;
   
    x=0;
    y=0;

    novo_tam = m->tam - 1;


    submatriz=aloca_matriz(novo_tam);

    for (i=0;i<m->tam;i++) {
        for (j=0;j<m->tam;j++) {
            if (i!=linha && j!=coluna){
                submatriz->mat[x][y]=m->mat[i][j];
                y++;
                if (y>=novo_tam) {
                    x++;
                    y=0;
                }
            }
        }
    }
   
    return pow(-1.0,linha + coluna)*determinante(submatriz);
}


