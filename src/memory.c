#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

/* Functions:
 * initMemory()
**/

Memory initMemory(FILE *arq) {
    // FILE *arq é um arquivo .txt com os dados dos livros da biblioteca
    // os dados estão na forma <index>|<título>|<autor>|<ano de lançamento>\n
    Memory memory;
    char block[BLOCK_SIZE];
    int index = 0;
    while((fgets(block, BLOCK_SIZE, arq) != NULL) && (index < RAM_SIZE)) {
        // como os dados estão separados por '\n', fgets facilmente os grava
        block[strcspn(block, "\n")] = '\0';

        memory.ram[index].line = index;
        strncpy(memory.ram[index].data, block, BLOCK_SIZE);

        index++;
    }

    return memory;
}
