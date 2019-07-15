#include <sys/types.h>
#include <malloc.h>

struct Thread_Client {
    pthread_t Thread;
    pid_t Pid;
    struct Thread_Client *Prev;
    struct Thread_Client *Next;
};

void Add_Pair(struct Thread_Client **Head, pthread_t Thread, pid_t Pid);

struct Thread_Client *Del_Pair (struct Thread_Client *To_Delete);
