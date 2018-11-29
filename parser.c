#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "bell.h"

/*
 * parser.c
 * 
 * contains functions that handle user input
 */

int MAX_ARGS = 100;
int MAX_LENGTH = 500;

/*
 * Parses a string representing a command
 * Arguments:
 * line: command line input
 *
 * Return value:
 * filename to redirect stdout to
 * NULL if no redirection occurs
 */
char *get_redir(char *line)
{
    char *p = strchr(line, '>');
    if (p)
    {
        while (*p == ' ' || *p == '>')
        {
            *(p++) = 0;
        }
        return p;
    }
    return NULL;
}

/*
 * Parses a string representing a single command separated by space.
 * Will return all the arguments for the command.
 * WILL MODIFY THE STRING!! (Due to strsep being used)
 *
 * Arguments:
 * args: string describing command line input
 *
 * Return Value:
 * An array of strings terminated by a null pointer. 
 * (For execvp purposes)
 *
 * If the number of arguments exceed MAX_ARGS,
 * it will return a null pointer.
 */

char **parse_args(char *args)
{
    char **args_array = malloc(sizeof(char *) * MAX_ARGS + 1); // add 1 for the null at the end
    char *token;
    long i = 0;
    while (token = strsep(&args, " "))
    {
        if (i == MAX_ARGS)
        {
            free(args_array);
            return 0;
        }
        if (strcmp(token, ""))
        {
            args_array[i++] = token;
        }
    }
    args_array[i] = 0;
    return args_array;
}
