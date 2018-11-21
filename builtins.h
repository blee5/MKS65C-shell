int bell_cd(char **args);
int bell_help(char **args);
int bell_exit(char **args);

extern char *builtins[];
extern int (*f_builtins[]) (char **);
