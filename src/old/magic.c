#include "magic.h"

/* (FREE) Analyze filetype. */
char *magic(FILE *file) {
    /* Hex file content. */
    char *hex = base16(file);

    /* File signature. */
    char magic[9];
    strncpy(magic, hex, 8);
    magic[8] = '\0';

    /* Filetype. */
    char *filetype = (char *)malloc(4);

    /* Print filetype. */
    printf("   Type: ");
    if (strncmp(magic, "4c000000", 8) == 0) {
        strncpy(filetype, "LNK\0", 4);
    } else {
        strncpy(filetype, "???\0", 4);
    }
    return *filetype;
}
