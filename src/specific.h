#ifndef SPECIFIC_H
#define SPECIFIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* (FREE) Dump file in hexadecimal format. */
char *hd(FILE *file);

/* Display specific analysis report. */
void report_specific(FILE *file);

#endif
