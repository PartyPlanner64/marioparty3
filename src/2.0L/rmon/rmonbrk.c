#include "common.h"
#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "rmonint.h"

#define TMP_BP 0
#define NUM_BREAKPOINTS 16
#define FAULT_BREAKNUM (NUM_BREAKPOINTS - 1)

typedef struct {
    u32 *breakAddress;
    u32 oldInstruction;
} BREAKINFO;

/* first breakpoint is reserved for implementing single-stepping */
static BREAKINFO breakpoints[NUM_BREAKPOINTS];
/* breakpoint for alternate branch target */
static BREAKINFO altBreak;
static BREAKINFO RCPbreakpoints[NUM_BREAKPOINTS];

static void SetTempBreakpoint(u32 *addr1, u32 *addr2) {
    /* Save the word at the target address to be restored later */
    breakpoints[TMP_BP].oldInstruction = *addr1;
    /* Install a break instruction at the target address */
    *addr1 = MIPS_BREAK(16);
    osWritebackDCache(addr1, sizeof(*addr1));
    osInvalICache(addr1, sizeof(*addr1));
    breakpoints[TMP_BP].breakAddress = addr1;

    /* Also do so for an alt address if required */
    if (addr2 != NULL) {
        altBreak.oldInstruction = *addr2;
        *addr2 = MIPS_BREAK(16);
        osWritebackDCache(addr2, sizeof(*addr2));
        osInvalICache(addr2, sizeof(*addr2));
        altBreak.breakAddress = addr2;
    }
}

static void ClearTempBreakpoint(void) {
    u32 inst;

    if (breakpoints[TMP_BP].breakAddress != NULL) {
        inst = *breakpoints[TMP_BP].breakAddress;

        if ((inst & MIPS_BREAK_MASK) == MIPS_BREAK_OPCODE) {
            /* After confirming that there is a break instruction with code at the target
                address, restore the original contents of the word at the target address  */
            *breakpoints[TMP_BP].breakAddress = breakpoints[TMP_BP].oldInstruction;
            osWritebackDCache(breakpoints[TMP_BP].breakAddress, sizeof(*breakpoints[TMP_BP].breakAddress));
            osInvalICache(breakpoints[TMP_BP].breakAddress, sizeof(*breakpoints[TMP_BP].breakAddress));
        }
        breakpoints[TMP_BP].breakAddress = NULL;
    }

    /* Same as above for the alt breakpoint */
    if (altBreak.breakAddress != NULL) {
        inst = *altBreak.breakAddress;

        if ((inst & MIPS_BREAK_MASK) == MIPS_BREAK_OPCODE) {
            *altBreak.breakAddress = altBreak.oldInstruction;
            osWritebackDCache(altBreak.breakAddress, sizeof(*altBreak.breakAddress));
            osInvalICache(altBreak.breakAddress, sizeof(*altBreak.breakAddress));
        }
        altBreak.breakAddress = NULL;
    }
}

int __rmonSetBreak(KKHeader *req) {
    KKSetBkptRequest *request = (KKSetBkptRequest *)req;
    BREAKINFO *breakBase;
    BREAKINFO *whichBreak;
    BREAKINFO *lastBreak;
    KKBkptEvent reply;

    /* Select breakpoint list */
    if (req->method == RMON_RSP) {
        breakBase = RCPbreakpoints;
        whichBreak = &RCPbreakpoints[1];
        lastBreak = &RCPbreakpoints[NUM_BREAKPOINTS];
    } else {
        breakBase = breakpoints;
        whichBreak = &breakpoints[1];
        lastBreak = &breakpoints[NUM_BREAKPOINTS];
    }

    /* Find breakpoint slot */
    for (; whichBreak < lastBreak; whichBreak++) {
        if (whichBreak->breakAddress != NULL) {
            if (whichBreak->breakAddress == (u32 *)request->addr) {
                /* Breakpoint already set here */
                break;
            }
            continue;
        } else {
            /* Empty slot */
            break;
        }
    }

    /* No breakpoints available */
    if (whichBreak == lastBreak) {
        return TV_ERROR_NO_MORE_IDS;
    }

    /* Set breakpoint if not already set */
    if (whichBreak->breakAddress == NULL) {
        if (req->method == RMON_RSP) {
            whichBreak->oldInstruction = __rmonReadWordAt((u32 *)request->addr);
            __rmonWriteWordTo((u32 *)request->addr, MIPS_BREAK((whichBreak - breakBase) + NUM_BREAKPOINTS));
        } else {
            whichBreak->oldInstruction = *(u32 *)request->addr;
            *(u32 *)request->addr = MIPS_BREAK((whichBreak - breakBase) + NUM_BREAKPOINTS);
            osWritebackDCache((void *)request->addr, sizeof(whichBreak->oldInstruction));
            osInvalICache((void *)request->addr, sizeof(whichBreak->oldInstruction));
        }
        whichBreak->breakAddress = (u32 *)request->addr;
    }

    /* Send reply */
    reply.header.code = request->header.code;
    reply.header.error = TV_ERROR_NO_ERROR;
    reply.object = request->object;
    reply.bp = whichBreak - breakBase;
    reply.instruction = whichBreak->oldInstruction;
    __rmonSendReply(&reply.header, sizeof(reply), KK_TYPE_REPLY);
    return TV_ERROR_NO_ERROR;
}

int __rmonListBreak(KKHeader *request) {
    return TV_ERROR_ILLEGAL_CALL;
}

int __rmonClearBreak(KKHeader *req) {
    KKClrBkptRequest *request = (KKClrBkptRequest *)req;
    BREAKINFO *whichBreak;
    KKBkptEvent reply;
    u32 inst;

    /* Check valid breakpoint index */
    if (request->bp >= NUM_BREAKPOINTS) {
        return TV_ERROR_INVALID_ID;
    }

    /* Clear the breakpoint, restore whatever was there before */
    if (req->method == RMON_RSP) {
        whichBreak = &RCPbreakpoints[request->bp];

        if (whichBreak->breakAddress == NULL) {
            return TV_ERROR_INVALID_ID;
        }

        inst = __rmonReadWordAt(whichBreak->breakAddress);
        if ((inst & MIPS_BREAK_MASK) == MIPS_BREAK_OPCODE) {
            __rmonWriteWordTo(whichBreak->breakAddress, whichBreak->oldInstruction);
        }
    } else {
        whichBreak = &breakpoints[request->bp];

        if (whichBreak->breakAddress == NULL) {
            return TV_ERROR_INVALID_ID;
        }

        inst = *whichBreak->breakAddress;
        if ((inst & MIPS_BREAK_MASK) == MIPS_BREAK_OPCODE) {
            *whichBreak->breakAddress = whichBreak->oldInstruction;
            osWritebackDCache(whichBreak->breakAddress, sizeof(*whichBreak->breakAddress));
            osInvalICache(whichBreak->breakAddress, sizeof(*whichBreak->breakAddress));
        }
    }
    whichBreak->breakAddress = NULL;

    /* Send reply */
    reply.header.code = request->header.code;
    reply.header.error = TV_ERROR_NO_ERROR;
    reply.object = request->object;
    reply.bp = request->bp;
    __rmonSendReply(&reply.header, sizeof(reply), KK_TYPE_REPLY);
    return TV_ERROR_NO_ERROR;
}

u32 __rmonGetBranchTarget(int method, int thread, char *addr) {
    int inst;

    if (method == RMON_RSP) {
        inst = __rmonReadWordAt((u32 *)addr);
    } else {
        inst = *(u32 *)addr;
    }

    switch ((inst >> 26) & 0x3F) {
        case 0: /* SPECIAL */
            if (((inst >> 5) & 0x7FFF) == 0 && (inst & 0x3F) == 8) {
                /* JR */
                return __rmonGetRegisterContents(method, thread, (inst >> 21) & 0x1F);
            }
            if (((inst >> 16) & 0x1F) == 0 && (inst & 0x7FF) == 9) {
                /* JALR */
                return __rmonGetRegisterContents(method, thread, (inst >> 21) & 0x1F);
            }
            break;
        case 1: /* REGIMM */
            switch ((inst >> 16) & 0x1F) {
                case 0:  /* BLTZ */
                case 1:  /* BGEZ */
                case 2:  /* BLTZL */
                case 3:  /* BGEZL */
                case 16: /* BLTZAL */
                case 17: /* BGEZAL */
                case 18: /* BLTZALL */
                case 19: /* BGEZALL */
                    return (u32)(((inst << 0x10) >> 0xE) + addr + 4);
            }
            break;
        case 2: /* J */
        case 3: /* JAL */
            return (((u32)inst << 6) >> 4) + (((s32)((u32)addr + 4) >> 0x1C) << 0x1C);
        case 4:  /* BEQ */
        case 5:  /* BNE */
        case 20: /* BEQL */
        case 21: /* BNEL */
            return (u32)(((inst << 0x10) >> 0xE) + addr + 4);
        case 6:  /* BLEZ */
        case 7:  /* BGTZ */
        case 22: /* BLEZL */
        case 23: /* BGTZL */
            if (((inst >> 16) & 0x1F) == 0) {
                return (u32)(((inst << 0x10) >> 0xE) + addr + 4);
            }
            break;
        case 16: /* COP0 */
        case 17: /* COP1 */
        case 18: /* COP2 */
        case 19: /* COP3 */
            if (((inst >> 21) & 0x1F) == 8) {
                switch ((inst >> 16) & 0x1F) {
                    case 0: /* BCzF  */
                    case 1: /* BCzT  */
                    case 2: /* BCzFL */
                    case 3: /* BCzTL */
                        return (u32)(((inst << 0x10) >> 0xE) + addr + 4);
                }
            }
            break;
    }
    return -1;
}

static int IsJump(u32 inst) {
    switch ((inst >> 26) & 0x3F) {
        case 0: /* SPECIAL */
            if (((inst >> 5) & 0x7FFF) == 0 && (inst & 0x3F) == 8) {
                /* JR */
                return TRUE;
            }
            if (((inst >> 16) & 0x1F) == 0 && (inst & 0x7FF) == 9) {
                /* JALR */
                return TRUE;
            }
            break;
        case 2: /* J */
        case 3: /* JAL */
            return TRUE;
    }
    return FALSE;
}

int __rmonSetSingleStep(int thread, u32 *instptr) {
    u32 branchTarget = __rmonGetBranchTarget(RMON_CPU, thread, (void *)instptr);

    if ((branchTarget & 3) != 0) {
        /* no branch target, set breakpoint at next pc */
        SetTempBreakpoint(instptr + 1, NULL);
    } else if (branchTarget == (u32)instptr) {
        /* branch target is this instruction, can't single step here */
        return FALSE;
    } else if (IsJump(*instptr) || branchTarget == (u32)(instptr + 2)) {
        /* unconditional branch, set at branch target */
        SetTempBreakpoint((u32 *)branchTarget, NULL);
    } else {
        /* set two breakpoints for handling conditional branches */
        SetTempBreakpoint((u32 *)branchTarget, instptr + 2);
    }
    return TRUE;
}

void __rmonGetExceptionStatus(KKStatusEvent *reply) {
    reply->status.flags = OS_STATE_STOPPED;
    reply->status.why = 2;
    reply->status.what = 0;
    reply->status.rv = 0;
    reply->status.info.major = 2;
    reply->status.info.minor = 4;
    reply->header.code = KK_CODE_THREAD_STATUS;
    reply->header.error = TV_ERROR_NO_ERROR;
    reply->header.length = sizeof(*reply);
}

static void rmonSendBreakMessage(s32 whichThread, int breakNumber) {
    KKStatusEvent reply;

    /* Build thread exception status */
    __rmonGetThreadStatus(RMON_CPU, (whichThread != 0) ? whichThread : RMON_TID_NOTHREAD, &reply);
    __rmonGetExceptionStatus(&reply);

    if (breakNumber == FAULT_BREAKNUM) {
        /* Hit fault */
        reply.status.info.major = 1;
        reply.status.info.minor = 2;
    }
    if (breakNumber < NUM_BREAKPOINTS) {
        breakNumber = 0;
    } else {
        breakNumber -= NUM_BREAKPOINTS;
    }
    if (breakNumber != 0) {
        /* Break not set by debugger, or set during single-step */
        reply.status.instr = MIPS_BREAK_OPCODE;
    }
    __rmonSendReply(&reply.header, sizeof(reply), KK_TYPE_EXCEPTION);
}

void __rmonHitBreak(void) {
    /* Stop all user threads and report faulted threads */
    ClearTempBreakpoint();
    __rmonStopUserThreads(0);
    rmonFindFaultedThreads();
}

void __rmonHitSpBreak(void) {
    KKStatusEvent exceptionReply;

    /* Rewind RSP PC by one instruction to return to the location of the break instruction */
    __rmonWriteWordTo((u32 *)SP_PC_REG, __rmonReadWordAt((u32 *)SP_PC_REG) - 4);

    /* Report RSP break event */
    __rmonGetThreadStatus(RMON_RSP, RMON_TID_RSP, &exceptionReply);
    __rmonGetExceptionStatus(&exceptionReply);
    __rmonSendReply(&exceptionReply.header, sizeof(exceptionReply), KK_TYPE_EXCEPTION);
    __rmonRcpAtBreak = TRUE;
}

void __rmonHitCpuFault(void) {
    /* Stop all user threads and report faulted threads */
    __rmonMaskIdleThreadInts();
    __rmonStopUserThreads(0);
    rmonFindFaultedThreads();
}

void rmonFindFaultedThreads(void) {
    OSThread *tptr = __osGetActiveQueue();

    while (tptr->priority != -1) {
        if (tptr->priority > OS_PRIORITY_IDLE && tptr->priority <= OS_PRIORITY_APPMAX) {
            if (tptr->flags & OS_FLAG_CPU_BREAK) {
                int inst = *(u32 *)tptr->context.pc;

                if ((inst & MIPS_BREAK_MASK) == MIPS_BREAK_OPCODE) {
                    rmonSendBreakMessage(tptr->id, inst >> 6);
                } else {
                    rmonSendBreakMessage(tptr->id, 0);
                }
            }
            if (tptr->flags & OS_FLAG_FAULT) {
                __rmonSendFault(tptr);
                rmonSendBreakMessage(tptr->id, FAULT_BREAKNUM);
            }
        }
        tptr = tptr->tlnext;
    }
}
