#include "specific.h"

/* (FREE) Dump file in hexadecimal format. */
char *od(FILE *file){
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


/* Detect filetype. */
unsigned short idfile(char *hexdump) {
    if (strncmp(hexdump, "4c000000", 8) == 0) {
        return 1; /* LNK */
    } else {
        return 0; /* ??? */
    }
}


/* Display specific analysis report. */
void report_specific(FILE *file) {
    /* Read file content. */
    char *hexdump = od(file);

    /* Detect fieltype ID. */
    unsigned short file_id = idfile(hexdump);
    printf("ID: %hu\n", file_id);

    free(hexdump);
}
