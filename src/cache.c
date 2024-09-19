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
Memory memory;

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

int find_cache_line(Cache *cache, int tag) {
    // Procura a tag pela cache
    for (int i = 0; i < CACHE_SIZE; i++) {
        if ((cache->positions[i].tag == tag) && (cache->positions[i].state != INVALID)) {
            return i;
        }
    }
    return -1; // não foi possível encontrar
}

void print_state(MesiState state) {
    printf("Estado: ");
    switch (state) {
    case MODIFIED:
        printf("MODIFIED\n");
        break;
    case EXCLUSIVE:
        printf("EXCLUSIVE\n");
        break;
    case SHARED:
        printf("SHARED\n");
        break;
    case INVALID:
        printf("INVALID\n");
        break;
    default:
        break;
    }
    printf("\n");
}

void print_segment(char **data) {
    while (**data != '|' && **data != '\0') {
        putchar(**data);
        (*data)++;
    }
}

void print_data(char *data) {
    printf("ID: ");
    print_segment(&data);
    printf("\n");

    if (*data == '|') data++; // Skip the delimiter
    printf("Titulo: ");
    print_segment(&data);
    printf("\n");

    if (*data == '|') data++; // Skip the delimiter
    printf("Autor: ");
    print_segment(&data);
    printf("\n");

    if (*data == '|') data++; // Skip the delimiter
    printf("Ano de lancamento: ");
    print_segment(&data);
    printf("\n");
}

static int FIFO_index[PROC_SIZE] = {0};
/* Posição para a próxima substituição FIFO
 * Na implementação, os índices estão sendo usados em ordem, portanto se inicia em 0
**/

int get_FIFO_index(int proc_id) {
    Cache *cache = &processors[proc_id].cache;
    int index = FIFO_index[proc_id];

    // Verifica a necessidade de write-back quando a cache está cheia
    if(cache->positions[index].state == MODIFIED) {
        int ram_pos = cache->positions[index].tag;
        strcpy(memory.ram[ram_pos].data, cache->positions[index].data);
        printf("Processor %d: Write-Back em tag: %d\n", proc_id, ram_pos);
        print_data(memory.ram[ram_pos].data);
    }

    FIFO_index[proc_id] = (FIFO_index[proc_id] + 1) % CACHE_SIZE; // próximo index até CACHE_SIZE
    return index;
}

int read_data(int proc_id, int ram_pos) {
    // proc_id = qual processador foi usado
    // tag = a tag usada para encontrar o dado (Memory.RAM.line)
    int tag = ram_pos;
    Cache *cache = &processors[proc_id].cache;

    int line_id = find_cache_line(cache, tag);
    if(line_id != -1) {
        // RH
        printf("OPERACAO:\n");
        printf("Processor %d:RH em tag: %d\n", proc_id, tag);
        print_state(cache->positions[line_id].state);
        print_data(cache->positions[line_id].data);
    } else {
        // RM

        // verificar se o dado está presente em outra cache
        int is_shared = 0; // 0 == não, 1 == sim
        for(int i = 0; i < PROC_SIZE; i++) {
            if(i != proc_id) { // pular a própria cache
                int other_line_id = find_cache_line(&processors[i].cache, tag);
                if(other_line_id != -1) {
                    // write-back caso outro processador tenha o dado em MODIFIED
                    if(processors[i].cache.positions[other_line_id].state == MODIFIED) {
                        strcpy(memory.ram[ram_pos].data, processors[i].cache.positions[other_line_id].data);
                        printf("Processor %d: Write-Back em tag: %d\n", proc_id, ram_pos);
                        print_data(memory.ram[ram_pos].data);
                        printf("----------\n");
                    }

                    processors[i].cache.positions[other_line_id].state = SHARED;
                    printf("ESTADO ALTERADO:\n");
                    printf("Processor %d: tag: %d\n", i, tag);
                    print_state(processors[i].cache.positions[other_line_id].state);
                    printf("----------\n");
                    is_shared = 1;
                }
            }
        }

        // Atualizar a cache
        int replace_id = get_FIFO_index(proc_id);
        CachePos *line = &cache->positions[replace_id];

        // Acessa o bloco da RAM
        strcpy(line->data, memory.ram[ram_pos].data);

        line->tag = tag;
        if(is_shared == 0) line->state = EXCLUSIVE;
        else line->state = SHARED;

        printf("OPERACAO:\n");
        printf("Processor %d:RM em tag: %d\n", proc_id, tag);
        print_state(cache->positions[replace_id].state);
        print_data(cache->positions[replace_id].data);
    }

    return 1;
}

int write_data(int proc_id, int ram_pos, char *new_data) {
    // proc_id = qual processador foi usado
    // tag = a tag usada para encontrar o dado (Memory.RAM.line)
    int tag = ram_pos;
    Cache *cache = &processors[proc_id].cache;

    int line_id = find_cache_line(cache, tag);
    if(line_id != -1) {
        // WH
        if(cache->positions[line_id].state == SHARED) {
            cache->positions[line_id].state = MODIFIED;

            // Verificar em qual cache o dado está presente
            for(int i = 0; i < PROC_SIZE; i++) {
                if(i != proc_id) { // pular a prórpia cache
                    int other_line_id = find_cache_line(&processors[i].cache, tag);
                    if(other_line_id != -1) {
                        processors[i].cache.positions[other_line_id].state = INVALID;
                        printf("ESTADO ALTERADO:\n");
                        printf("Processor %d: tag: %d\n", i, tag);
                        print_state(processors[i].cache.positions[other_line_id].state);
                        printf("----------\n");
                    }
                }
            }

        } else if(cache->positions[line_id].state == EXCLUSIVE) {
            cache->positions[line_id].state = MODIFIED;
        }

        // escreve o novo dado na cache
        strcpy(cache->positions[line_id].data, new_data);

        printf("OPERACAO:\n");
        printf("Processor %d:WH em tag: %d\n", proc_id, tag);
        print_state(cache->positions[line_id].state);
        print_data(cache->positions[line_id].data);

    } else {
        // WM

        // Atualizar a cache
        int replace_id = get_FIFO_index(proc_id);
        CachePos *line = &cache->positions[replace_id];

        // carrega a linha na cache
        line->tag = tag;
        strcpy(line->data, memory.ram[ram_pos].data);

        line->state = MODIFIED;

        // Verifica se a linha está presente em outra cache
        for(int i = 0; i < PROC_SIZE; i++) {
            if(i != proc_id) { // pular a própria cache
                int other_line_id = find_cache_line(&processors[i].cache, tag);
                if(other_line_id != -1) {
                    processors[i].cache.positions[other_line_id].state = INVALID;
                    printf("ESTADO ALTERADO:\n");
                    printf("Processor %d: tag: %d\n", i, tag);
                    print_state(processors[i].cache.positions[other_line_id].state);
                    printf("----------\n");
                }
            }
        }

        // escreve o novo dado na cache
        strcpy(line->data, new_data);

        printf("OPERACAO:\n");
        printf("Processor %d:WM em tag: %d\n", proc_id, tag);
        print_state(line->state);
        print_data(line->data);

    }

    return 1;
}
