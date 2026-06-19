#include "hash/hash.c"
#include "PATRICIA/PATRICIA.c"

int main() {

    TabelaHash Tabela;
    TipoPesos pesos;
    Inicializa(Tabela);
    GeraPesos(pesos);

    FILE *entrada = fopen("../entrada.txt", "r");
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

        TipoItem x;
        x.idDoc=i+1;
        while (fscanf(fabula, "%s", x.Palavra) == 1) {
            InsereHash(x, pesos, Tabela);
        }

        fclose(fabula);
    }

    fclose(entrada);

    printf("Hash Após entrada:\n\n");
    ImprimeHash(Tabela);

    return 0;
}
