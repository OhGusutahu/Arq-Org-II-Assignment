#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "cache.h"

/* Functions:
 * init_cache()
 * read_data()
 * write_data()
 */

Processor processors[PROC_SIZE];

Cache initCache() {
    Cache cache;
    for(int i = 0; i < CACHE_SIZE; i++) {
        cache.positions[i].tag = -1;
        cache.positions[i].state = INVALID;
        strcpy(cache.positions[i].data, "");
    }
}

int read_data(int proc_id, int ram_pos) {

}

int write_data(int proc_id, int ram_pos, char *new_data) {

}
