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
        char *buf;
        buffer_size = 10;
        input_size = 0;
        input_buffer = calloc(1, 10);
        printf("Enter a command: ");
        buf = read_line();
        if (*buf)
        {
            pid = fork();
            if (pid)
            {
                free(buf);
                wait(NULL);
            }
            else
            {
                char **args = parse_args(buf);
                if (args)
                {
                    execvp(args[0], args);
                    printf("Error %d: %s\n", errno, strerror(errno));
                    free(args);
                }
                else
                {
                    printf("Too many arguments.\n");
                }
                return -1;
            }
        }
    }
    return 0;
}
