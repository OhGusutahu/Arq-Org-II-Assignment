#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "memory.h"

Processor processors[PROC_SIZE];
Memory memory;

// Functions if needed

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
        // smth smth

    } else {
        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s nome_arquivo\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
