#include <string.h>
#include <stdlib.h>
#include "parser.h"

const int MAX_ARGS = 10;
const int INIT_ARGS_SIZE = 5;

/*
 * Parses a string representing a command line input
 * separated by space.
 *
 * Arguments:
 * @args: string describing command line input,
 *
 * Return Value:
 * An array of strings
 */
char **parse_args(const char *args)
{
    char *argstr = malloc(strlen(args));
    char **args_array = malloc(sizeof(char *) * INIT_ARGS_SIZE);
    int i;
    strcpy(argstr, args);
    while (
    args_array[0] = strsep(&argstr, " ");
    return args_array;
}
