#include "common.h"
#include "game/hvq.h"
#include "game/malloc.h"
#include "game/mallocblock.h"


void func_80108AF0_inst(s16 model, void *imageHeader, void *imageData, u8 *alpha) {
    u16 *decoded;
    u8 *work;
    u8(*pixels)[4];
    HmfData *hmf;
    HmfModelData_Unk64_Unk60_Struct *mesh;
    Vtx *vertex;
    Vtx *faceVertices;
    Gfx *gfx;
    s16 width = 128;
    s16 height = 96;
    s16 index;
    s16 face;
    s16 corner;
    s16 node;
    u16 color;
    f32 x;
    f32 y;
    f32 minX, maxX, minY, maxY;
    f32 originX, originY, extentX, extentY;
    s16 left, right, top, bottom;

    hmf = HmfModelData[model].hmf;
    decoded = HuMemMemoryAllocPerm(0x6000);
    hvqMpsInit1(255);
    hvqMpsDecodeStart1(imageHeader);
    work = HuMemMemoryAllocPerm(0xC00);
    hvqMpsDecode1(imageData, decoded, 128, work);
    HuMemMemoryFreePerm(work);
    pixels = HuMemAllocTag(0xC000, hmf->unk0E);
    alpha += (alpha[10] << 16) + alpha[11];
    for (y = 0, face = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            color = decoded[face];
            pixels[face][0] = (color >> 8) & 0xF8;
            pixels[face][1] = (color >> 3) & 0xF8;
            pixels[face][2] = (color << 2) & 0xF8;
            pixels[face][3] = alpha[face];
            face++;
        }
    }
    HuMemMemoryFreePerm(decoded);
    node = func_8002C834_main(hmf, "gamen");
    mesh = &hmf->unk60[node];
    vertex = HuMemAllocTag(0x640, hmf->unk0E);
    ((Gfx **)hmf->unk3C)[node] = gfx = HuMemAllocTag(0x2000, hmf->unk0E);
    mesh->unk50 |= 0x10000;
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
    gSPClearGeometryMode(gfx++, G_LIGHTING);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    maxY = maxX = -100000.0f;
    minY = minX = 100000.0f;
    for (face = 0; face < mesh->unk22; face++) {
        for (corner = 0; corner < mesh->unk54[face].unk00; corner++) {
            index = mesh->unk54[face].unk04[corner];
            if (hmf->unk50[index][0] < minX) {
                minX = hmf->unk50[index][0];
            }
            if (maxX < hmf->unk50[index][0]) {
                maxX = hmf->unk50[index][0];
            }
            if (hmf->unk50[index][1] < minY) {
                minY = hmf->unk50[index][1];
            }
            if (maxY < hmf->unk50[index][1]) {
                maxY = hmf->unk50[index][1];
            }
        }
    }
    extentX = maxX - minX;
    extentY = maxY - minY;
    originX = minX;
    originY = minY;
    for (face = 0; face < mesh->unk22; face++) {
        faceVertices = vertex;
        maxY = maxX = -100000.0f;
        minY = minX = 100000.0f;
        for (corner = 0; corner < mesh->unk54[face].unk00; corner++) {
            index = mesh->unk54[face].unk04[corner];
            x = vertex->v.ob[0] = hmf->unk50[index][0];
            y = vertex->v.ob[1] = hmf->unk50[index][1];
            vertex->v.ob[2] = hmf->unk50[index][2];
            if (x < minX) {
                minX = x;
            }
            if (maxX < x) {
                maxX = x;
            }
            if (y < minY) {
                minY = y;
            }
            if (maxY < y) {
                maxY = y;
            }
            vertex->n.n[0] = vertex->n.n[1] = vertex->n.n[2] = -1;
            x = width - width * ((-x - originX) / extentX);
            y = height * ((-y - originY) / extentY);
            vertex->v.tc[0] = x * 32.0f;
            vertex->v.tc[1] = y * 32.0f;
            vertex->v.cn[3] = 255;
            vertex++;
        }
        minX = ((minX - originX) / extentX) * width;
        maxX = ((maxX - originX) / extentX) * width;
        minY = height - ((minY - originY) / extentY) * height;
        if (minY == height) {
            minY = height - 0.1f;
        }
        maxY = height - ((maxY - originY) / extentY) * height;
        top = maxY;
        bottom = minY;
        right = maxX;
        left = minX;
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPLoadTextureTile(gfx++, pixels, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height,
                           left, top, right, bottom, 0,
                           G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                           G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(gfx++, faceVertices, mesh->unk54[face].unk00, 0);
        if (mesh->unk54[face].unk00 == 3) {
            gSP1Triangle(gfx++, 0, 1, 2, 0);
        } else {
            gSP1Quadrangle(gfx++, 0, 1, 2, 3, 0);
        }
    }
    gSPEndDisplayList(gfx++);
}
