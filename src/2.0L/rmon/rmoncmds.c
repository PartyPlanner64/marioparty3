#include "common.h"
#include "rmonint.h"

extern FUNPTR D_800A4240_main[]; // dispatchTable

int __rmonExecute(KKHeader *request) {
    int retval;
    KKHeader reply;

    if (request->code >= 53) {
        return TV_ERROR_ILLEGAL_CALL;
    }

    retval = D_800A4240_main[(int)request->code](request);
    if (retval < TV_ERROR_NO_ERROR) {
        reply.code = request->code;
        reply.error = retval;
        __rmonSendReply(&reply, sizeof(reply), KK_TYPE_REPLY);
    }
    return retval;
}

int NotImplemented(KKHeader *dummy) {
    return TV_ERROR_ILLEGAL_CALL;
}
