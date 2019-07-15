#include "server.h"

void Make_Message (struct Message *MsgIn, struct Message *MsgOut, pid_t *Arg)
{
    strcpy(MsgOut->Message, MsgIn->Message);
    *Arg = strtol(strtok(MsgIn->Message, " "), NULL, 10);
}