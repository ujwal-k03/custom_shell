#ifndef _EXECUTE_
#define _EXECUTE_

int execute_command(ArgVector *argvector);

int execute_line(ArgVector *fromVector, ArgVector *toVector, bool used_pipe);

int launch_external(ArgVector *argvector);

int parse_args(ArgVector *args);

#endif
