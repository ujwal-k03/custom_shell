#include "headr.h"

int builtin_cd(ArgVector *argvector)
{
    
	if (argvector->vector[1] == NULL){
		fprintf(stderr, "uBash: cd: Atleast a single argument is required!\n");
	}
	else if (chdir(argvector->vector[1]) < 0){
		perror("uBash");
	}
	getcwd(PWD, sizeof(PWD));
	return 1;
};

int builtin_echo(ArgVector *argvector)
{
    int i = 1;
	while (1)
    {
		if (argvector->vector[i] == NULL)
        {
			break;
		}
		printf("%s ", argvector->vector[i]);
		i++;
	}
	printf("\n");
};

int builtin_help()
{
    printf("\nWelcome to the uBash shell! Short for ujwalBash.\n\n");
	printf("Here are the list of internal commands that are currently implemented: \n\n");
	printf("\t\t\t\t\t\t1. echo\n\t\t\t\t\t\t2. help\n\t\t\t\t\t\t3. pwd\n\t\t\t\t\t\t4. exit\n\t\t\t\t\t\t5. cd\n\t\t\t\t\t\t6. history\n");
	printf("\nOther than this, all external commands in your default PATH can also be used!\n\n");
};

int builtin_pwd()
{
    printf("%s\n", PWD);
	return 1;
};

int builtin_exit()
{
    exit(0);
};

int builtin_history()
{   
    int c;
    FILE *file;
    file = fopen("history.txt", "r");
    if (file) 
    {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }
};

int isbuiltin(ArgVector *argvector)
{	
	int check = 0;
	
	if(!strcmp(argvector->vector[0],"cd"))
        check = 1;
    else if(!strcmp(argvector->vector[0],"echo"))
        check = 1;
    else if(!strcmp(argvector->vector[0],"help"))
        check = 1;
    else if(!strcmp(argvector->vector[0],"pwd"))
        check = 1;
    else if(!strcmp(argvector->vector[0],"exit"))
        check = 1;
    else if(!strcmp(argvector->vector[0],"history"))
        check = 1;
    else 
		check =0;

	return check;
        
}