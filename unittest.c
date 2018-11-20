#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

void test_arg_parser()
{
    int i;
    char args[] = "TEST OF ARG    PARSER";
    char **s = parse_args(args);
    for (i = 0; s[i]; i++)
    {
        printf("%s\n", s[i]);
    }
    char args2[] = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21";
    free(s);
    s = parse_args(args2);
    if (s)
    {
        printf("This should not print!");
    }
}

int main()
{
    test_arg_parser();
    return 0;
}
