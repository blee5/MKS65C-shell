# bell

bell is a shell written as a final project for the Systems Development class at Stuyvesant High School.
It's like a worse version of Bash.

NOTE: bell is currently incomplete

## Features

- Has nice builtin commands like `help`, `cd`, `exit`
- You can execute programs wow
- Multiple commands on one line (with `;`)
- Organic, free range, GMO free shell made in the USA
- Ceritifed memory leak free (probably not)

### TODO
- Redirect stdout and stdin with `>` and `<`
- Piping

### Maaybe (if I have time)
- Quotes and esacpe characters?
- Probably do something with SIGINT
- Tab completion
- Wildcards

## Bugs
- Piping into bell doesn't print newlines
- SIGTSTP (Ctrl+Z) isn't handled and I don't think I want to

## Functions
```c
void quit_shell();
int execute(char **args);
void print_user_info()
void execute_commands(char *buf)
void loop();
int main();

char *read_line();
char ***parse_lines(char *args);
char **parse_args(char *args);

int bell_cd(char **args);
int bell_help(char **args);
int bell_exit(char **args);
```
