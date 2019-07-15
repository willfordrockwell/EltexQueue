#include "list.h"

struct Thread_Client *Del_Pair (struct Thread_Client *To_Delete)
{
    struct Thread_Client *Pointer;
    //only head
    if (To_Delete->Prev == NULL && To_Delete->Next == NULL) {
        free(To_Delete);
        return NULL;
    }
    //head
    if (To_Delete->Prev == NULL && To_Delete->Next != NULL) {
        To_Delete->Next->Prev = NULL;
        Pointer = To_Delete->Next;
        free (To_Delete);
        return Pointer;
    }
    //in center
    if (To_Delete->Prev != NULL && To_Delete->Next != NULL) {
        To_Delete->Prev->Next = To_Delete->Next;
        To_Delete->Next->Prev = To_Delete->Prev;
        Pointer = To_Delete->Next;
        free(To_Delete);
        return Pointer;
    }
    //end
    if (To_Delete->Prev != NULL && To_Delete->Next == NULL) {
        To_Delete->Prev->Next = NULL;
        Pointer = To_Delete->Prev;
        free(To_Delete);
        return Pointer;
    }
    
}