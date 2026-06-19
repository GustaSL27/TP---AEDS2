#include "patricia.h"

// retorna o bit i da chave k
int TipoBit(TipoIndex i, TipoChave k) {
    if (i == 0) return 0;

    int byte = (i - 1) / 8;
    int bit = 7 - ((i - 1) % 8);

    // se ultrapassar o tamanho da string, considera 0
    if (byte >= strlen((char*)k))
        return 0;

    return (k[byte] >> bit) & 1;
}

// verifica se o no e externo (folha)
short VerificaExterno(TipoArvore p) {
    return (p->InternoExterno == Externo);
}

// cria no interno
// guarda o bit de decisao e os filhos esquerdo e direito
TipoArvore CriaNoInterno(int i, TipoArvore *esq, TipoArvore *dir) {
    TipoArvore p = (TipoArvore) malloc(sizeof(TipoPatNo));

    p->InternoExterno = Interno;
    p->NO.NInterno.Index = i;
    p->NO.NInterno.Esq = *esq;
    p->NO.NInterno.Dir = *dir;

    return p;
}

// cria no externo (folha)
// guarda a palavra e inicializa as contagens
TipoArvore CriaNoExterno(TipoChave k, int idDoc) {
    TipoArvore p = (TipoArvore) malloc(sizeof(TipoPatNo));

    p->InternoExterno = Externo;
    strcpy((char*)p->NO.NExterno.Chave, (char*)k);

    // zera todas as contagens
    for (int i = 0; i < MAXDOCS; i++)
        p->NO.NExterno.qtde[i] = 0;

    // marca a primeira ocorrencia no documento
    p->NO.NExterno.qtde[idDoc] = 1;

    return p;
}

// pesquisa uma palavra na arvore
void PesquisaPatricia(TipoChave k, TipoArvore t) {
    if (t == NULL) return;

    // chegou em folha
    if (VerificaExterno(t)) {
        if (strcmp((char*)k, (char*)t->NO.NExterno.Chave) == 0)
            printf("%s encontrada\n", k);
        return;
    }

    // decide qual lado seguir pelo bit
    if (TipoBit(t->NO.NInterno.Index, k) == 0)
        PesquisaPatricia(k, t->NO.NInterno.Esq);
    else
        PesquisaPatricia(k, t->NO.NInterno.Dir);
}

// insere uma palavra em um ponto de divergencia
TipoArvore InsereEmDivergencia(TipoChave k, TipoArvore *t, int i, int idDoc) {
    TipoArvore novo = CriaNoExterno(k, idDoc);

    // se o bit da nova chave for 0, vai para esquerda
    if (TipoBit(i, k) == 0)
        return CriaNoInterno(i, &novo, t);
    else
        return CriaNoInterno(i, t, &novo);
}

// insere palavra na arvore
TipoArvore InserePatricia(TipoChave k, TipoArvore *t, int idDoc) {
    int i;

    // arvore vazia -> cria folha
    if (*t == NULL)
        return CriaNoExterno(k, idDoc);

    // se chegou em folha
    if (VerificaExterno(*t)) {

        // se a palavra ja existe, incrementa quantidade nesse documento
        if (strcmp((char*)(*t)->NO.NExterno.Chave, (char*)k) == 0) {
            (*t)->NO.NExterno.qtde[idDoc]++;
            return *t;
        }

        // encontra o primeiro bit diferente entre as duas palavras
        for (i = 1; i <= D; i++) {
            if (TipoBit(i, k) != TipoBit(i, (*t)->NO.NExterno.Chave))
                break;
        }

        // cria no interno no ponto da divergencia
        return InsereEmDivergencia(k, t, i, idDoc);
    }

    // se for no interno, continua descendo pela arvore
    if (TipoBit((*t)->NO.NInterno.Index, k) == 0)
        (*t)->NO.NInterno.Esq =
            InserePatricia(k, &(*t)->NO.NInterno.Esq, idDoc);
    else
        (*t)->NO.NInterno.Dir =
            InserePatricia(k, &(*t)->NO.NInterno.Dir, idDoc);

    return *t;
}

// percorre e imprime a arvore
void ImprimePatricia(TipoArvore t) {
    if (t == NULL) return;

    // folha -> imprime palavra e ocorrencias
    if (VerificaExterno(t)) {
        printf("%-20s ", t->NO.NExterno.Chave);

        // imprime apenas os documentos onde apareceu
        for (int i = 0; i < MAXDOCS; i++) {
            if (t->NO.NExterno.qtde[i] > 0)
                printf("<%d, %d> ", t->NO.NExterno.qtde[i], i + 1);
        }

        printf("\n");
        return;
    }

    // percurso em ordem
    ImprimePatricia(t->NO.NInterno.Esq);
    ImprimePatricia(t->NO.NInterno.Dir);
}
