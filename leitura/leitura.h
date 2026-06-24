#ifndef LEITURA_H
#define LEITURA_H
#include <stdio.h>
#include "../PATRICIA/patricia.h"
#include "../hash/hash.h"

int LerEntrada(char * entrada);
void LerFabulas(char *nomeArquivoBase, int qtd, TipoArvore *arvore, TipoArvore arvorestop, TabelaHash Tabela, TipoPesos pesos);
void LerFabulasPATRICIA(char *nomeArquivoBase, int qtd, TipoArvore *arvore, TipoArvore arvorestop);
void LerFabulasHash(char *nomeArquivoBase, int qtd, TipoArvore arvorestop, TabelaHash Tabela, TipoPesos pesos, int *total);

#endif