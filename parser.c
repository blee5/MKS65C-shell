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

/*
 * These limits set low on purpose
 */
const int MAX_ARGS = 10;
const int MAX_LENGTH = 50;

/*
 * Read user input from stdin.
 *
 * Return Value:
 * A string containing user input, excluding the newline character.
 *
 * Error:
 * If the input is longer than MAX_LENGTH, a null pointer is returned.
 */

char *read_line()
{
    char *buffer = malloc(MAX_LENGTH);
    fgets(buffer, MAX_LENGTH, stdin);
    if (buffer[strlen(buffer) - 1] == '\n')
    {
        /* Remove newline */
        buffer[strlen(buffer) - 1] = 0;
        return buffer;
    }
    free(buffer);
    /* Discard rest of stdin buffer */
    int c;
    do
    {
        c = getchar();
    }
    while (c != '\n');
    return 0;
}

/*
 * Parses a string representing a single command,
 * separated by space. WILL MODIFY THE STRING!!
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
