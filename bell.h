#ifndef BELL
#define BELL
int main();
void loop();
void print_user_info();
void run_command(char *command);
void pipe_handler(char *line);
int execute(char **args);
void redir_exe(char **args, char *r_stdout);
#endif

#ifndef DEF_PARSER
#define DEF_PARSER
int MAX_ARGS;
int MAX_LENGTH;
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
