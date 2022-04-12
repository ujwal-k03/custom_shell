#include "headr.h"

ArgVector *parse(char *line)
{   
    ArgVector *ArgVector_Return;
    ArgVector_Return = (ArgVector* )malloc(sizeof(ArgVector));

    int buffer_size = 64;
    int index = 0;
    int cnt=0;

    char **arg_array = (char **)malloc(buffer_size * sizeof(char *));
    char *token;

    token = strtok(line, " \t\n");

    if (!arg_array) 
    {
    fprintf(stderr, "arg_array: Allocation Error!\n");
    exit(1);
    }
    while(token!=NULL)
    {
        arg_array[index] = token;
        index++;

        if(index >= buffer_size)
        {
            buffer_size+=64;
            arg_array = realloc(arg_array, buffer_size*sizeof(char *));

            if (!arg_array) 
            {
            fprintf(stderr, "arg_array: Allocation Error!\n");
            exit(1);
            }
        }

        token = strtok(NULL, " \t\n\r");
    }

    arg_array[index]=NULL;
    
    ArgVector_Return->vector = arg_array;
    ArgVector_Return->count = index;
    
    return ArgVector_Return;
}
