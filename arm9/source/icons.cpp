/*
    icons.cpp
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "icons.h"

void cIcons::maskBlt(const u16* aSrc, u16* aDst) {
    for (u32 ii = 0; ii < 32; ++ii) {
        for (u32 jj = 0; jj < 16; ++jj) {
            if (((*(u32*)aSrc) & 0x80008000) == 0x80008000) {
                *(u32*)aDst = *(u32*)aSrc;
            } else {
                if (aSrc[0] & 0x8000) aDst[0] = aSrc[0];
                if (aSrc[1] & 0x8000) aDst[1] = aSrc[1];
            }
            aSrc += 2;
            aDst += 2;
        }
    }
}
