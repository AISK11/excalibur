#include "basic.h"
#include "specific.h"
#include <getopt.h>
#include <stdbool.h>
#include <sys/stat.h>

void help() {
    puts("NAME");
    puts("    excalibur - malware analyzer");
    puts("\nSYNOPSIS");
    puts("    excalibur [-bh] <FILE>");
    puts("\nDESCRIPTION");
    puts("    -b    Only perform basic analysis.");
    puts("    -h    Only show this help message.");
    puts("\nEXIT STATUS");
    puts("    0    success");
    puts("    1    error (option)");
    puts("    2    error (file)");
}


int main(int argc, char *argv[]) {
    /* Default options. */
    bool opt_b = false; /* -b */

    /* CLI option parser. */
    char *path = "";
    int opt;
    while ((opt = getopt(argc, argv, "-:bh")) != -1) {
        switch (opt) {
            case 'b':
                opt_b = true;
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
    report_basic(path, file);
    if (opt_b) {
        return 0;
    }
    report_specific(file);

    /* Exit. */
    return 0;
}
