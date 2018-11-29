#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "bell.h"

#define BOLD "\e[1m"
#define REGULAR "\e[0m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define WHITE "\x1B[37m"

int main()
{
    signal(SIGINT, SIG_IGN);
    loop();
    return -1;
}

void loop()
{
    char *buf;
    char *bufcopy;
    char *token;
    char **args;
    while (1)
    {
        if (isatty(STDIN_FILENO))
        {
            print_user_info();
        }
        bufcopy = buf = malloc(MAX_LENGTH);
        fgets(buf, MAX_LENGTH, stdin);
        /* EOF at beginning of line, exit shell */
        if (strlen(buf) == 0) 
        {
            printf("\n");
            exit(0);
        }
        /* Check if input fit in buffer */
        else if (buf[strlen(buf) - 1] == '\n')
        {
            /* Remove newline */
            buf[strlen(buf) - 1] = 0;
        }
        else
        {
            /* Input didn't fit into buffer, discard rest of stdin so it's not read later */
            printf("bell: Input too long, max: %d\n", MAX_LENGTH);
            int c;
            do
                c = getchar();
            while (c != '\n' && c != EOF);
            continue;
        }
        while (token = strsep(&bufcopy, ";"))
        {
            char *redir_target = get_redir(token);
            args = parse_args(token);
            if (args == NULL)
            {
                printf("bell: Too many arguments, max: %d\n", MAX_ARGS);
                continue;
            }
            if (redir_target)
            {
                int stdout_backup = dup(STDOUT_FILENO);
                int fd = open(redir_target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd > 0)
                {
                    dup2(fd, STDOUT_FILENO);
                    execute(args);
                    dup2(stdout_backup, STDOUT_FILENO);
                }
                else
                {
                    printf("bell: %s: %s\n", redir_target, strerror(errno));
                }
            }
            else
            {
                execute(args);
                free(args);
            }
        }
        free(buf);
    }
}

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
        signal(SIGINT, SIG_DFL); // allow child processes to be interrupted
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


