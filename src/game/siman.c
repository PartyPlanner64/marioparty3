#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/process.h"
#include "game/siman.h"
#include "macros.h"

static OSMesg siMesgBuf[32];
static OSMesg siReqMesgBuf[32];
static OSThread siThread;
static u64 sSIThreadStack[0x800 / sizeof(u64)];
static functionListEntry *siRetraceClientList;
static functionListEntry *siPreNMIClientList;

void InitSI(void) {
    siRetraceClientList = NULL;
    siPreNMIClientList = NULL;
    osCreateMesgQueue(&siMesgQueue, siMesgBuf, ARRAY_COUNT(siMesgBuf));
    osSetEventMesg(OS_EVENT_SI, &siMesgQueue, (OSMesg)32);
    osCreateMesgQueue(&siReqQueue, siReqMesgBuf, ARRAY_COUNT(siReqMesgBuf));
    osCreateThread(&siThread, 0x14, SIProc, NULL, &sSIThreadStack[ARRAY_COUNT(sSIThreadStack)], HOS_PRIORITY_SIMGR);
    osStartThread(&siThread);
}

functionListEntry **GetSIClientListTable(functionListEntry *entry) {
    switch (entry->type) {
        case 0:
            return &siRetraceClientList;
        case 1:
            return &siPreNMIClientList;
        default:
            return NULL;
    }
}

/* Function Linked List Insertion */
s32 _AddSIClient(functionListEntry *node) {
    functionListEntry *pYoungest;
    functionListEntry *child;

    // Add node as youngest child of a linked list
    pYoungest = (functionListEntry *)GetSIClientListTable(node);
    child = pYoungest->child;
    if (child != NULL) {
        pYoungest = child;
        if (pYoungest->child != NULL) {
            do {
                pYoungest = pYoungest->child;
            } while (pYoungest->child != NULL);
        }
    }
    pYoungest->child = node;
    node->child = NULL;
    return 0;
}

void AddSIClient(functionListEntry *entry, s16 type, void *func) {
    OSMesg msgBuffer;
    OSMesgQueue mq;
    unkMesg msgOut;

    msgOut.func = (HuSiFunc)&_AddSIClient;
    msgOut.arg = entry;
    msgOut.recvQueue = &mq;
    entry->func = func;
    entry->type = type;

    osCreateMesgQueue(&mq, &msgBuffer, OS_MESG_BLOCK);
    osSendMesg(&siReqQueue, &msgOut, OS_MESG_BLOCK);
    osRecvMesg(&mq, NULL, 1);
}

/* Function Linked List Deletion */
s32 _RemoveSIClient(functionListEntry *arg0) {
    functionListEntry *var_v0;
    functionListEntry *var_v1;
    functionListEntry **root;

    root = GetSIClientListTable(arg0);
    var_v0 = *root;
    var_v1 = NULL;
    // Search until the end of the list
    while (var_v0 != NULL) {
        // Check if the node is the one we're looking for
        if (var_v0 == arg0) {
            // If this wasn't at the start of the list (previous node is nonnull), remove it from the list
            if (var_v1 != NULL) {
                var_v1->child = arg0->child;
            } else {
                // Otherwise set the root of the list to the next node
                *root = arg0->child;
            }
            return 0;
        }
        var_v1 = var_v0;
        var_v0 = var_v0->child;
    }
    return 0;
}

void RemoveSIClient(void *entry) {
    OSMesg msgBuffer;
    OSMesgQueue mq;
    unkMesg msgOut;

    msgOut.func = (HuSiFunc)&_RemoveSIClient;
    msgOut.arg = entry;
    msgOut.recvQueue = &mq;

    osCreateMesgQueue(&mq, &msgBuffer, 1);
    osSendMesg(&siReqQueue, &msgOut, OS_MESG_BLOCK);
    osRecvMesg(&mq, NULL, OS_MESG_BLOCK);
}

/* Do all functions in functionList of type "type" */
void CallSIClient(s16 type) {
    functionListEntry *funcList;

    funcList = NULL;
    switch (type) {
        case 0:
            funcList = siRetraceClientList;
            break;
        case 1:
            funcList = siPreNMIClientList;
            break;
    }
    if (funcList != NULL) {
        do {
            funcList->func();
            funcList = funcList->child;
        } while (funcList != 0);
    }
}

/* Wait for message to do all functions in a global function list
 * or to run custom functions?
 */
void SIProc(void *arg0) {
    unkMesgWrapper msgWrapper;

    AddSchedulerClient(&msgWrapper.client, &siReqQueue, 3);

    while (TRUE) {
        osRecvMesg(&siReqQueue, (OSMesg *)&msgWrapper.unkMsg, OS_MESG_BLOCK);
        switch ((s32)msgWrapper.unkMsg) {
            case 1:
                CallSIClient((s16)0);
                break;
            case 2:
                CallSIClient((s16)1);
                break;
            default: {
                unkMesg *recvdMsg;
                recvdMsg = msgWrapper.unkMsg;
                recvdMsg->ret = recvdMsg->func(recvdMsg->arg);
                if (recvdMsg->recvQueue != NULL) {
                    osSendMesg(recvdMsg->recvQueue, NULL, OS_MESG_BLOCK);
                }
            }
        }
    }
}

s32 RequestSIFunction(unkMesg *siMessg, void *func, void *arg, s32 type) {
    OSMesgQueue msgQueue;
    OSMesg tmpMsg;

    siMessg->func = func;
    siMessg->arg = arg;
    siMessg->recvQueue = &msgQueue;
    osCreateMesgQueue(&msgQueue, &tmpMsg, 1);
    osSendMesg(&siReqQueue, siMessg, OS_MESG_BLOCK);
    switch (type) {
        case 0:
            siMessg->ret = 0;
            break;
        case 1:
            osRecvMesg(&msgQueue, NULL, OS_MESG_BLOCK);
            break;
        case 2:
            while (osRecvMesg(&msgQueue, NULL, OS_MESG_NOBLOCK)) {
                HuPrcVSleep();
            }
            break;
    }
    return siMessg->ret;
}
