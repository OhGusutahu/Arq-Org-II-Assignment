#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

/* Definitions:
 * struct memory
 * 
 * memory.c functions declarations
 */

#define BLOCK_SIZE 64 // tamanho do bloco da RAM
#define RAM_SIZE 50 // quantidade mínima de posições da memória

typedef struct {
    int line;
    char data[BLOCK_SIZE];
} RAM; // struct da RAM

typedef struct {
    RAM ram[RAM_SIZE];
} Memory; // struct da memória principal

Memory initMemory();
/*
 * Função para inicializar a memória principal
*/

#endif // MEMORY_H_INCLUDED
