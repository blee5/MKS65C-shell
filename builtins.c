#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bell.h"

char *builtins[] = 
{
    "cd",
    "help",
    "exit",
    0,
};

// why do declaring function pointers look so weird
int (*f_builtins[]) (char **) = 
{
    &bell_cd,
    &bell_help,
    &bell_exit,
};

/*
 * Changes the current working directory of the shell.
 * If unsucessful, will report the error.
 *
 * Arguments:
 * args: An array in the format:
 * {"cd", path, NULL} or {"cd", NULL}.
 * If path does not exist the working directory will be changed to the home directory of the user.
 *
 * Return Value:
 * 0 if succesful
 * -1 if unsuccessful
 */

int bell_cd(char **args)
{ 
    int i;
    for (i = 0; args[i]; i++)
    {
        if (i == 2)
        {
            printf("bell: cd: Too many arguments\n");
            return -1;
        }
    }
    char *path = args[1];
    if (path == NULL)
    {
        path = getenv("HOME");
    }
    if (chdir(path) < 0)
    {
        printf("bell: cd: %s: %s\n", path, strerror(errno));
        return -1;
    }
    return 0;
}

int bell_help(char **args)
{
    int i;
    printf("Commands:\n");
    for (i = 0; builtins[i]; i++)
    {
        printf("%s\n", builtins[i]);
    }

    return 0;
}

int bell_exit(char **args)
{
    return 1;
}
