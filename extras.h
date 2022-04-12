#ifndef _EXTRAS_
#define _EXTRAS_

typedef struct {
    char **vector;
    ssize_t count;
    ssize_t size;
} ArgVector;

void initArgVector(ArgVector *argvector);

void addtoArgVector(ArgVector *argvector, char *element);

void freeArgVector(ArgVector *argvector);

#endif
