# bell

bell is a shell written as a final project for the Systems Development class at Stuyvesant High School.
It's like a worse version of Bash.

The `testcommands` directory has useful commands that you can run with bell by `bell < testcommands/<filename>` that demonstrate the functions of bell.

## Features

- Has nice builtin commands like `help`, `cd`, `exit`
- Quit shell by pressing Ctrl D
- You can execute programs wow
- Multiple commands on one line (with `;`)
- Redirecting with `>` works
- Organic, free range, GMO free shell made in the USA
- Ceritifed memory leak free (probably not)
- Redirect stdout and stdin with `>` and `<`

### TODO
- Piping

### Maaybe (if I have time)
- Quotes and esacpe characters?
- Tab completion
- Wildcards

## Bugs
- Most things are parsed by whitespace, so commands such as `ls>a` do not work.
- EOF (Ctrl+D) breaks stuff if entered in middle of line
- Doesn't kill child processes when exiting

## Functions
```c
int main();
void loop();
void print_user_info();
void run_command(char *command);
int execute(char **args);
void redir_exe(char **args, char *r_stdout);

char **parse_args(char *args);

int bell_cd(char **args);
int bell_help(char **args);
int bell_exit(char **args);
```
