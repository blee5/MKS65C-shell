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
#define P_READ 0
#define P_WRITE 1

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
    char *line;
    while (1)
    {
        if (isatty(STDIN_FILENO))
            print_user_info();
        bufcopy = buf = malloc(MAX_LENGTH);
        fgets(buf, MAX_LENGTH, stdin);
        /* EOF at beginning of line, exit shell */
        if (strlen(buf) == 0) 
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            exit(0);
        }
        /* Check if input fit in buffer */
        if (buf[strlen(buf) - 1] == '\n')
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
            free(buf);
            continue;
        }
        while (line = strsep(&bufcopy, ";"))
        {
            if (strchr(line, '|'))
            {
                pipe_handler(line);
            }
            else
            {
                run_command(line);
            }
        }
        free(buf);
    }
}

void pipe_handler(char *line)
{
    // TODO: Multiple pipes
    char *command = strsep(&line, "|");
    char *next_command = strsep(&line, "|");
    int p[2];
    int stdout_backup = dup(STDOUT_FILENO);
    int stdin_backup = dup(STDIN_FILENO);
    pipe(p);
    if (fork() == 0)
    {
        close(p[P_WRITE]);
        dup2(p[P_READ], STDIN_FILENO);
        wait(NULL);
        run_command(next_command);
        dup2(stdin_backup, STDIN_FILENO);
    }
    else
    {
        close(p[P_READ]);
        dup2(p[P_WRITE], STDOUT_FILENO);
        run_command(command);
        close(STDIN_FILENO);
        exit(0);
    }
}

/*
 * This function is a mess I'm sorry
 */
void run_command(char *command)
{
    int stdout_backup = dup(STDOUT_FILENO);
    int stdin_backup = dup(STDIN_FILENO);
    int stdout_new_fd = stdout_backup;
    int stdin_new_fd = stdin_backup;
    int stdout_mode = O_CREAT | O_WRONLY;
    int i, args_i;

    char *stdout_new = NULL, *stdin_new = NULL;
    char **tokens = parse_args(command);
    char *args[MAX_ARGS];
    if (tokens == NULL)
    {
        printf("bell: Too many arguments, max: %d\n", MAX_ARGS);
        return;
    }
    for (args_i = i = 0; tokens[i]; i++)
    {
        if (strcmp(tokens[i], ">") == 0)
        {
            stdout_new = tokens[++i];
            stdout_mode |= O_TRUNC;
        }
        else if (strcmp(tokens[i], ">>") == 0)
        {
            stdout_new = tokens[++i];
            stdout_mode |= O_APPEND;
        }
        else if (strcmp(tokens[i], "<") == 0)
        {
            stdin_new = tokens[++i];
        }
        else
        {
            args[args_i++] = tokens[i];
        }
    }
    args[args_i] = NULL;
    if (stdout_new)
    {
        stdout_new_fd = open(stdout_new, stdout_mode, 0644);
        if (stdout_new_fd < 0)
        {
            printf("bell: error redirecting stdout: %s: %s\n", stdout_new, strerror(errno));
            free(tokens);
            return;
        }
    }
    else if (stdin_new)
    {
        stdin_new_fd = open(stdin_new, O_RDONLY);
        if (stdin_new_fd < 0)
        {
            printf("bell: error redirecting stdin: %s: %s\n", stdin_new, strerror(errno));
            free(tokens);
            return;
        }
    }
    dup2(stdout_new_fd, STDOUT_FILENO);
    dup2(stdin_new_fd, STDIN_FILENO);
    execute(args);
    dup2(stdout_backup, STDOUT_FILENO);
    dup2(stdin_backup, STDIN_FILENO);
    
    close(stdin_new_fd);
    close(stdout_new_fd);
    free(tokens);
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
        wait(NULL);
        return 0;
    }
    else
    {
        /* Child process */
        signal(SIGINT, SIG_DFL); // Allow child processes to be interrupted
        execvp(args[0], args);
        printf("%s: %s\n", args[0], strerror(errno));
        /* This somehow fixes a weird bug with commands duplicating after an invalid command when reading stdin from a file*/
        fclose(stdin);
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
