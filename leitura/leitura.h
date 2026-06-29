// MÁRCIO PAULINO, GUSTAVO SOUZA, MATHEUS GONÇALVES SANTOS , PEDRO MOURA SIMOES
#ifndef LEITURA_H
#define LEITURA_H
#include <stdio.h>
#include "../PATRICIA/patricia.h"
#include "../hash/hash.h"

int LerEntrada(char * entrada);
void LerFabulas(char *nomeArquivoBase, int qtd, TipoArvore *arvore, TipoArvore arvorestop, TabelaHash Tabela, TipoPesos pesos, int *comp);
void LerFabulasPATRICIA(char *nomeArquivoBase, int qtd, TipoArvore *arvore, TipoArvore arvorestop, int *comp);
void LerFabulasHash(char *nomeArquivoBase, int qtd, TipoArvore arvorestop, TabelaHash Tabela, TipoPesos pesos, int *total, int *comp);

#endif