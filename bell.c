#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parser.h"

int main()
{
    char *input_buffer;
    char *temp_buffer = malloc(2);
    int buffer_size;
    int input_size;
    
    int pid;
    while (1)
    {
        buffer_size = 10;
        input_size = 0;
        input_buffer = calloc(1, 10);
        printf("Enter a command: ");
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
        if (*input_buffer)
        {
            pid = fork();
            if (pid)
            {
                free(input_buffer);
                wait(NULL);
            }
            else
            {
                char **args = parse_args(input_buffer);
                execvp(args[0], args);
                printf("Error %d: %s\n", errno, strerror(errno));
                free(args);
                return -1;
            }
        }
    }
    return 0;
}
