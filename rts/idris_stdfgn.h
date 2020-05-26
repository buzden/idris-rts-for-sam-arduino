#ifndef _IDRISSTDFGN_H
#define _IDRISSTDFGN_H

#include "idris_rts.h"

// A collection of useful standard functions to be used by the prelude.

void putStr(char* str);
//char* readStr();

// return 0 on success
int idris_writeStr(void*h, char* str);

// Some machinery for building a large string without reallocating
// Create a string with space for 'len' bytes
void* idris_makeStringBuffer(int len);
void idris_addToString(void* buffer, char* str);
VAL idris_getString(VM* vm, void* buffer);

int isNull(void* ptr);

void idris_forceGC();

#endif
