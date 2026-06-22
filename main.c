#include <ctype.h>
#include <string.h>
#include "PATRICIA/patricia.h"
#include "stopwords/stopword.h"
#include "hash/hash.h"
#include "leitura/leitura.h"

int main() {
    TipoArvore arvore = NULL;
    TipoArvore arvorestop = NULL;
    char nomeArquivoStop[30] = "stopwords/stopwords.txt";
    char decisao;
    int opcao;

    TabelaHash Tabela;
    TipoPesos pesos;
    Inicializa(Tabela);
    GeraPesos(pesos);

    printf("Bem vindo ao sistema de indexacao de fabulas\n\n");

    do {
        printf("Qual funcao voce gostaria de usar:\n\n");
        printf("a - Receber e inserir as fabulas\n");
        printf("b - Imprimir a tabela hash e a arvore PATRICIA\n");
        printf("c - Buscar palavra\n");
        printf("d - Sair\n\n");
        printf("Digite a letra da funcao desejada: ");
        scanf(" %c", &decisao);

        if(decisao == 'a'){
            printf("Recebendo e inserindo as fabulas\n\n");

            LerStopWord(nomeArquivoStop, &arvorestop);

            int qtd = LerEntrada("fabulas/entrada.txt");
            if (qtd == -1) {
                printf("Erro ao ler entrada.txt\n");
            } else {
                LerFabulas("fabulas/fabula", qtd, &arvore, arvorestop, Tabela, pesos);
                printf("Fabulas recebidas e inseridas com sucesso\n\n");
            }
        }
        else if (decisao == 'b') {
            do
            {
                printf("\n1- Hash\n");
                printf("2- Patricia\n");
                printf("Digite a opcao desejada: ");
                scanf("%d",&opcao);

                if(opcao != 1 && opcao !=2){
                    printf("Opcao invalida!!!!\n\n");
                }
            } while (opcao !=1 && opcao != 2);

            if(opcao == 1){
                 printf("Imprimindo tabela hash...\n\n");
                 printf("Hash apos entrada:\n\n");
                 ImprimeHash(Tabela);
            }else if(opcao == 2){
                printf("Imprimindo arvore PATRICIA\n\n");
                printf("PATRICIA apos entrada:\n\n");
                ImprimePatricia(arvore);
            }

        }

        else if(decisao == 'c') {
            // busca por ordem de relevancia a ser implementada
        }

        else if(decisao == 'd') {
            printf("Finalizando o programa.\n");
        }
        else {
            printf("Opcao invalida! Tente novamente.\n\n");
        }

    } while (decisao != 'd');

    return 0;
}