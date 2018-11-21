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

const int MAX_ARGS = 255;

/*
 * Read user input from stdin, until a newline
 *
 * Return Value:
 * A string containing user input, excluding the newline character.
 */
char *read_line()
{
    int buflen = 10;
    char *buffer = malloc(buflen);
    int c;
    int i = 0;
    while (1)
    {
        c = fgetc(stdin);
        if (c != EOF)
        {
            if (c == '\n')
            {
                buffer[i] = 0;
                return buffer;
            }
            buffer[i++] = c;
            if (i >= buflen)
            {
                buflen *= 2;
                buffer = realloc(buffer, buflen);
            }
        }
    }
}

/*
 * Parses a string representing user input,
 * with each command separated by semicolons.
 * 
 * Note that the array may contain null pointers.
 *
 * Arguments:
 * args: string describing command line input
 *
 * Return Value:
 * An array of array of strings, terminated by a null pointer.
 * (Refer to parse_args)
 */
char ***parse_line(char *args)
{
    char ***commands = malloc(sizeof(char *) * 255);
    char *token;
    long i = 0;
    while (token = strsep(&args, ";"))
    {
        commands[i++] = parse_args(token);
    }
    commands[i] = 0;
    return commands;
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
    char **args_array = malloc(sizeof(char *) * MAX_ARGS);
    char *token;
    long i = 0;
    while (token = strsep(&args, " "))
    {
        if (i == MAX_ARGS - 1)
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
