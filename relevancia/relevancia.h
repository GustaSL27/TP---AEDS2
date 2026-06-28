#ifndef RELEVANCIA_H
#define RELEVANCIA_H

#include "../PATRICIA/lista/lista.h" // Precisa acessar a estrutura de lista

typedef struct {
    int idDoc;
    float pesoTotal;
} TipoResultadoBusca;

// Função que calcula o peso de um termo específico em um documento
float CalculaPesoTFIDF(int freqTermo, int numDocsColecao, int numDocsComTermo);

// Função para ordenar os resultados (bubble sort simples)
void OrdenaResultados(TipoResultadoBusca *resultados, int n);

int ContaDocumentos(TipoListaOcorrencia lista);

#endif