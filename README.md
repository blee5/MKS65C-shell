# bell

bell is a shell written as a final project for the Systems Development class at Stuyvesant High School.
It's like a worse version of Bash.

Run `testscript` to test its basic features.

## Features

- Has nice builtin commands like `help`, `cd`, `exit`
- You can exit the shell by pressing Ctrl+D (if the line is empty)
- You can execute programs wow!!!!
- Multiple commands on one line (with `;`)
- Redirect stdout and stdin with `>` and `<` (or `>>`)
- Pipe commands with `|` (currently only one pipe per command is supported)
- Organic, free range, GMO free shell made in the USA
- (Probably) doesn't leak memory

### TODO
- Redirect stderror (I can just copy and paste the current code and modify it to fit stderror but I'm kinda lazy)
- Pipe more than once

## Bugs (aka *features*)
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
