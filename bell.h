#ifndef DEF_PARSER
#define DEF_PARSER
const int MAX_ARGS;
const int MAX_LENGTH;
char *read_line();
char **parse_args(char *args);
#endif

#ifndef DEF_BUILTINS
#define DEF_BUILTINS
int bell_cd(char **args);
int bell_help(char **args);
int bell_exit(char **args);

extern char *builtins[];
extern int (*f_builtins[]) (char **);
#endif
