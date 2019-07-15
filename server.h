#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

#include "./menu/menu.h"
#include "./list/list.h"

#define MSG_SIZE 255

struct Message {
    long mtype;
    char Message[MSG_SIZE];
};

struct Args_To_Threads {
    int Client;
    int Threads;
    pthread_t Parent;
};

enum Action {
    READ_CLIENT,
    START_THREAD,
    WATCH_THREADS
};

void Change_Action (enum Action *Act, int Is_New_Thread, int Is_Stop);

void Make_Message (struct Message *MsgIn, struct Message *MsgOut, pid_t *Arg);

void *Server_Thread (void *arg);
