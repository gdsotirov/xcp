#include <stdio.h>

#include "libxcpy.h"

int main(int argc, char* argv[]) {
    int bufsz = 0;

    if ( argc < 3 ) {
        printf("Usage: %s <source> <destination> [<buffer size in bytes>]\n", argv[0]); 
        return 0;
    }

    FILENAME source = argv[1];
    FILENAME destination = argv[2];

    /* Set buffer size if provided */
    if ( argc == 4 ) {
        bufsz = atoi(argv[3]);
        if ( bufsz <= 1024 ) {
            printf("error: Buffer size should be larger or equal to 1024 bytes.\n");
            return 1;
        }
        set_bufsize(bufsz);
    }    

    filecopy(source, destination);

    return 0;
}

