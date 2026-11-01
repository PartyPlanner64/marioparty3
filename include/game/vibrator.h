#ifndef _GAME_VIBRATOR_H
#define _GAME_VIBRATOR_H

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

void RetraceCallbackVibrator(void);
void InitVibrator(void);
void ResetVibrator(s16 contId);
void _StartVibrator(s16 *contId);
void StartVibrator(s16 contId);
void _StopVibrator(s16 *contId);
void StopVibrator(s16 contId);
void _RepeatVibrator(VibratorSetting *setting);

#endif
