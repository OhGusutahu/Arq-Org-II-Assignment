#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "cache.h"

/* Functions:
 * init_cache()
 * read_data()
 * write_data()
**/

Processor processors[PROC_SIZE];

Cache initCache() {
    Cache cache;
    for(int i = 0; i < CACHE_SIZE; i++) {
        cache.positions[i].tag = -1;
        cache.positions[i].state = INVALID;
        strcpy(cache.positions[i].data, "");
    }
    return cache;
}

void initProcessors() {
    for (int i = 0; i < PROC_SIZE; i++) {
        processors[i].cache = initCache();
    }
}

/***************************************/
// Funções beta, talvez mude

int find_cache_line(Cache *cache, int tag) {
    // Procura a tag pela cache
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache->positions[i].tag == tag) {
            return i;
        }
    }
    return -1; // não foi possível encontrar
}

int FIFO_index = 0;
/* Posição para a próxima substituição FIFO
 * Na implementação, os índices estão sendo usados em ordem, portanto se inicia em 0
**/

int get_FIFO_index() {
    int index = FIFO_index;
    FIFO_index = (FIFO_index + 1) % CACHE_SIZE; // próximo index até CACHE_SIZE
    return index;
}

// Fim das funções beta
/***************************************/

int read_data(int proc_id, int ram_pos) {

}

int write_data(int proc_id, int ram_pos, char *new_data) {

}
