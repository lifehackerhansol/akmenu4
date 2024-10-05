/*
    Copyright (C) 2007 Acekard, www.acekard.com

    SPDX-License-Identifier: MIT
*/

#include <nds.h>

void waitMs(unsigned int requestTime) {
    unsigned int lastLine = REG_VCOUNT;
    unsigned int newLine;
    unsigned int elapsedTime = 0;   // in ms
    unsigned int elapsedLines = 0;  // in lines

    while (elapsedTime < requestTime) {
        int diffLine;
        newLine = REG_VCOUNT;

        diffLine = newLine - lastLine;
        if (diffLine < 0) diffLine = 263 + diffLine;

        elapsedLines += diffLine;

        // does this correctly optimize?
        // elapsedTime = elapsedLines/16; // 16 lines = 1ms
        elapsedTime = elapsedLines >> 4;  // 16 lines = 1ms

        lastLine = newLine;
    }
}
