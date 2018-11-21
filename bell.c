#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "bell.h"

#define BOLD "\e[1m"
#define REGULAR "\e[0m"
#define GREEN "\x1B[32m"
#define idk "\x1B[34m"
#define WHITE "\x1B[37m"

char *buf;
char ***commands;

/*
 * Clean up stuff and exit
 */
void quit_shell()
{
    int i;
    for (i = 0; commands[i]; i++)
    {
        free(commands[i]);
    }
    free(commands);
    free(buf);
    exit(0);
}

/*
 * Runs a program or a shell builtin.
 */
int execute(char **args)
{
    int i;
    if (args[0] == 0)
    {
        // empty command
        return 0;
    }
    // run if builtin
    for (i = 0; builtins[i]; i++)
    {
        if (strcmp(args[0], builtins[i]) == 0)
        {
            return (*f_builtins[i])(args);
        }
    }

    // run program
    if (fork())
    {
        // parent
        int status;
        wait(&status);
        return 0;
    }
    else
    {
        // child
        execvp(args[0], args);
        printf("%s: %s\n", args[0], strerror(errno));
        quit_shell();
    }
}

void loop()
{
    int i;
    char cwd[256];
    while (1)
    {
        getcwd(cwd, 256);
        printf(GREEN BOLD "%s" WHITE REGULAR " >> ", cwd);
        buf = read_line();
        commands = parse_line(buf);
        for (i = 0; commands[i]; i++)
        {
            if (execute(commands[i]) == 1)
            {
                quit_shell();
            }
        }
        free(buf);
        for (i = 0; commands[i]; i++)
        {
            free(commands[i]);
        }
        free(commands);
    }
}

int main()
{
    signal(SIGINT, quit_shell);
    loop();
    return 0;
}
