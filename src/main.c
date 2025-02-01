#include <sys/stat.h>
#include "utils.h"

int main(int argc, char *argv[]) {
    /* CLI arguments. */
    if (argc != 2) {
        return 1;
    }
    char *path = argv[1];

    /* Open file in read-only binary mode. */
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        return 2;
    }

    /* Check if file is regular file or symbolic link. */
    struct stat path_stat;
    stat(path, &path_stat);
    if (!(S_ISREG(path_stat.st_mode))) {
        return 2;
    }

    /* Basic analysis. */
    char *name = basename(path);
    printf("   Name: %s\n", name);
    unsigned long long size = wc(f);
    char *size_SI = size2human(size, SIZE_SI);
    char *size_IEC = size2human(size, SIZE_IEC);
    printf("   Size: %llu B (%s = %s)\n", size, size_SI, size_IEC);
    free(size_SI);
    free(size_IEC);
    long double entropy = ent(f);
    printf("Entropy: %.6Lf (%.0Lf%%)\n", entropy, entropy * 100 / 8);
    char *md5 = md5sum(f);
    printf("    MD5: %s\n", md5);
    free(md5);
    char *sha1 = sha1sum(f);
    printf("  SHA-1: %s\n", sha1);
    free(sha1);
    char *sha256 = sha256sum(f);
    printf("SHA-256: %s\n", sha256);
    free(sha256);

    /* Filetype analysis. */
    char *hexdump = od(f);
    if (strncmp(hexdump, "4c000000", 8) == 0) {
        puts("   Type: LNK");
    } else {
        puts("   Type: ???");
    }

    //printf("DEBUG: %s\n", hexdump);
    free(hexdump);

    /* Exit. */
    return 0;
}
