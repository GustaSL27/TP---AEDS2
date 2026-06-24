#include "lista.h"

void FLVaziaOcorrencia(TipoListaOcorrencia *Lista)
{ Lista -> Primeiro = (TipoApontadorOcorrencia) malloc(sizeof(TipoCelulaOcorrencia));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

int LEhVaziaOcorrencia(TipoListaOcorrencia Lista)
{ 
    return (Lista.Primeiro == Lista.Ultimo);
}

void InsereListaOcorrencia(TipoItemOcorrencia x, TipoListaOcorrencia *Lista)
{ 
    Lista -> Ultimo -> Prox = (TipoApontadorOcorrencia) malloc(sizeof(TipoCelulaOcorrencia));
    Lista -> Ultimo = Lista -> Ultimo -> Prox;
    Lista -> Ultimo -> Item = x;
    Lista -> Ultimo -> Prox = NULL;
}

void AtualizaOcorrencia(TipoListaOcorrencia *Lista, int idDoc) {
    TipoApontadorOcorrencia Aux;
    Aux = Lista->Primeiro->Prox;  // pula a celula cabeca
    
    // procura se ja existe um par com esse idDoc
    while (Aux != NULL) {
        if (Aux->Item.idDoc == idDoc) {
            Aux->Item.qtde++;  //se achou, incrementa
            return;
        }
        Aux = Aux->Prox;
    }
    
    // nao achou, cria um novo par
    TipoItemOcorrencia novoItem;
    novoItem.qtde = 1;
    novoItem.idDoc = idDoc;
    InsereListaOcorrencia(novoItem, Lista);
}

void ImprimeListaOcorrencia(TipoListaOcorrencia Lista)
{ TipoApontadorOcorrencia Aux;
  Aux = Lista.Primeiro -> Prox;
  while (Aux != NULL) 
    { 
      printf("<%d, %d>", Aux->Item.qtde, Aux->Item.idDoc);
      Aux = Aux -> Prox;
    }
}
