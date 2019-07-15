#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define STRLEN 20

enum Command {
    TIME,
    STOP,
    DONE,
    UNKNOWN,
};

enum Command Parse_Command(char *CommandStr);

char *strlwr(char *str);
