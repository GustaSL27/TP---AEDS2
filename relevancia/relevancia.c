#include "relevancia.h"
#include <math.h>
// Calcula o peso de relevância de um termo utilizando a fórmula TF-IDF.
float CalculaPesoTFIDF(int freqTermo, int numDocsColecao, int numDocsComTermo) {
    //Evita divisão por zero caso o termo não tenha sido encontrado em nenhum documento
    if (numDocsComTermo == 0) return 0;
    // log2(N / dj)
    //numDocsColecao é o total de fabulas
    //numDocsComTermo é o total de fabulas diferentes que contem a palavra buscada
    float idf = log2((float)numDocsColecao / (float)numDocsComTermo);
    return (float)freqTermo * idf;
}

// Ordena o vetor de resultados em ordem decrescente de peso. 
void OrdenaResultados(TipoResultadoBusca *resultados, int n) {
    // Bubble sort simples para ordenar por peso decrescente
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (resultados[j].pesoTotal < resultados[j+1].pesoTotal) {
                TipoResultadoBusca temp = resultados[j];
                resultados[j] = resultados[j+1];
                resultados[j+1] = temp;
            }
        }
    }
}

int ContaDocumentos(TipoListaOcorrencia lista) {// Recebe lista com os indices invertidos pra saber quantas vezes palavra apareceu
    int cont = 0;
    // Começa do nó depois da celula cabeça que é o q de fato guarda algo
    TipoApontadorOcorrencia aux = lista.Primeiro->Prox;
    while (aux != NULL) {
        cont++;   // Soma +1 para cada documento encontrado
        aux = aux->Prox; // Vai para o próximo documento
    }
    return cont;// Retorna o total de documentos onde a palavra apareceu
}