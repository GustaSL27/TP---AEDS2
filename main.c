#include "hash/hash.c"
#include "PATRICIA/PATRICIA.c"

int main() {

    TabelaHash Tabela;
    TipoPesos pesos;
    Inicializa(Tabela);
    GeraPesos(pesos);

    TipoArvore arvore = NULL;

    FILE *entrada = fopen("entrada.txt", "r");
    if (!entrada) {
        fprintf(stderr, "Erro ao abrir entrada.txt\n");
        return 1;
    }

    int qtd;
    fscanf(entrada, "%d\n", &qtd);

    for (int i = 0; i < qtd; i++) {
        char nomeFabula[64];
        fscanf(entrada, "%s", nomeFabula);

        FILE *fabula = fopen(nomeFabula, "r");
        if (!fabula) {
            fprintf(stderr, "Erro ao abrir %s\n", nomeFabula);
            continue;
        }

        TipoChave palavra;
        TipoItem x;
        x.idDoc=i+1;
        while (fscanf(fabula, "%s", x.Palavra) == 1) {
            InsereHash(x, pesos, Tabela);
            arvore = InserePatricia(palavra, &arvore, i);
        }

        fclose(fabula);
    }

    fclose(entrada);

    printf("Hash apos entrada:\n\n");
    ImprimeHash(Tabela);

    printf("PATRICIA apos entrada:\n\n");
    ImprimePatricia(arvore);

    return 0;
}
