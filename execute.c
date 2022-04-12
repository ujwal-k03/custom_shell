#include "headr.h"

int launch_external(ArgVector *argvector)
{
    pid_t pid, wait_pid;
    int status_code;

    pid = fork();

    if (pid == 0) 
    {
        if (execvp(argvector->vector[0], argvector->vector) == -1) 
        {
            perror("uBash");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) 
    {
        perror("uBash");
    } 
    else 
    {
        do 
        {
            wait_pid = waitpid(pid, &status_code, WUNTRACED);
        } 
        while (!WIFEXITED(status_code) && !WIFSIGNALED(status_code));
    }

    return 1;
}

int execute_command(ArgVector *argvector)
{   
    int status_code;
    if(!strcmp(argvector->vector[0],"cd"))
        status_code = builtin_cd(argvector);
    else if(!strcmp(argvector->vector[0],"echo"))
        status_code = builtin_echo(argvector);
    else if(!strcmp(argvector->vector[0],"help"))
        status_code = builtin_help();
    else if(!strcmp(argvector->vector[0],"pwd"))
        status_code = builtin_pwd();
    else if(!strcmp(argvector->vector[0],"exit"))
        status_code = builtin_exit();
    else if(!strcmp(argvector->vector[0],"history"))
        status_code = builtin_history();
    else 
        status_code = launch_external(argvector);
}

int parse_args(ArgVector *args) 
{      
    ArgVector *curr = malloc(sizeof(ArgVector));
    ArgVector *curr2 = malloc(sizeof(ArgVector));

    if (curr == NULL || curr2 == NULL) 
    {
        perror("uBASH");
    };

    initArgVector(curr);
    initArgVector(curr2);

    bool used_pipe = false;

    // EXECUTING LOOP
    for (int i = 0; i < args->count; i++) 
    {   
        if(args->vector[i]==NULL)
        {
            continue;
        }
        if (!strcmp(args->vector[i], "|"))
        {   
            used_pipe = true;  
        } 
        else 
        {   
            if(used_pipe)
                addtoArgVector(curr2, args->vector[i]); 
            else
                addtoArgVector(curr,args->vector[i]);
        }
    };

    execute_line(curr,curr2,used_pipe);

    return 0;

}

int execute_line(ArgVector *fromVector, ArgVector *toVector, bool used_pipe)
{   
    // Exit special case
    if(!strcmp(fromVector->vector[0],"exit"))
    {
        exit(0);
    }
    
    int fd[2];
	pid_t pid1, pid2;

	pipe(fd);

	/* Create the first child and run the first command. */
	pid1 = fork();
	if (pid1<0) {
		perror("First fork() failed!");
		return -1;
	}
	if (pid1==0) {
		/* Set the process output to the input of the pipe. */
        
        if(used_pipe)
        {   
            close(fd[0]);
            dup2(fd[1],1);
        }

        if(isbuiltin(fromVector))
        {
            execute_command(fromVector);
            exit(0);
        }
        else
        execvp(fromVector->vector[0],fromVector->vector);
        perror("uBash");
	}

    if(used_pipe)
    {
        /* Create the second child and run the second command. */
        pid2 = fork();
        if (pid2<0) {
            perror("Second fork() failed!");
            return -1;
        }
        if (pid2==0) {
		/* Set the process input to the output of the pipe. */
		close(fd[1]);
		dup2(fd[0],0);
		
        if(isbuiltin(toVector))
        {
            execute_command(toVector);
            exit(0);
        }
        else
        execvp(toVector->vector[0],toVector->vector);
        perror("uBash");
	}
    }
	

	close(fd[0]);

    if(used_pipe)
	close(fd[1]);

	/* Wait for the children to finish, then exit. */
	waitpid(pid1,NULL,0);

    if(used_pipe)
	waitpid(pid2,NULL,0);

	return 0;
}
