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
 * Runs a program or a shell builtin.
 */
int execute(char **args)
{
    int i;
    if (args[0] == 0)
    {
        /* Command was empty */
        return 0;
    }
    /* Check and run if builtin command */
    for (i = 0; builtins[i]; i++)
    {
        if (strcmp(args[0], builtins[i]) == 0)
        {
            return (*f_builtins[i])(args);
        }
    }

    /* Run program */
    if (fork())
    {
        /* Parent process */
        int status;
        wait(&status);
        return 0;
    }
    else
    {
        /* Child process */
        execvp(args[0], args);
        printf("%s: %s\n", args[0], strerror(errno));
        exit(0);
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
                exit(0);
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
    loop();
    return 0;
}
