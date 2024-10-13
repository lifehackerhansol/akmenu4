/*
    AcekardLauncher.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin
    Copyright (C) 2024 lifehackerhansol

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <climits>
#include <cstring>
#include <string>

#include <nds.h>

#include "../../../share/fifotool.h"
#include "AcekardLauncher.h"
#include "dbgtool.h"

// 256 UCS-2 characters encoded into UTF-8 can use up to 768 UTF-8 chars
#define MAX_FILENAME_LENGTH 768

// FIFO_CHANNEL_BITS - number of bits used to specify the channel in a packet - default=4
#define FIFO_CHANNEL_BITS 4
#define FIFO_CHANNEL_SHIFT (32 - FIFO_CHANNEL_BITS)
#define FIFO_IMMEDIATEBIT_SHIFT (FIFO_CHANNEL_SHIFT - 2)
#define FIFO_IMMEDIATEBIT (1 << FIFO_IMMEDIATEBIT_SHIFT)
#define FIFO_EXTRABIT_SHIFT (FIFO_CHANNEL_SHIFT - 3)
#define FIFO_EXTRABIT (1 << FIFO_EXTRABIT_SHIFT)
#define FIFO_VALUE32_MASK (FIFO_EXTRABIT - 1)

#define FIFO_PACK_VALUE32(channel, value32) \
    (((channel) << FIFO_CHANNEL_SHIFT) | FIFO_IMMEDIATEBIT | (((value32)) & FIFO_VALUE32_MASK))

static void resetAndLoop() {
    // Interrupt
    REG_IME = 0;
    REG_IE = 0;
    REG_IF = ~0;

    DC_FlushAll();
    DC_InvalidateAll();

    fifoSendValue32(FIFO_USER_01, MENU_MSG_ARM7_REBOOT);
    while (true) {
        while (REG_IPC_FIFO_CR & IPC_FIFO_RECV_EMPTY)
            ;
        u32 res = REG_IPC_FIFO_RX;
        if (FIFO_PACK_VALUE32(FIFO_USER_01, MENU_MSG_ARM7_READY_BOOT) == res) break;
    }

    swiSoftReset();
}

bool AcekardLauncher::launchRom(std::string romPath, std::string savePath, u32 flags,
                                u32 cheatOffset, u32 cheatSize) {
    tNDSHeader header;

    dbg_printf("load %s\n", romPath.c_str());

    // akloaders are very old and expect the old-style libfat mount points
    romPath.replace(0, 3, "fat0");
    savePath.replace(0, 3, "fat0");

    FILE* loader = fopen("fat:/__rpg/akloader.nds", "rb");
    if (loader == NULL) return false;

    fseek(loader, 0, SEEK_SET);
    fread(&header, sizeof(header), 1, loader);

    // copy loader's arm7 code
    fseek(loader, header.arm7romOffset, SEEK_SET);
    fread(header.arm7destination, 4, header.arm7binarySize >> 2, loader);
    __NDSHeader->arm7executeAddress = header.arm7executeAddress;

    // copy loader's arm9 code
    fseek(loader, header.arm9romOffset, SEEK_SET);
    fread(header.arm9destination, 4, header.arm9binarySize >> 2, loader);
    __NDSHeader->arm9executeAddress = header.arm9executeAddress;
    fclose(loader);

    *(u32*)0x23fd900 = flags;
    *(u32*)0x23fd904 = cheatOffset;
    *(u32*)0x23fd908 = cheatSize;
    memset((void*)0x23fda00, 0, MAX_FILENAME_LENGTH * 2);
    strcpy((char*)0x23fda00, romPath.c_str());
    strcpy((char*)(0x23fda00 + MAX_FILENAME_LENGTH), savePath.c_str());

    dbg_printf("load done\n");

    resetAndLoop();
    return true;
}
