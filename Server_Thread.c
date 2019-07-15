#include "server.h"

void *Server_Thread (void *arg)
{
    pid_t Pid;
    pthread_t Tid = pthread_self();
    enum Command Cmd;
    //get args
    struct Args_To_Threads *Args = (struct Args_To_Threads*) arg;
    struct Message Msg;
    memset(Msg.Message, 0, MSG_SIZE);
    //search for our task in Thread queue
    msgrcv(Args->Threads, &Msg, MSG_SIZE, Tid, 0);
    //parse command
    Pid = strtol(strtok(Msg.Message, " "), NULL, 10);
    Cmd = Parse_Command(strtok(NULL, " "));
    //make message to Client
    switch (Cmd)
    {
    case TIME:
        Msg.mtype = Pid;
        sprintf(Msg.Message, "%d\n", time(NULL));
        break;

    case STOP:
        Msg.mtype = Pid;
        strcpy(Msg.Message, "done");
        break;

    default:
        break;
    }
    //write to Clients queue
    msgsnd(Args->Client, &Msg, MSG_SIZE, 0);
    //make message to Threads
    Msg.mtype = Args->Parent;
    memset(Msg.Message, 0, MSG_SIZE);
    if (Cmd != STOP) {
        strcpy(Msg.Message, "done");
    }
    else {
        strcpy(Msg.Message, "stop");
    }
    
    //write to Threads
    msgsnd(Args->Threads, &Msg, MSG_SIZE, 0);
    pthread_exit(0);
}
