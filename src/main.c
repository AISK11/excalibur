#include "utils.h"
#include <getopt.h>
#include <sys/stat.h>

void help() {
    puts("NAME");
    puts("    excalibur - malware analyzer");
    puts("\nSYNOPSIS");
    puts("    excalibur [-bh] FILE");
    puts("\nDESCRIPTION");
    puts("    -b    Only perform basic analysis.");
    puts("    -h    Only show this help message.");
    puts("\nEXIT STATUS");
    puts("    0    success");
    puts("    1    error (option)");
    puts("    2    error (file)");
}


/* Display basic analysis. */
void report_basic(char *path, FILE *file) {
    char *name = basename(path);
    printf("   Name: %s\n", name);
    free(name);
    unsigned long long size = wc(file);
    char *size_SI = size2human(size, SIZE_SI);
    char *size_IEC = size2human(size, SIZE_IEC);
    printf("   Size: %llu B (%s = %s)\n", size, size_SI, size_IEC);
    free(size_SI);
    free(size_IEC);
    long double entropy = ent(file);
    printf("Entropy: %.6Lf (%.0Lf%%)\n", entropy, entropy * 100 / 8);
    char *md5 = md5sum(file);
    printf("    MD5: %s\n", md5);
    free(md5);
    char *sha1 = sha1sum(file);
    printf("  SHA-1: %s\n", sha1);
    free(sha1);
    char *sha256 = sha256sum(file);
    printf("SHA-256: %s\n", sha256);
    free(sha256);
}


/* Display filetype and execute specific analysis. */
void report_type(FILE *file) {
    /* Get file signature. */
    char magic[9];
    strncpy(magic, base16(file), 8);
    magic[8] = '\0';

    /* Print filetype. */
    if (strncmp(magic, "4c000000", 8) == 0) {
        printf("   Type: %s (%s)\n", "LNK", magic);
        // Analyze LNK...
    } else {
        printf("   Type: %s (%s)\n", "???", magic);
    }
}


int main(int argc, char *argv[]) {
    /* Default options. */
    unsigned char opt_b = 0;

    /* CLI option parser. */
    char *path = "";
    int opt;
    while ((opt = getopt(argc, argv, "-:bh")) != -1) {
        switch (opt) {
            case 'b':
                opt_b = 1;
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
    if (!opt_b) {
        report_type(file);
    }

    /* Exit. */
    return 0;
}
