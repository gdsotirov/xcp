#include "libxcpy.h"

int main(int argc, char* argv[]) {
    if ( argc < 3 ) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 0;
    }

    FILENAME source = argv[1];
    FILENAME destination = argv[2];

    filecopy(source, destination);

    return 0;
}

