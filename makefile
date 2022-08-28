#makefile para o trabalho 1 de icc
#Hendrik Kees Koppe GRR20203941

BIBLIOTECA= -lm

all: invmat

clean: 
	rm -f *.o *~

purge: clean
	-rm -f invmat


invmat: invmat.o lib_vet_e_mat.o funcoes_principais.o funcoes_parametros.o utils.o
	gcc invmat.o lib_vet_e_mat.o funcoes_principais.o funcoes_parametros.o utils.o -o invmat $(BIBLIOTECA)


lib_vet_e_mat.o: lib_vet_e_mat.c lib_vet_e_mat.h
	gcc -c lib_vet_e_mat.c

funcoes_principais.o: funcoes_principais.c funcoes_principais.h
	gcc -c funcoes_principais.c

funcoes_parametros.o: funcoes_parametros.c funcoes_parametros.h
	gcc -c funcoes_parametros.c

utils.o: utils.c utils.h
	gcc -c utils.c

invmat.o: invmat.c
	gcc -c invmat.c
