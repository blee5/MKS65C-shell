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

/*
 * Execute all commands in the buffer
 */
void execute_commands(char *buf)
{
    int i;
    int n;
    char ***commands = parse_line(buf, &n);
    for (i = 0; i < n; i++)
    {
        if (commands[i] == NULL)
        {
            printf("bell: Too many arguments\n");
        }
        else if (execute(commands[i]) == 1)
        {
            exit(0);
        }
    }
    for (i = 0; i < n; i++)
    {
        if (commands[i])
        {
            free(commands[i]);
        }
    }
    free(commands);
}

void loop()
{
    char *buf;
    while (1)
    {
        print_user_info();
        buf = read_line();
        if (buf == NULL)
        {
            printf("bell: Input too long\n");
        }
        else
        {
            execute_commands(buf);
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
