#include "idris_stdfgn.h"
#include "idris_rts.h"
#include "idris_gmp.h"
#include "idris_gc.h"

extern char** environ;

void putStr(char* str) {
    printf("%s", str);
}

int idris_writeStr(void* h, char* str) {
    FILE* f = (FILE*)h;
    if (fputs(str, f) >= 0) {
        return 0;
    } else {
        return -1;
    }
}

int isNull(void* ptr) {
    return ptr==NULL;
}

char* getEnvPair(int i) {
    return *(environ + i);
}

void idris_forceGC(void* vm) {
    idris_gc((VM*)vm);
}

typedef struct {
    char* string;
    int len;
} StrBuffer;

void* idris_makeStringBuffer(int len) {
    StrBuffer* sb = malloc(sizeof(StrBuffer));
    if (sb != NULL) {
        sb->string = malloc(len);
        sb->string[0] = '\0';
        sb->len = 0;
    }
    return sb;
}

void idris_addToString(void* buffer, char* str) {
    StrBuffer* sb = (StrBuffer*)buffer;
    int len = strlen(str);

    memcpy(sb->string + sb->len, str, len+1);
    sb->len += len;
}

VAL idris_getString(VM* vm, void* buffer) {
    StrBuffer* sb = (StrBuffer*)buffer;

    VAL str = MKSTR(vm, sb->string);
    free(sb->string);
    free(sb);
    return str;
}
