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
#define YELLOW "\x1B[33m"
#define WHITE "\x1B[37m"

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
        signal(SIGINT, SIG_DFL);
        execvp(args[0], args);
        printf("%s: %s\n", args[0], strerror(errno));
        exit(-1);
    }
}

void print_user_info()
{
    char cwd[256];
    char usr[256];
    char hostname[256];
    getcwd(cwd, 256);
    getlogin_r(usr, 256);
    gethostname(hostname, 256);
    printf(GREEN BOLD "%s@%s" WHITE":" YELLOW "%s" WHITE REGULAR " >> ", usr, hostname, cwd);
    fflush(stdout);
}

void loop()
{
    char *buf;
    char *token;
    char **args;
    while (1)
    {
        print_user_info();
        buf = read_line();
        if (buf == NULL)
        {
            printf("bell: Input too long, max: %d\n", MAX_LENGTH);
        }
        else
        {
            while (token = strsep(&buf, ";"))
            {
                args = parse_args(token);
                if (args)
                {
                    execute(args);
                    free(args);
                }
                else
                {
                    printf("bell: Too many arguments, max: %d\n", MAX_ARGS);
                }
            }
            free(buf);
        }
    }
}

int main()
{
    signal(SIGINT, SIG_IGN);
    loop();
    return 0;
}
