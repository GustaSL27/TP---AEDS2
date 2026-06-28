#ifndef HASH_H
#define HASH_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define M 251
#define N 20
#define TAMALFABETO 256
#define MAX_ARRAY 5000

typedef char TipoPalavra[N];
typedef unsigned TipoPesos[N][TAMALFABETO];

typedef struct TipoItem {
  TipoPalavra Palavra;
  int qnt;
  int idDoc;
} TipoItem;

typedef struct TipoCelula* TipoApontador;
typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct ListaEncadeada {
  TipoCelula *Primeiro, *Ultimo;
} ListaEncadeada;

typedef ListaEncadeada TabelaHash[M];

// Vetor contendo as palavras para ordenar
extern TipoItem Palavras_ordenadas[MAX_ARRAY];

void InsereArray(TipoItem item, int *total);
void ImprimeArrayOrdenado();
int comparar_elementos_vetor(const void *a, const void *b);

void FLVazia(ListaEncadeada *Hash);
short Vazia(ListaEncadeada Hash);
void GeraPesos(TipoPesos p);
unsigned int h(TipoPalavra Palavra, TipoPesos p);
void Inicializa(TabelaHash T);
TipoApontador PesquisaHash(TipoPalavra Ch, TipoPesos p, TabelaHash T);
void InsereHash(TipoItem x, TipoPesos p, TabelaHash T, int *total);
void Imp(ListaEncadeada Hash);
void ImprimeHash(TabelaHash Tabela);
void LerPalavra(char *p, int Tam);
TipoApontador PesquisaUltima(TipoPalavra Ch, TipoPesos p, TabelaHash T);
TipoApontador BuscaListaHash(TipoPalavra Ch, TipoPesos p, TabelaHash T);
#endif
