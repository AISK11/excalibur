#include "utils.h"

/* Strip directory and suffix from file path. */
char *basename(char *path) {
    /* Cross-platform delimeter declaration. */
    #ifdef __unix__
        char *delimeter = strrchr(path, '/');
    #else
        char *delimeter = strrchr(path, '\\');
    #endif

    /* Return string after delimeter. */
    if (!delimeter) {
        return strdup(path);
    }
    return strdup(delimeter + 1);
}


/* Count file size in bytes. */
unsigned long long wc(FILE *file) {
    /* Get file size. */
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    /* Return size in bytes. */
    return size;
}


/* (FREE) Show size in user-friendly way. */
char *size2human(unsigned long long size, unsigned short base) {
    /* Size string, max value: '123.56 kiB' (10 + null byte). */
    char *s = (char *)malloc(11);

    /* Calculate human readable size. */
    long double size_h = size;
    unsigned char count = 0;
    do {
        size_h /= base;
        count++;
    }
    while (size_h >= base);

    /* Convert double and add value to string. */
    sprintf(s, "%.2Lf", size_h);

    /* Append unit to string. */
    size_t s_length = strlen(s);
    s[s_length++] = ' ';
    switch (count) {
        case 1:
            s[s_length++] = 'k';
            break;
        case 2:
            s[s_length++] = 'M';
            break;
        case 3:
            s[s_length++] = 'G';
            break;
        case 4:
            s[s_length++] = 'T';
            break;
        case 5:
            s[s_length++] = 'P';
            break;
        case 6:
            s[s_length++] = 'E';
            break;
        case 7:
            s[s_length++] = 'Z';
            break;
        case 8:
            s[s_length++] = 'Y';
            break;
        case 9:
            s[s_length++] = 'R';
            break;
        case 10:
            s[s_length++] = 'Q';
            break;
        default:
            s[s_length++] = '?';
    }
    if (base == SIZE_IEC) {
        s[s_length++] = 'i';
    }
    s[s_length++] = 'B';
    s[s_length] = '\0';

    /* Return human readable size string. */
    return s;
}


/* Calculate file entropy. */
long double ent(FILE *file) {
    /* Amount of bytes in a file. */
    unsigned long long bytes = 0;

    /* Store count fo each possible byte (0x00 -> 0xff). */
    unsigned long long count[256] = {0};

    /* Count byte frequencies. */
    int byte;
    while ((byte = fgetc(file)) != EOF) {
        count[(unsigned char)byte]++;
        bytes++;
    }

    /* Calculate entropy.
     * 0.0 = 0x01 0x01 .. 0x01
     * 8.0 = 0x00 0x01 .. 0xff
     */
    long double entropy = 0.0;
    unsigned short i;
    for (i = 0; i < 256; i++) {
        if (count[i] > 0) {
            long double probability = (long double)count[i] / bytes;
            entropy -= probability * log2(probability);
        }
    }

    /* Allow file re-read. */
    rewind(file);

    /* Return entropy. */
    return entropy;
}


/* (FREE) Compute MD5 file digest. */
char *md5sum(FILE *file) {
    /* MD5 hash size = 16 bytes. */
    #define HASH_SIZE 16

    /* Buffer to read 1024 bytes at a time. */
    char data[1024];

    /* Calculate hash. */
    Md5Context md5Context;
    Md5Initialise(&md5Context);
    size_t data_read;
    while ((data_read = fread(data, 1, sizeof(data), file)) > 0) {
        Md5Update(&md5Context, data, (uint32_t)data_read);
    }
    MD5_HASH md5Hash;
    Md5Finalise(&md5Context, &md5Hash);
    char* hash = (char*)malloc(HASH_SIZE * 2 + 1);
    for (int i = 0; i < HASH_SIZE; i++) {
        sprintf(hash + (i * 2), "%02x", md5Hash.bytes[i]);
    }
    hash[HASH_SIZE * 2] = '\0';
    #undef HASH_SIZE

    /* Allow file re-read. */
    rewind(file);

    /* Return hash string. */
    return hash;
}


/* (FREE) Compute SHA-1 file digest. */
char *sha1sum(FILE *file) {
    /* SHA-1 hash size = 20 bytes. */
    #define HASH_SIZE 20

    /* Buffer to read 1024 bytes at a time. */
    char data[1024];

    /* Calculate hash. */
    Sha1Context sha1Context;
    Sha1Initialise(&sha1Context);
    size_t data_read;
    while ((data_read = fread(data, 1, sizeof(data), file)) > 0) {
        Sha1Update(&sha1Context, data, (uint32_t)data_read);
    }
    SHA1_HASH sha1Hash;
    Sha1Finalise(&sha1Context, &sha1Hash);
    char* hash = (char*)malloc(HASH_SIZE * 2 + 1);
    for (int i = 0; i < HASH_SIZE; i++) {
        sprintf(hash + (i * 2), "%02x", sha1Hash.bytes[i]);
    }
    hash[HASH_SIZE * 2] = '\0';
    #undef HASH_SIZE

    /* Allow file re-read. */
    rewind(file);

    /* Return hash string. */
    return hash;
}


/* (FREE) Compute SHA-256 file digest. */
char *sha256sum(FILE *file) {
    /* SHA-256 hash size = 32 bytes. */
    #define HASH_SIZE 32

    /* Buffer to read 1024 bytes at a time. */
    char data[1024];

    /* Calculate hash. */
    Sha256Context sha256Context;
    Sha256Initialise(&sha256Context);
    size_t data_read;
    while ((data_read = fread(data, 1, sizeof(data), file)) > 0) {
        Sha256Update(&sha256Context, data, (uint32_t)data_read);
    }
    SHA256_HASH sha256Hash;
    Sha256Finalise(&sha256Context, &sha256Hash);
    char* hash = (char*)malloc(HASH_SIZE * 2 + 1);
    for (int i = 0; i < HASH_SIZE; i++) {
        sprintf(hash + (i * 2), "%02x", sha256Hash.bytes[i]);
    }
    hash[HASH_SIZE * 2] = '\0';
    #undef HASH_SIZE

    /* Allow file re-read. */
    rewind(file);

    /* Return hash string. */
    return hash;
}
