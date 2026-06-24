#ifndef LISTA_H
#define LISTA_H
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int qtde;
    int idDoc;
} TipoItemOcorrencia;

typedef struct TipoCelulaOcorrencia *TipoApontadorOcorrencia;

typedef struct TipoCelulaOcorrencia {
    TipoItemOcorrencia Item;
    TipoApontadorOcorrencia Prox;
} TipoCelulaOcorrencia;

typedef struct {
    TipoApontadorOcorrencia Primeiro, Ultimo;
} TipoListaOcorrencia;

void FLVaziaOcorrencia(TipoListaOcorrencia * Lista);
int  LEhVaziaOcorrencia(TipoListaOcorrencia  Lista);
void InsereListaOcorrencia(TipoItemOcorrencia x ,TipoListaOcorrencia *Lista);
void AtualizaOcorrencia(TipoListaOcorrencia * Lista , int idDoc);
void ImprimeListaOcorrencia(TipoListaOcorrencia Lista);


#endif
