// MÁRCIO PAULINO, GUSTAVO SOUZA, MATHEUS GONÇALVES SANTOS , PEDRO MOURA SIMOES
#ifndef RELEVANCIA_H
#define RELEVANCIA_H

#include "../PATRICIA/lista/lista.h" // Precisa acessar a estrutura de lista

typedef struct {
    int idDoc; //idDoc da fábula
    float pesoTotal; //relevancia
} TipoResultadoBusca;

// Função que calcula o peso de um termo específico em um documento
float CalculaPesoTFIDF(int freqTermo, int numDocsColecao, int numDocsComTermo);

// Função para ordenar os resultados (bubble sort simples)
void OrdenaResultados(TipoResultadoBusca *resultados, int n);

int ContaDocumentos(TipoListaOcorrencia lista);

#endif