#include "server.h"

int main (int argc, char **argv)
{
    struct Message With_Clients;
    int idWC;

    struct Message To_Threads;
    struct Message From_Threads;
    int idWT;

    struct Args_To_Threads
    *Arg = (struct Args_To_Threads*) malloc (sizeof(struct Args_To_Threads));

    struct Thread_Client *Pairs = NULL;
    pthread_t Tid;
    pid_t Pid;

    int Returns;

    int Stop_Read = 0;
    int Is_New_Thread = 0;
    int Exit = 0;
    enum Action Act = READ_CLIENT;
    enum Command Cmd;

    struct msqid_ds Queue_Conf;

    Arg->Parent = pthread_self();

    if ((Returns = msgget(ftok("./Server.elf", 1), 0660 | IPC_CREAT)) != -1) {
        idWC = Returns;
        printf("Queue %d with Clients was created\n", idWC);
    } else {
        printf("Queue with Clients was NOT created %s\n", strerror(Returns));
        exit(-1);
    }

    Arg->Client = idWC;

    //get info to make readonly permission for clients
    if ((Returns = msgctl(idWC, IPC_STAT, &Queue_Conf)) != -1) {
        printf("Get info about msqid_ds\n");
    }
    else {
        printf("Can NOT get info about msqid_ds error:  %s\n",
               strerror(Returns));
        exit(-1);
    }

    //make readonly permission
    Queue_Conf.msg_perm.mode = 0640;

    if ((Returns = msgget(ftok("./Server.elf", 2), 0600 | IPC_CREAT)) != -1) {
        idWT = Returns;
        printf("Queue %d with Threads was created\n", idWT);
    } else {
        printf("Queue with Threads was NOT created %s\n", strerror(Returns));
        exit(-1);
    }

    Arg->Threads = idWT;

    printf("Server started\n");

    while(!Exit) {
        switch (Act)
        {
        case READ_CLIENT:
            memset(With_Clients.Message, 0, MSG_SIZE);
            memset(To_Threads.Message, 0, MSG_SIZE);
            if (!Stop_Read) {
                //try to get message from Clients and create a thread
                Returns = msgrcv(idWC, &With_Clients, MSG_SIZE, 1, IPC_NOWAIT);
                if (Returns > 0) {
                    Make_Message(&With_Clients, &To_Threads, &Pid);
                    //need new Thread
                    Is_New_Thread = 1;
                }
                //no massage - no new Thread
            }
            //no read - no new Threads
            break;

        case START_THREAD:
            pthread_create(&Tid, NULL, Server_Thread, Arg);
            //write a task for thread
            To_Threads.mtype = Tid;
            msgsnd(idWT, &To_Threads, MSG_SIZE, 0);
            //write to watch
            Add_Pair(&Pairs, Tid, Pid);
            printf("Thread to work with (PID: %d)\n", Pid);
            Is_New_Thread = 0;
            break;

        case WATCH_THREADS:
            //try to join done threads
            while (Pairs != NULL) {
                Returns = msgrcv(idWT, &From_Threads, MSG_SIZE, pthread_self(),
                                 IPC_NOWAIT);
                if (Returns > 0) {
                    Cmd = Parse_Command(From_Threads.Message);
                    switch (Cmd)
                    {
                    case STOP:
                        //stop listening Clients and change theirs permissions
                        Stop_Read = 1;
                        Returns = msgctl(idWC, IPC_SET, &Queue_Conf);
                        if (Returns == 0) {
                            printf("Stop to read from Clients\n");
                        }

                    case DONE:
                        //Thread done its work, join should be non blocking
                        pthread_join(Pairs->Thread, NULL);
                        printf("Thread for PID %d done\n", Pairs->Pid);
                        Pairs = Del_Pair(Pairs);
                        break;

                    default:
                        break;
                    }
                }
                if (Pairs != NULL) {
                    if (Pairs->Next != NULL) {
                        Pairs = Pairs->Next;
                    }
                    else {
                        break;
                    }
                }
            }
            //go to begin
            if (Pairs != NULL) {
                while (Pairs->Prev != NULL) {
                    Pairs = Pairs->Prev;
                }
            }
            if (Pairs == NULL && Stop_Read) {
                Exit = 1;
            }
            break;
        }
        Change_Action(&Act, Is_New_Thread, Stop_Read);
    }
    //end of program
    Returns = msgctl(idWC, IPC_RMID, NULL);
    if (Returns > 0) {
        //error
        exit(EXIT_FAILURE);
    }
    printf("Success removed %d Queue\n", idWC);

    Returns = msgctl(idWT, IPC_RMID, NULL);
    if (Returns > 0) {
        //error
        exit(EXIT_FAILURE);
    }
    printf("Success removed %d Queue\n", idWT);
    free(Arg);
    return 0;
}