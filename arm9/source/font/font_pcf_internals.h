/*
    font_pcf_internals.h
    Copyright (C) 2008-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>

#define PCF_COMPRESSED_METRICS 0x00000100UL

#define PCF_FILE_VERSION (('p' << 24) | ('c' << 16) | ('f' << 8) | 1)

#define PCF_PROPERTIES (1 << 0)
#define PCF_ACCELERATORS (1 << 1)
#define PCF_METRICS (1 << 2)
#define PCF_BITMAPS (1 << 3)
#define PCF_INK_METRICS (1 << 4)
#define PCF_BDF_ENCODINGS (1 << 5)
#define PCF_SWIDTHS (1 << 6)
#define PCF_GLYPH_NAMES (1 << 7)
#define PCF_BDF_ACCELERATORS (1 << 8)

struct SPcfHeader {
    u32 iVersion;
    u32 iCount;
};

struct SPcfEntry {
    u32 iType;
    u32 iFormat;
    u32 iSize;
    u32 iOffset;
};

struct SPcfBitmapsHeader {
    u32 iFormat;
    u32 iCount;
};

struct PACKED SPcfEncodingsHeader {
    u32 iFormat;
    u16 iFirstCol;
    u16 iLastCol;
    u16 iFirstRow;
    u16 iLastRow;
    u16 iDefaultChar;
};

struct SPcfCompressedMetric {
    u8 iLeftSideBearing;
    u8 iRightSideBearing;
    u8 iCharacterWidth;
    u8 iAscent;
    u8 iDescent;
};

struct SPcfAccel {
    u32 iFormat;
    u8 iNoOverlap;
    u8 iConstantMetrics;
    u8 iTerminalFont;
    u8 iConstantWidth;
    u8 iInkInside;
    u8 iInkMetrics;
    u8 iDrawDirection;
    u8 iUnused;
    u32 iFontAscent;
    u32 iFontDescent;
    u32 iMaxOverlap;
};
