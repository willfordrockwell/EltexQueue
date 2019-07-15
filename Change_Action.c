#include "server.h"

void Change_Action (enum Action *Act, int Is_New_Thread, int Is_Stop)
{
    switch (*Act)
    {
    case READ_CLIENT:
        if (Is_New_Thread) {
            *Act = START_THREAD;
        }
        else {
            *Act = WATCH_THREADS;
        }
        break;
    
    case START_THREAD:
        *Act = WATCH_THREADS;
        break;

    case WATCH_THREADS:
        if (!Is_Stop) {
            *Act = READ_CLIENT;
        }
        break;
    }
}