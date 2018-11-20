#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

/*
 * parser.c
 * 
 * contains functions that handle user input
 */

const int MAX_ARGS = 20;

/*
 * Read user input from stdin, until a newline character is reached.
 *
 * Return Value:
 * A string containing user input, excluding the newline character.
 * TODO:
 * Returns a null pointer if an EOF (Ctrl+D) character is read.
 */
char *read_line()
{
    char *input_buffer;
    char *temp_buffer = malloc(2);
    int buffer_size;
    int input_size;
    
    buffer_size = 10;
    input_size = 0;
    input_buffer = calloc(1, 10);
    while (fgets(temp_buffer, 2, stdin) && strcmp(temp_buffer, "\n"))
    {
        input_size++;
        if (input_size >= buffer_size)
        {
            buffer_size *= 2;
            input_buffer = realloc(input_buffer, buffer_size);
        }
        strcat(input_buffer, temp_buffer);
    }
    return input_buffer;
}

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
