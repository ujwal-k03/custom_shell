#ifndef _BUILTINS_
#define _BUILTINS_

int builtin_cd(ArgVector *argvector);

int builtin_echo(ArgVector *argvector);

int builtin_help();

int builtin_pwd();

int builtin_exit();

int builtin_history();

int isbuiltin(ArgVector *argvector);

#endif