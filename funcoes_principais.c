/*
HENDRIK KEES KOPPE
GRR20203941
TRABALHO 1 ICC
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "funcoes_principais.h"


double norma_l2(matriz *m,double *tempo_norma){
//funcao que calcula a norma l2
    double norma;
    int i,j;

    *tempo_norma=timestamp();

    for(i=0;i<m->tam;i++){
        for(j=0;j<m->tam;j++){
            norma=pow(m->mat[i][j],2);
        }
    }
    *tempo_norma=timestamp()-*tempo_norma;

    return(sqrt(norma));
}

int encontra_maior_da_coluna(matriz *m, int lin_e_col_pivo){
//compara o pivo da coluna lin_e_col_pivo com os elementos abaixo dele e devolve o indice do maior
    int i;
    int novo_pivo;

    novo_pivo=lin_e_col_pivo;

    for(i=lin_e_col_pivo+1;i<m->tam;i++){
        if (m->mat[i][lin_e_col_pivo]>m->mat[novo_pivo][lin_e_col_pivo])
            novo_pivo=i;
    }

    return novo_pivo;
}

void pivoteamento(matriz *m, matriz *identidade){
/*realiza o pivoteamento e atualiza as matrizes m e identidade
obs: durante o refinamento essa funcao tambem eh usada,
mas ao inves da identidade usa-se a matriz de residuos */
    int i,pivo;

    for(i=0;i<m->tam;++i){
        pivo = encontra_maior_da_coluna(m,i);

        if (i!=pivo){
            troca_linhas(m,identidade,i,pivo);
        }
    }
}

void encontra_lu(matriz *l, matriz *u,double *tempo_lu){
//encontra as matrizes l e u, tomando u inicialmente como uma copia da matriz original

    int i,j,k;
    double multiplicador;

    *tempo_lu=timestamp();

    for(i=0;i<u->tam;i++){
        l->mat[i][i]=1.0;

        for(k=i+1;k<u->tam;++k){
            multiplicador = u->mat[k][i]/u->mat[i][i];
            u->mat[k][i]=0.0;
            for(j=i+1;j<u->tam;++j)
                u->mat[k][j]-=u->mat[i][j]*multiplicador;


            l->mat[k][i]=multiplicador;
        }
    }
    *tempo_lu=timestamp()- *tempo_lu;
}

matriz * encontra_a_inversa(matriz *l, matriz *u, matriz *identidade){
//funcao que encontra a inversa da matriz pelas matrizes l,u e identidade pivoteada

    int i,j,k;
    matriz *inversa;

    inversa=aloca_matriz(l->tam);

    //ly=b

    for(i=0;i<l->tam;i++){
        for(j=0;j<l->tam;j++){
            inversa->mat[j][i]=identidade->mat[i][j];

            for(k=j-1;k>=0;k--){
                inversa->mat[j][i]-= l->mat[j][k]*inversa->mat[k][i];
            }

            inversa->mat[j][i]/=l->mat[j][j];
        }
    }

    //ux=y

    for(i=0;i<u->tam;i++){
        for(j=u->tam-1;j>=0;j--){
            for(k=j+1;k<u->tam;k++){
                inversa->mat[j][i]-=u->mat[j][k]*inversa->mat[k][i];
            }

            inversa->mat[j][i]/=u->mat[j][j];
        }
    }

    return inversa;
}




matriz *refinamento(matriz *m,matriz *l,matriz *u, matriz *inversa, matriz *identidade,int iteracoes,double *tempo_iter, double *tempo_residuo,FILE *arq){
//funcao que realiza o refinamento
    int i;
    matriz *aux, *residuo, *w;
    double norma,tempo_aux1,tempo_aux2;

    for(i=0;i<iteracoes;i++){
        tempo_aux1=timestamp();

        aux=multiplica_matrizes_quadradas(m,inversa);

        residuo=subtrai_matrizes_quadradas(identidade,aux);

        norma=norma_l2(residuo,&tempo_aux2);
        fprintf(arq,"iteracao %i: <|%.15g|>\n",i+1,norma);

        w=encontra_a_inversa(l,u,residuo);

        soma_matrizes_quadradas(inversa,w);

        tempo_aux1=timestamp()- tempo_aux1;
        *tempo_iter+=tempo_aux1;
        *tempo_residuo+=tempo_aux2;
    }

    *tempo_iter/=iteracoes;
    *tempo_residuo/=iteracoes;

    desaloca_matriz(aux);
    desaloca_matriz(residuo);
    desaloca_matriz(w);

    return inversa;
}


matriz * fatoracao_lu(matriz *m, double *tempo_lu, double *tempo_iter, double *tempo_residuo,FILE *arq,int iteracoes){
//funcao que realiza a fatoracao lu e chama o refinamento

    matriz *identidade, *l,*u,*inversa;
    
    l=aloca_matriz(m->tam);
    u=aloca_matriz(m->tam);

    identidade=cria_identidade(m->tam);

    pivoteamento(m,identidade);

    copia_matriz(m,u);

    encontra_lu(l,u,tempo_lu);

    inversa=encontra_a_inversa(l,u,identidade);

    inversa=refinamento(m,l,u,inversa,identidade,iteracoes,tempo_iter,tempo_residuo,arq);

    desaloca_matriz(l);
    desaloca_matriz(u);
    
    return inversa;
}