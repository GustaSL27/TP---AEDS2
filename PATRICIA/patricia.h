#ifndef PATRICIA_H
#define PATRICIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPALAVRA 50
#define D (MAXPALAVRA * 8)

typedef unsigned char TipoChave[MAXPALAVRA];  // char para bitS
typedef unsigned int TipoIndex;  // indice do bit analisado

// no externo(folha) e a palavra
// no interno - guarda o bit ponto de decisao
typedef enum {
    Interno,
    Externo
} TipoNo;

// union guarda dados de no interno ou externo - nunca duas coisas ao mesmo tempo
// quando interno, guarda o index do bit, ponteiro para o filho esquerdo e ponteiro para o filho direito
// quando externo, guarda o valor da chave
typedef struct TipoPatNo* TipoArvore;

typedef struct TipoPatNo {
    TipoNo InternoExterno;
    union {
        struct {
            TipoIndex Index;
            TipoArvore Esq, Dir;
        } NInterno;
        struct {
            TipoChave Chave;
            int contador;  // quantas vezes a palavra apareceu
        } NExterno;
    } NO;
} TipoPatNo;


int TipoBit(TipoIndex i, TipoChave k);
short VerificaExterno(TipoArvore p);
TipoArvore CriaNoInterno(int i, TipoArvore *esq, TipoArvore *dir);
TipoArvore CriaNoExterno(TipoChave k);
void Pesquisa(TipoChave k, TipoArvore t);
TipoArvore InsereEmDivergencia(TipoChave k, TipoArvore *t, int i);
TipoArvore Insere(TipoChave k, TipoArvore *t);

#endif
