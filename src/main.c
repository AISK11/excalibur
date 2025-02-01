#include "basics.h"
#include "lnk.h"
#include <sys/stat.h>
#include <stdbool.h>

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


bool is_valid_file(char *path, FILE *file) {
    /* File could not be read. */
    if (file == NULL) {
        return false;
    }

    /* File is not regular file. */
    struct stat path_stat;
    stat(path, &path_stat);
    if (!(S_ISREG(path_stat.st_mode))) {
        return false;
    }
    return true;
}


int main(int argc, char *argv[]) {
    /* CLI arguments. */
    if (argc != 2) {
        return 1;
    }
    char *path = argv[1];

    /* Open file in read-only binary mode. */
    FILE *file = fopen(path, "rb");
    if (!is_valid_file(path, file)) {
        return 2;
    }

    /* Basic analysis. */
    basic_analysis(path, file);

    /* Filetype analysis. */
    char *hexdump = od(file);
    if (strncmp(hexdump, "4c000000", 8) == 0) {
        puts("   Type: LNK");
        analyze_lnk(hexdump);
    } else {
        puts("   Type: ???");
    }
    free(hexdump);

    /* Exit. */
    return 0;
}
