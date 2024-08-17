#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

/* Functions:
 * initMemory()
*/

Memory initMemory() {
    Memory memory;
    for(int i = 0; i < RAM_SIZE; i++) {
        /* Ideia inicial:
         * Dados da memória serem números, relacionados com os IDs dos livros
         * Talvez haja blocos com as informações dos livros, como título e autor, para poder modificar
         * struct RAM sujeita a mudança
        */
    }
}
