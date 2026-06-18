#include "patricia.h"

// retorna o bit da posicao do indice
int TipoBit(TipoIndex i, TipoChave k) {
    int c, j;
    if (i == 0) {  // bit vai de 1 a D (total de bits da palavra)
        return 0;
    } else {
        c = k[(i - 1) / 8]; // c assume o valor do caractere da palavra que contem o bit i
        for (j = 1; j <= 8 - ((i - 1) % 8 + 1); j++) c /=2;  //a divisão por 2 "empurra para a direita"
        return(c & 1); // o 1 retorna 0 nas posicoes a esquerda de j
    }
}

/* verifica se p e no externo*/
short VerificaExterno(TipoArvore p) {
    return (p->InternoExterno == Externo);
}                          

// cria um no interno
TipoArvore CriaNoInterno(int i, TipoArvore *esq, TipoArvore *dir) {
    TipoArvore p;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->InternoExterno = Interno;
    p->NO.NInterno.Esq = *esq;
    p->NO.NInterno.Dir = *dir;
    p->NO.NInterno.Index = i;
    return p;
}

// cria no externo
TipoArvore CriaNoExterno(TipoChave k) {
    TipoArvore p;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->InternoExterno = Externo;
    strncpy(p->NO.NExterno.Chave, k, MAXPALAVRA);
    p->NO.NExterno.contador = 1; // primeira vez que a palavra apareceu
    return p;
}

/* ALGORITMO DE PESQUISA*/


void Pesquisa(TipoChave k, TipoArvore t) {
    if (VerificaExterno(t)) {
        if (strcmp(k, t->NO.NExterno.Chave) == 0) {
            printf("Elemento encontrado\n");
        }
        else
            printf("Elemento nao encontrado\n");
        return;
    }
    if (TipoBit(t->NO.NInterno.Index, k) == 0)
        Pesquisa(k, t->NO.NInterno.Esq); //vai para esquerda
    else
        Pesquisa(k, t->NO.NInterno.Dir); //vai para direita

}

/*ALGORITMO DE INSERCAO*/

TipoArvore InsereEmDivergencia(TipoChave k, TipoArvore *t, int i) {
    TipoArvore p;
    if (VerificaExterno(*t) || i < (*t)->NO.NInterno.Index) {
        p = CriaNoExterno(k);
        if (TipoBit(i, k) == 1)
            return (CriaNoInterno(i, t, &p));
        else
            return (CriaNoInterno(i, &p, t));
    }
    else {
        if (TipoBit((*t)->NO.NInterno.Index, k) == 1)
            (*t)->NO.NInterno.Dir = InsereEmDivergencia(k, &((*t)->NO.NInterno.Dir), i);
        else
            (*t)->NO.NInterno.Esq = InsereEmDivergencia(k, &((*t)->NO.NInterno.Esq), i);
        return (*t);
    }
}

TipoArvore Insere(TipoChave k, TipoArvore *t) {
    TipoArvore p;
    int i;
    if (*t == NULL) {
        return (CriaNoExterno(k));
    }
    else {
        p = *t;
        while(!VerificaExterno(p)) {
            if (TipoBit(p->NO.NInterno.Index, k) == 1) 
                p = p->NO.NInterno.Dir;
            else
                p = p->NO.NInterno.Esq;
        }
        /* acha o primeiro bit dierente*/
        i = 1;
        while ((i <= D) && (TipoBit(i, k) == TipoBit(i, p->NO.NExterno.Chave)))
        i++;
        if (i > D) {
            p->NO.NExterno.contador++; // palavra ja exite, incrementa o contador
            return (*t);
        }
        else
            return(InsereEmDivergencia(k, t, i));
    }
}
