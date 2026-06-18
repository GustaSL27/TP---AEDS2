#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define M 509
#define N 20
#define TAMALFABETO 256

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

void FLVazia(ListaEncadeada *Hash);
short Vazia(ListaEncadeada Hash);
void GeraPesos(TipoPesos p);
unsigned int h(TipoPalavra Palavra, TipoPesos p);
void Inicializa(TabelaHash T);
TipoApontador Pesquisa(TipoPalavra Ch, TipoPesos p, TabelaHash T);
void Insere(TipoItem x, TipoPesos p, TabelaHash T);
void Imp(ListaEncadeada Hash);
void Imprime(TabelaHash Tabela);
void LerPalavra(char *p, int Tam);
TipoApontador PesquisaUltima(TipoPalavra Ch, TipoPesos p, TabelaHash T);
