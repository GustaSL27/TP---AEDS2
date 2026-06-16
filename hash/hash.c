/*
Modificações a fazer:
Colocar if na inserção para caso o idDoc seja igual, não inserir na celula seguinte da lista encadeada e sim qnt++

*/

#include "hash.h"

void FLVazia(ListaEncadeada *Hash){
  Hash->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
  Hash->Ultimo = Hash->Primeiro; Hash->Primeiro->Prox = NULL;
}  

short Vazia(ListaEncadeada Hash){
    return (Hash.Primeiro == Hash.Ultimo); 
}

void Ins(TipoItem x, ListaEncadeada *Hash){
  Hash->Ultimo->Prox = (TipoCelula *)malloc(sizeof(TipoCelula));
  Hash->Ultimo = Hash->Ultimo->Prox; Hash->Ultimo->Item = x;
  Hash->Ultimo->Prox = NULL;
}  

void GeraPesos(TipoPesos p){
  /* Gera valores randomicos entre 1 e 10.000 */
  int i, j;
  struct timeval semente;
  /* Utilizar o tempo como semente para a funcao srand() */
  gettimeofday(&semente, NULL); 
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  for (i = 0; i < N; i++)
    for (j = 0; j < TAMALFABETO; j++)
      p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

unsigned int h(TipoPalavra Palavra, TipoPesos p){
  int i; unsigned int Soma = 0; 
  int comp = strlen(Palavra);
  for (i = 0; i < comp; i++) Soma += p[i][(unsigned int)Palavra[i]];
  return (Soma % M);
}

void Inicializa(TabelaHash T){
  int i;
  for (i = 0; i < M; i++) FLVazia(&T[i]);
}

TipoApontador Pesquisa(TipoPalavra Ch, TipoPesos p, TabelaHash T){
  /* TipoApontador de retorno aponta para o item anterior da Hash */
  unsigned int i;
  TipoApontador Ap;
  i = h(Ch, p);
  if (Vazia(T[i])) return NULL;  /* Pesquisa sem sucesso */
  else 
  { Ap = T[i].Primeiro;
    while (Ap->Prox->Prox != NULL &&
        strncmp(Ch, Ap->Prox->Item.Palavra, sizeof(TipoPalavra))) 
      Ap = Ap->Prox;
    if (!strncmp(Ch, Ap->Prox->Item.Palavra, sizeof(TipoPalavra))) 
    return Ap;
    else return NULL;  /* Pesquisa sem sucesso */
  }
}  

void Insere(TipoItem x, TipoPesos p, TabelaHash T){
  if (Pesquisa(x.Palavra, p, T) == NULL)
  Ins(x, &T[h(x.Palavra, p)]);
  else printf(" Registro ja  esta  presente\n");
} 

void Imp(ListaEncadeada Hash){
  TipoApontador Aux;
  Aux = Hash.Primeiro->Prox;
  while (Aux != NULL) 
    { printf("%.*s ", N, Aux->Item.Palavra);
      Aux = Aux->Prox;
    }
}

void Imprime(TabelaHash Tabela){
  int i;
  for (i = 0; i < M; i++) 
    { printf("%d: ", i);
      if (!Vazia(Tabela[i]))
      Imp(Tabela[i]);
      putchar('\n');
    }
} 
 
void LerPalavra(char *p, int Tam){
  char c; int i, j;
  fflush(stdin); j=0;
  while (((c=getchar())!='\n') && j<Tam-1) p[j++]= c;
  p[j]='\0';
  while(c != '\n') c=getchar();
  for(i=j-1;(i>=0 && p[i]==' ');i--) p[i]='\0';
}
