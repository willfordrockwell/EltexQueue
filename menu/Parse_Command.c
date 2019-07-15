#include "menu.h"

enum Command Parse_Command(char *CommandStr)
{
    const char TimeStr[5] = "time";
    const char DoneStr[5] = "done";
    const char StopStr[5] = "stop";


    CommandStr = strlwr(CommandStr);
    if (strncmp(CommandStr, TimeStr, strlen(TimeStr)) == 0) {
        return TIME;
    }
    if (strncmp(CommandStr, StopStr, strlen(StopStr)) == 0) {
        return STOP;
    }
    if (strncmp(CommandStr, DoneStr, strlen(DoneStr)) == 0) {
        return DONE;
    }
    else {
        return UNKNOWN;
    }
}
