#include "server.h"

int main(int argc, const char **argv) {
    if (argc != 3) {
        fprintf(stderr, "No id for Queue, no command\n");
        exit(EXIT_FAILURE);
    }
    struct Message Msg;
    int idWC = atoi(argv[1]);
    Msg.mtype = 1;
    sprintf(Msg.Message, "%d %s\n", getpid(), argv[2]);
    msgsnd(idWC, &Msg, MSG_SIZE, NULL);
    sleep(1);
    msgrcv(idWC, &Msg, MSG_SIZE, getpid(), NULL);
    printf("Recived from server: %s\n", Msg.Message);
    return 0;
}