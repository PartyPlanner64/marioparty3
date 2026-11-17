#include "humath.h"

void HuMtxCatF(const HuMtx4F a, const HuMtx4F b, HuMtx4F result) {
    HuMtx4F temp;
    s32 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            temp[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j];
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            result[i][j] = temp[i][j];
        }
    }
}

void HuMtxCat(Mtx *a, Mtx *b, Mtx *result) {
    HuMtx4F tempA, tempB;

    HuMtxL2F(tempA, a);
    HuMtxL2F(tempB, b);
    HuMtxCatF(tempA, tempB, tempA);
    HuMtxF2L(tempA, result);
}

// Multiply by an affine matrix, preserving the fourth column.
void HuMtxCatAffineF(const HuMtx4F a, const HuMtx4F b, HuMtx4F result) {
    HuMtx4F temp;
    s32 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            temp[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j];
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = temp[i][j];
        }
        result[i][3] = a[i][3];
    }
}

void HuMtxCatAffine(Mtx *a, const Mtx *b, Mtx *result) {
    HuMtx4F tempA, tempB;
    s32 i, j;
    const u16 *row;

    HuMtxL2F(tempA, a);
    row = (const u16 *)b->m;
    for (i = 0; i < 4; row += 4, i++) {
        for (j = 0; j < 3; j++) {
            tempB[i][j] = (s32)(((u32)row[j] << 16) | row[j + 16]) * (1.0f / 65536.0f);
        }
    }
    HuMtxCatAffineF(tempA, tempB, tempA);
    HuMtxF2L(tempA, result);
}

// Multiply by the upper-left 3x3 matrix, preserving the fourth column.
void HuMtxCatRotF(const HuMtx4F a, const HuMtx4F b, HuMtx4F result) {
    HuMtx4F temp;
    s32 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            temp[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j];
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = temp[i][j];
        }
        result[i][3] = a[i][3];
    }
}

void HuMtxCatRot(Mtx *a, const Mtx *b, Mtx *result) {
    HuMtx4F tempA, tempB;
    s32 i, j;
    const u16 *row;

    HuMtxL2F(tempA, a);
    row = (const u16 *)b->m;
    for (i = 0; i < 3; row += 4, i++) {
        for (j = 0; j < 3; j++) {
            tempB[i][j] = (s32)(((u32)row[j] << 16) | row[j + 16]) * (1.0f / 65536.0f);
        }
    }
    HuMtxCatRotF(tempA, tempB, tempA);
    HuMtxF2L(tempA, result);
}

// Multiply by a translation-only matrix.
void HuMtxCatTransF(const HuMtx4F a, const HuMtx4F b, HuMtx4F result) {
    HuMtx4F temp;
    s32 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            temp[i][j] = a[i][j] + a[i][3] * b[3][j];
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = temp[i][j];
        }
        result[i][3] = a[i][3];
    }
}

void HuMtxCatTrans(Mtx *a, Mtx *b, Mtx *result) {
    HuMtx4F tempA, tempB;
    u16 (*integer)[4] = (u16 (*)[4])b->m;
    u16 (*fraction)[4] = (u16 (*)[4])&b->m[2];

    HuMtxL2F(tempA, a);
    tempB[3][0] = (s32)(((u32)integer[3][0] << 16) | fraction[3][0]) * (1.0f / 65536.0f);
    tempB[3][1] = (s32)(((u32)integer[3][1] << 16) | fraction[3][1]) * (1.0f / 65536.0f);
    tempB[3][2] = (s32)(((u32)integer[3][2] << 16) | fraction[3][2]) * (1.0f / 65536.0f);
    HuMtxCatTransF(tempA, tempB, tempA);
    HuMtxF2L(tempA, result);
}
