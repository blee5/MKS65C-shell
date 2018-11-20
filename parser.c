#include <string.h>
#include <stdlib.h>
#include "parser.h"

/*
 * parser.c
 * 
 * contains functions that handle user input
 */

const int MAX_ARGS = 20;

/*
 * Parses a string representing a command line input
 * separated by space. WILL MODIFY THE STRING!!
 *
 * Arguments:
 * @args: string describing command line input
 *
 * Return Value:
 * An array of strings terminated by a null pointer.
 *
 * Error:
 * If the number of arguments exceed MAX_ARGS,
 * it will return a null pointer.
 */
char **parse_args(char *args)
{
    char **args_array = malloc(sizeof(char *) * (MAX_ARGS + 1));
    char *token;
    int i = 0;
    while (token = strsep(&args, " "))
    {
        if (i == MAX_ARGS) // too many args
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
