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
void Pesquisa(TipoChave k, TipoArvore t) {
    if (t == NULL) return;

    // chegou em folha
    if (VerificaExterno(t)) {
        if (strcmp((char*)k, (char*)t->NO.NExterno.Chave) == 0)
            printf("%s encontrada\n", k);
        return;
    }

    // decide qual lado seguir pelo bit
    if (TipoBit(t->NO.NInterno.Index, k) == 0)
        Pesquisa(k, t->NO.NInterno.Esq);
    else
        Pesquisa(k, t->NO.NInterno.Dir);
}

// insere uma palavra em um ponto de divergencia
// mantem o Index sempre crescente ao descer na arvore,
// para que o percurso esquerda-direita preserve a ordem dos bits (alfabetica)
TipoArvore InsereEmDivergencia(TipoChave k, TipoArvore *t, int i, int idDoc) {
    TipoArvore p;
    if (VerificaExterno(*t) || i < (*t)->NO.NInterno.Index) {
        // insere o novo no interno aqui mesmo
        p = CriaNoExterno(k, idDoc);
        if (TipoBit(i, k) == 1)
            return (CriaNoInterno(i, t, &p));
        else
            return (CriaNoInterno(i, &p, t));
    }
    else {
        // ainda nao chegou no ponto certo, desce mais na arvore
        if (TipoBit((*t)->NO.NInterno.Index, k) == 1)
            (*t)->NO.NInterno.Dir = InsereEmDivergencia(k, &((*t)->NO.NInterno.Dir), i, idDoc);
        else
            (*t)->NO.NInterno.Esq = InsereEmDivergencia(k, &((*t)->NO.NInterno.Esq), i, idDoc);
        return (*t);
    }
}

// insere palavra na arvore
TipoArvore Insere(TipoChave k, TipoArvore *t, int idDoc) {
    TipoArvore p;
    int i;

    // arvore vazia -> cria folha
    if (*t == NULL)
        return CriaNoExterno(k, idDoc);

    // desce ate uma folha usando os bits da chave nova
    p = *t;
    while (!VerificaExterno(p)) {
        if (TipoBit(p->NO.NInterno.Index, k) == 1)
            p = p->NO.NInterno.Dir;
        else
            p = p->NO.NInterno.Esq;
    }

    // se a palavra ja existe, incrementa quantidade nesse documento
    if (strcmp((char*)p->NO.NExterno.Chave, (char*)k) == 0) {
        p->NO.NExterno.qtde[idDoc]++;
        return *t;
    }

    // encontra o primeiro bit diferente entre as duas palavras
    for (i = 1; i <= D; i++) {
        if (TipoBit(i, k) != TipoBit(i, p->NO.NExterno.Chave))
            break;
    }

    // cria no interno no ponto da divergencia
    return InsereEmDivergencia(k, t, i, idDoc);
}

// percorre e imprime a arvore
void Imprime(TipoArvore t) {
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
    Imprime(t->NO.NInterno.Esq);
    Imprime(t->NO.NInterno.Dir);
}
