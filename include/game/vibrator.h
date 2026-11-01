#ifndef _VIBRATOR_H_
#define _VIBRATOR_H_

#include "ultra64.h"
#include "game/siman.h"

extern void PRENMICallbackVibrator(void);
extern s32 _InitVibrator(void);

typedef struct {
    s16 stat;
    s16 mode;
    s16 onTime;
    s16 offTime;
    s16 timer;
    s16 duration;
} VibratorState; // 0xC

typedef struct {
    s16 stateIdx;
    s16 onTime;
    s16 offTime;
    s16 duration;
} VibratorSetting;

#define MOTOR_START		1
#define MOTOR_STOP		0
#define	osMotorStart(x)		__osMotorAccess((x), MOTOR_START)
#define	osMotorStop(x)		__osMotorAccess((x), MOTOR_STOP)
extern s32 __osMotorAccess(OSPfs *, s32);

void RepeatVibrator(s16 contId, s16 onTime, s16 offTime, s16 duration);
s32 _ResetVibrator(s16* contId);

#endif