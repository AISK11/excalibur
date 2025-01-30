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
    unsigned long long size = wc(f);
    char *size_SI = size2human(size, SIZE_SI);
    char *size_IEC = size2human(size, SIZE_IEC);
    long double entropy = ent(f);
    char *md5 = md5sum(f);
    char *sha1 = sha1sum(f);
    char *sha256 = sha256sum(f);
    printf("   Name: %s\n", name);
    printf("   Size: %llu B (%s = %s)\n", size, size_SI, size_IEC);
    printf("Entropy: %.6Lf (%.0Lf%%)\n", entropy, entropy * 100 / 8);
    printf("    MD5: %s\n", md5);
    printf("  SHA-1: %s\n", sha1);
    printf("SHA-256: %s\n", sha256);
    free(size_SI);
    free(size_IEC);
    free(md5);
    free(sha1);
    free(sha256);

    /* Exit. */
    return 0;
}
