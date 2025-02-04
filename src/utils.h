#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WjCryptLib/WjCryptLib_Md5.h"
#include "WjCryptLib/WjCryptLib_Sha1.h"
#include "WjCryptLib/WjCryptLib_Sha256.h"

#define SIZE_SI  1000
#define SIZE_IEC 1024

/* Strip directory and suffix from file path. */
char *basename(char *path);

/* Count file size in bytes. */
unsigned long long wc(FILE *file);

/* (FREE) Show size in user-friendly way. */
char *size2human(unsigned long long size, unsigned short base);

/* Calculate file entropy. */
long double ent(FILE *file);

/* (FREE) Compute MD5 file digest. */
char *md5sum(FILE *file);

/* (FREE) Compute SHA-1 file digest. */
char *sha1sum(FILE *file);

/* (FREE) Compute SHA-256 file digest. */
char *sha256sum(FILE *file);

/* (FREE) Dump file in hexadecimal (base16) format. */
char *base16(FILE *file);

#endif
