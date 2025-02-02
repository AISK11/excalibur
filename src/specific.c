#include "specific.h"
#include "files/lnk.h"

/* (FREE) Dump file in hexadecimal format. */
char *hd(FILE *file){
    /* Get file size. */
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    /* Double file size: 0x00 -> '0' (0x30) + '0' (0x30). */
    size *= 2;

    /* Allocate memory for file content + null byte. */
    char *content = (char *)malloc(size + 1);

    /* Read file char by char. */
    char *hexdigits = "0123456789abcdef";
    unsigned long long n = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        /* Convert char '\0' (0x00) to two chars: '0' (0x30) + '0' (0x30). */
        content[n++] = hexdigits[(c >> 4) & 0xF];
        content[n++] = hexdigits[c & 0xF];
    }
    content[n] = '\0';

    /* Allow file re-read. */
    rewind(file);

    /* Return content as hex string. */
    return content;
}


/* Display specific analysis report. */
void report_specific(FILE *file) {
    /* Read file content. */
    char *hexdump = hd(file);

    /* File signature. */
    char magic[9];
    strncpy(magic, hexdump, 8);
    magic[8] = '\0';

    /* Print filetype. */
    printf("   Type: ");
    if (strncmp(magic, "4c000000", 8) == 0) {
        printf("%s (%s)\n", "LNK", magic);
        lnk(hexdump);
    } else {
        printf("%s (%s)\n", "???", magic);
    }
    free(hexdump);
}
