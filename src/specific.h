#ifndef SPECIFIC_H
#define SPECIFIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* (FREE) Dump file in hexadecimal format. */
char *od(FILE *file);

/* Detect filetype. */
unsigned short idfile(char *base16);

/* Display specific analysis report. */
void report_specific(FILE *file);

#endif
