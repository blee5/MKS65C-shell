#include <stdio.h>
#include "parser.h"

int main()
{
    char **s = parse_args("hey -a");
    printf("%s\n", s[0]);
    return 0;
}
