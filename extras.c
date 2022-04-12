#include "headr.h"

static size_t initSize = 2;

void initArgVector(ArgVector *ArgVector) 
{
    ArgVector->vector = malloc(initSize * sizeof(char *));

    if (ArgVector->vector == NULL) 
    {
        // Throw fatal error
        //CHANGE
        //fatal_error_check(0, 0);
    }

    ArgVector->vector[0] = NULL;
    ArgVector->count = 0;
    ArgVector->size = initSize;
};

static void increase_size(ArgVector *argvector) 
{
    argvector->size *= 2;

    argvector->vector = realloc(argvector->vector, argvector->size * sizeof(char *));

    if (argvector->vector == NULL) { 
        // Throw fatal error
        //fatal_error_check(0, 0);
    }

    for (int i = argvector->count; i < argvector->size; i++) 
    {
        argvector->vector[i] = NULL;
    }
};

void addtoArgVector(ArgVector *argvector, char *element) 
{
    if (argvector->count == argvector->size) 
    {
        increase_size(argvector);
    } 
    argvector->vector[argvector->count++] = element;
};

void freeArgVector(ArgVector *argvector) 
{
    for (int i = 0; i < argvector->count; i++) 
    {
        free(argvector->vector[i]);
        argvector->vector[i] = NULL;
    }

    free(argvector->vector);
    argvector->count = argvector->size = 0;
};