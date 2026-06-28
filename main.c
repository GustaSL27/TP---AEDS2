#include <ctype.h>
#include <string.h>
#include "PATRICIA/patricia.h"
#include "stopwords/stopword.h"
#include "hash/hash.h"
#include "leitura/leitura.h"
#include "time.h"

int main() {
    TipoArvore arvore = NULL;
    TipoArvore arvorestop = NULL;
    char nomeArquivoStop[30] = "stopwords/stopwords.txt";
    char decisao;
    int opcao;
    clock_t tempo_inicio_Hash, tempo_final_Hash;
    clock_t tempo_inicio_PATRICIA, tempo_final_PATRICIA;
    double tempo_total_Hash = 0;
    double tempo_total_PATRICIA = 0;
    int total_elementos_array = 0;

    TabelaHash Tabela;
    TipoPesos pesos;
    Inicializa(Tabela);
    GeraPesos(pesos);

    printf("Bem vindo ao sistema de indexacao de fabulas\n\n");

    // Começo do menu
    do {
        printf("\nQual funcao voce gostaria de usar:\n\n");
        printf("a - Receber e inserir as fabulas\n");
        printf("b - Imprimir a tabela hash e a arvore PATRICIA\n");
        printf("c - Buscar palavra\n");
        printf("d - Sair\n\n");
        printf("Digite a letra da funcao desejada: ");
        scanf(" %c", &decisao);


        // Escolhe inserir
        if(decisao == 'a'){
            LerStopWord(nomeArquivoStop, &arvorestop);

            // Salva a quantidade de fábulas na variável qtd
            int qtd = LerEntrada("fabulas/entrada.txt");
            if (qtd == -1) {
                printf("Erro ao ler entrada.txt\n");
            }

            do{
                printf("\nOnde voce gostaria de inserir as fabulas:\n");
                printf("\n1- Hash\n");
                printf("2- Patricia\n");
                printf("Digite a opcao desejada: ");
                scanf("%d",&opcao);

                if(opcao != 1 && opcao !=2){
                    printf("Opcao invalida!!!!\n\n");
                }
            } while (opcao !=1 && opcao != 2);

            if(opcao == 1){
                printf("Inserindo na tabela hash...\n\n");

                tempo_inicio_Hash = clock();
                LerFabulasHash("fabulas/fabula", qtd, arvorestop, Tabela, pesos, &total_elementos_array);
                tempo_final_Hash = clock();

                tempo_total_Hash = (double)(tempo_final_Hash - tempo_inicio_Hash) / CLOCKS_PER_SEC;
                printf("Insercao hash concluida\n\n");
            }
            else if(opcao == 2){
                printf("Inserindo na arvore PATRICIA\n\n");

                tempo_inicio_PATRICIA = clock();
                LerFabulasPATRICIA("fabulas/fabula", qtd, &arvore, arvorestop);
                tempo_final_PATRICIA = clock();

                tempo_total_PATRICIA = (double)(tempo_final_PATRICIA - tempo_inicio_PATRICIA) / CLOCKS_PER_SEC;
                printf("Insercao PATRICIA concluida\n\n");
            }
        }

        // Escolhe imprimir (ordem alfabetica + estatistica de tempo)
        else if (decisao == 'b') {
            do
            {
                printf("Qual estrutura voce gostaria de imprimir\n");
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
                ImprimeArrayOrdenado(total_elementos_array);
                printf("Imprimindo tempo da tabela hash...\n\n");
                printf("%.5f segundos", tempo_total_Hash);
            }
            else if(opcao == 2){
                printf("Imprimindo arvore PATRICIA\n\n");
                printf("PATRICIA apos entrada:\n\n");
                ImprimePatricia(arvore);
                printf("Imprimindo tempo da arvore PATRICIA\n\n");
                printf("%.5f segundos", tempo_total_PATRICIA);
            }

        }

        else if(decisao == 'c') {
            // busca por ordem de relevancia a ser implementada
        }

        else if(decisao == 'd'){
            printf("Finalizando o programa.\n");
        }

        else{
            printf("Opcao invalida! Tente novamente.\n\n");
        }

    } while (decisao != 'd');

    return 0;
}
