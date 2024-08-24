#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "memory.h"

Processor processors[PROC_SIZE];
Memory memory;

void clear_buffer() {
    // para impedir buffer overflow
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char *argv[]) {
    

    if (argc == 2) {
        FILE *arq_dados = fopen(argv[1], "r");
        if(arq_dados == NULL) {
            // caso o arquivo não seja encontrado
            perror(NULL);
            exit(EXIT_FAILURE);
        }
        // inicializa a memória e os processadores
        initMemory(arq_dados);
        initProcessors();
        while(1) { // fazer várias operações
            int proc_id, ram_pos;
            char operation;

            printf("Escolha uma operacao ('r' = leitura, 'w' = escrita, 'q' = sair): ");
            operation = getchar();
            clear_buffer();

            if(operation == 'r') {
                printf("Insira o ID (0 a %d) do processador a ser usado: ", PROC_SIZE - 1);
                scanf("%d", &proc_id);
                clear_buffer();
                if(proc_id < 0 || proc_id >= PROC_SIZE) {
                    printf("ID invalido, tente novamente...\n");
                    continue; // volta para o começo do loop
                }
                printf("Insira o endereco (0 a %d) de memoria: ", RAM_SIZE - 1);
                scanf("%d", &ram_pos);
                clear_buffer();
                if(ram_pos < 0 || ram_pos >= RAM_SIZE) {
                    printf("Endereco invalido, tente movamente...\n");
                    continue; // volta para o começo do loop
                }
                read_data(proc_id, ram_pos);

            } else if(operation == 'w') {
                printf("Insira o ID (0 a %d) do processador a ser usado: ", PROC_SIZE - 1);
                scanf("%d", &proc_id);
                clear_buffer();
                if(proc_id < 0 || proc_id >= PROC_SIZE) {
                    printf("ID invalido, tente novamente...\n");
                    continue; // volta para o começo do loop
                }
                printf("Insira o endereco (0 a %d) de memoria: ", RAM_SIZE - 1);
                scanf("%d", &ram_pos);
                clear_buffer();
                if(ram_pos < 0 || ram_pos >= RAM_SIZE) {
                    printf("Endereco invalido, tente movamente...\n");
                    continue; // volta para o começo do loop
                }

                char data[BLOCK_SIZE];
                printf("Inisira o novo dado (<ID>|<titulo>|<autor>|<ano lancamento>) a ser escrito (max: 63 caracteres): ");
                if (fgets(data, sizeof(data), stdin) != NULL) {
                    // remover '\n' da data
                    int len = strlen(data);
                    if (len > 0 && data[len - 1] == '\n') {
                        data[len - 1] = '\0';
                    }
                    write_data(proc_id, ram_pos, data);
                } else {
                    printf("Erro na leitura dos dados.\n");
                }

            } else if(operation == 'q') {
                printf("Saindo do programa...\n");
                break;

            } else {
                printf("Operacao invalida, tente novamente...\n");
            }
            printf("\n");
        }

    } else {
        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s nome_arquivo\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
