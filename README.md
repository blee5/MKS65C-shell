# bell

bell is a shell written as a final project for the Systems Development class at Stuyvesant High School.
It's like a worse version of Bash.


NOTE: bell is currently incomplete

## Features

Can do basic stuff a shell should do, like:
- Builtin commands like `help`, `cd`, `exit`
- Execute programs
- wow that's it

### TODO
- Multiple commands on one line (with `;`)
- Redirect stdout and stdin with `>` and `<`
- Piping

### Maaybe (if I have time)
- Quotes and esacpe characters?
- Probably do something with SIGINT
- Tab completion
- Wildcards

## Bugs
- idk

## Functions
```
void quit_shell();
int execute(char **args);
void loop();
int main();

char *read_line();
char **parse_args(char *args);

int bell_cd(char **args);
int bell_help(char **args);
int bell_exit(char **args);
```
