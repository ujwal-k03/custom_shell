#include "headr.h"

char *readline()
{
    size_t buffer_size = 0;
    char *line = NULL;

    //getting return value of getline
    int return_val = getline(&line,&buffer_size,stdin);

    //checking for code -1 i.e. error
    if(return_val == -1)
    {
        //subcase when only EOF character is present for input
        if(!feof(stdin))
        {
            perror("readline: ");
            exit(1);
        }
    }
    
    return line;
}
