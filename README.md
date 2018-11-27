# bell

bell is a shell written as a final project for the Systems Development class at Stuyvesant High School.
It's like a worse version of Bash.

The `testcommands` directory has useful commands that you can run with bell by `bell < testcommands/<filename>` that demonstrate the functions of bell.

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
- Tab completion
- Wildcards

## Bugs
- SIGTSTP (Ctrl+Z) isn't handled well

## Functions
```c
void quit_shell();
int execute(char **args);
void print_user_info()
void loop();
int main();

char *read_line();
char **parse_args(char *args);

int bell_cd(char **args);
int bell_help(char **args);
int bell_exit(char **args);
```
