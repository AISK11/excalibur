#include "basic.h"
#include "specific.h"
#include <getopt.h>
#include <stdbool.h>
#include <sys/stat.h>

void help() {
    puts("NAME");
    puts("    excalibur - malware analyzer");
    puts("\nSYNOPSIS");
    puts("    excalibur [-bdh] <FILE>");
    puts("\nDESCRIPTION");
    puts("    -b    Only perform basic analysis.");
    puts("    -d    Only dump file content in base16.");
    puts("    -h    Only show this help message.");
    puts("\nEXIT STATUS");
    puts("    0    success");
    puts("    1    error (option)");
    puts("    2    error (file)");
}


int main(int argc, char *argv[]) {
    /* Default options. */
    bool only_dump = false;  /* -d */
    bool only_basic = false; /* -b */

    /* CLI option parser. */
    int opt;
    char *path = "";
    while ((opt = getopt(argc, argv, "-:bdh")) != -1) {
        switch (opt) {
            case 'b':
                only_basic = true;
                break;
            case 'd':
                only_dump = true;
                break;
            case 'h':
                help();
                return 0;
            case '?':
                return 1;
                break;
            case ':':
                return 1;
                break;
            case 1:
                path = optarg;
                break;
        }
    }

    /* Open regular file in read-only binary mode. */
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        return 2;
    }
    struct stat path_stat;
    stat(path, &path_stat);
    if (!(S_ISREG(path_stat.st_mode))) {
        return 2;
    }

    /* Process passed options. */
    if (only_basic) {
        report_basic(path, file);
        return 0;
    } else if (only_dump) {
        printf("%s\n", od(file));
        return 0;
    }

    /* Analysis. */
    report_basic(path, file);
    //report_specific(file);

    /* Exit. */
    return 0;
}
