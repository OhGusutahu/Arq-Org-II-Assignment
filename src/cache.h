#ifndef CACHE_H_INCLUDED
#define CACHE_H_INCLUDED

#include "memory.h" // para usar "BLOCK_SIZE"

/* Definitions:
 * struct cachePos
 * struct cache
 * struct processor
 * 
 * cache.c functions declarations
**/

#define CACHE_SIZE 5 // quantidade mínima de posições da cache
#define PROC_SIZE 3 // quantidade mínima de processadores

typedef enum {MODIFIED, EXCLUSIVE, SHARED, INVALID} MesiState;

typedef struct {
    int tag;
    MesiState state;
    char data[BLOCK_SIZE];
} CachePos; // struct da linha de cache

typedef struct {
    CachePos positions [CACHE_SIZE];
} Cache; // struct da cache

typedef struct {
    Cache cache;
} Processor;

extern Processor processors[PROC_SIZE];

Cache initCache();
/*
 * Função para inicializar o cache
**/

void initProcessors();
/*
 * Função para inicializar os processadores
**/

int read_data(int proc_id, int ram_pos);
/*
 * Função para simular a leitura de um dado
**/

int write_data(int proc_id, int ram_pos, char *new_data);
/*
 * Função para simular a escrita de um dado
**/

#endif // CACHE_H_INCLUDED
