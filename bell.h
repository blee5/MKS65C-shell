#ifndef BELL
#define BELL
int execute(char **args);
void print_user_info();
void loop();
int main();
#endif

#ifndef DEF_PARSER
#define DEF_PARSER
int MAX_ARGS;
int MAX_LENGTH;
char **parse_args(char *args);
char *get_redir(char *line);
#endif

#ifndef DEF_BUILTINS
#define DEF_BUILTINS
int bell_cd(char **args);
int bell_help(char **args);
int bell_exit(char **args);

extern char *builtins[];
extern int (*f_builtins[]) (char **);
#endif
