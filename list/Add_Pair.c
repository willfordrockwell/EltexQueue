#include "list.h"

void Add_Pair(struct Thread_Client **Head, pthread_t Thread, pid_t Pid)
{
    if (*Head == NULL) {
        *Head = (struct Thread_Client *) malloc (sizeof(struct Thread_Client));
        (*Head)->Prev = NULL;
        (*Head)->Next = NULL;
        (*Head)->Thread = Thread;
        (*Head)->Pid = Pid;
    }
    else {
        while ((*Head)->Next != NULL) {
            *Head = (*Head)->Next;
        }
        (*Head)->Next = (struct Thread_Client *) malloc (sizeof(struct Thread_Client));
        (*Head)->Next->Prev = *Head;
        (*Head)->Next->Next = NULL;
        (*Head)->Thread = Thread;
        (*Head)->Pid = Pid;
    }
}