#ifndef __PROCESS_H
#define __PROCESS_H

#include "ultra64.h"

typedef struct jump_buf
{
    u32* sp;
    void *func;
    u32 regs[21];
} jmp_buf;

extern s32 setjmp(jmp_buf *jump_buf);
extern s32 longjmp(jmp_buf *jump_buf, s32 val);

#define PROCESS_STAT_PAUSE 0x1

#define HUPRC_EXEC_NORMAL 0
#define HUPRC_EXEC_SLEEP 1
#define HUPRC_EXEC_CHILDWATCH 2
#define HUPRC_EXEC_KILLED 3

typedef void (*process_func)();

typedef struct Process {
/* 0x00 */ struct Process *next;
/* 0x04 */ struct Process *youngest_child;
/* 0x08 */ struct Process *oldest_child;
/* 0x0C */ struct Process *relative;
/* 0x10 */ struct Process *parent_oldest_child;
/* 0x14 */ struct Process *new_process;
/* 0x18 */ void *heap;
/* 0x1C */ u16 exec_mode;
/* 0x1E */ u16 stat;
/* 0x20 */ u16 priority;
/* 0x22 */ s16 dtor_idx;
/* 0x24 */ s32 sleep_time;
/* 0x28 */ void *base_sp;
/* 0x2C */ jmp_buf prc_jump;
/* 0x88 */ process_func destructor;
/* 0x8C */ void *user_data;
} Process;

void HuPrcInit();
Process* HuPrcCreate(process_func func, u16 priority, s32 stack_size, s32 extra_data_size);
void HuPrcChildLink(Process*process, Process*child);
void HuPrcChildUnlink(Process*process);
Process* HuPrcChildCreate(process_func func, u16 priority, s32 stack_size, s32 extra_data_size, Process* parent);
void HuPrcChildWatch();
Process* HuPrcCurrentGet();
s32 HuPrcChildGet(Process*process);
s32 SetKillStatusProcess(Process*process);
s32 HuPrcKill(Process*process);
void HuPrcChildKill(Process*process);
void HuPrcTerminate(Process*process);
void HuPrcEnd();
void HuPrcSleep(s32 time);
void HuPrcVSleep();
void HuPrcWakeup(Process*process);
void HuPrcDestructorSet2(Process*process, process_func destructor);
void HuPrcDestructorSet(process_func destructor);
void* HuPrcMemAlloc(s32 size);
void HuPrcMemFree(void *ptr);

#endif