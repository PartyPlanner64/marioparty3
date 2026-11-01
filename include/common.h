#ifndef _COMMON_H_
#define _COMMON_H_

#define IS_DEBUG_PANIC(statement, file, line) do {} while(1)
#define ASSERT(condition) \
    if (!(condition)) { \
        IS_DEBUG_PANIC("Assertion failed: " #condition, __FILE__, __LINE__); \
    }

#define FALSE 0
#define TRUE 1

#include "ultra64.h"
#include "types.h"
#include "humath.h"

#include "game/audio.h"
#include "game/audiomgr.h"
#include "game/board.h"
#include "game/camera.h"
#include "game/camsetup.h"
#include "game/data.h"
#include "game/decode.h"
#include "game/eeprom.h"
#include "game/effect.h"
#include "game/esprite.h"
#include "game/gameman.h"
#include "game/gamemes.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/graphics.h"
#include "game/hmfanim.h"
#include "game/hmfcoll.h"
#include "game/hmfdraw.h"
#include "game/hmflight.h"
#include "game/hmfload.h"
#include "game/hmfparticle.h"
#include "game/hmfshape.h"
#include "game/hmfspr.h"
#include "game/hmfvertex.h"
#include "game/hu3d.h"
#include "game/hvq.h"
#include "game/input.h"
#include "game/lightdebug.h"
#include "game/main.h"
#include "game/malloc.h"
#include "game/mallocblock.h"
#include "game/mapspace.h"
#include "game/messdata.h"
#include "game/mgdata.h"
#include "game/msm.h"
#include "game/nnsched.h"
#include "game/object.h"
#include "game/ovlEvent.h"
#include "game/pad.h"
#include "game/pause.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/profiler.h"
#include "game/rom.h"
#include "game/saveEncode.h"
#include "game/saveload.h"
#include "game/siman.h"
#include "game/sprite.h"
#include "game/texload.h"
#include "game/util.h"
#include "game/vibrator.h"
#include "game/window.h"
#include "game/wipe.h"

#include "common_structs.h"

#include "variables.h"
#include "macros.h"
#include "enums.h"
#include "overlay.h"

#ifndef RECOMP
#include "include_asm.h"
#include "ld_addrs.h"
#endif

#endif
