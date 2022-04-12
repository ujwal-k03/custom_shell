#include "headr.h"
#include "readline.c"
#include "parse.c"
#include "execute.c"
#include "builtins.c"
#include "extras.c"
#include "history.c"

int main( int argc, char** argv)
{   
    getcwd(PWD, sizeof(PWD));

    while(1)
    {
        printf("uBash>> ");

        char *line = readline();
        
        char *line2;
        strcpy(line2,line);

        add_to_history(line2);
        ArgVector *argarr = parse(line);
        parse_args(argarr);
    }
    
    return 1;
}
