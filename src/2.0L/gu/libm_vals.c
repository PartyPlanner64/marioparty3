#include "ultra64.h"

/* Bit pattern of a quiet NaN, read as a float by sinf and cosf. */
const u32 __libm_qnan_f = 0x7F810000;
