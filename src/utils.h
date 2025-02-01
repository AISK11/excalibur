#ifndef UTILS_H
#define UTILS_H

#include <math.h>                         /* std -lm    */
#include <stdint.h>                       /* std        */
#include <stdio.h>                        /* std        */
#include <stdlib.h>                       /* std        */
#include <string.h>                       /* std        */
#include "WjCryptLib/WjCryptLib_Md5.h"    /* WjCryptLib */
#include "WjCryptLib/WjCryptLib_Sha1.h"   /* WjCryptLib */
#include "WjCryptLib/WjCryptLib_Sha256.h" /* WjCryptLib */

#define SIZE_SI  1000
#define SIZE_IEC 1024

/* Strip directory and suffix from file path. */
char *basename(char *path);

/* Calculate file entropy. */
long double ent(FILE *file);

/* (FREE) Compute MD5 file digest. */
char *md5sum(FILE *file);

/* (FREE) Dump file in hexadecimal format. */
char *od(FILE *file);

/* (FREE) Compute SHA-1 file digest. */
char *sha1sum(FILE *file);

/* (FREE) Compute SHA-256 file digest. */
char *sha256sum(FILE *file);

/* (FREE) Show size in user-friendly way. */
char *size2human(unsigned long long size, unsigned short base);

/* Count file size in bytes. */
unsigned long long wc(FILE *file);

#endif
