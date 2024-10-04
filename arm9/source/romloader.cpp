/*
    romloader.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include <limits.h>
#include <nds.h>
#include <fat.h>
#include "romloader.h"
#include "dbgtool.h"
//#include "akloader_arm7_bin.h"
//#include "akloader_arm9_bin.h"
#include "savemngr.h"
#include "../../share/fifotool.h"
#include "timetool.h"
#include "globalsettings.h"

// FIFO_CHANNEL_BITS - number of bits used to specify the channel in a packet - default=4
#define FIFO_CHANNEL_BITS				4
#define FIFO_CHANNEL_SHIFT				(32-FIFO_CHANNEL_BITS)
#define FIFO_IMMEDIATEBIT_SHIFT			(FIFO_CHANNEL_SHIFT-2)
#define FIFO_IMMEDIATEBIT				(1<<FIFO_IMMEDIATEBIT_SHIFT)
#define FIFO_EXTRABIT_SHIFT				(FIFO_CHANNEL_SHIFT-3)
#define FIFO_EXTRABIT					(1<<FIFO_EXTRABIT_SHIFT)
#define FIFO_VALUE32_MASK				(FIFO_EXTRABIT-1)

#define FIFO_PACK_VALUE32(channel, value32) \
	( ((channel)<<FIFO_CHANNEL_SHIFT) | FIFO_IMMEDIATEBIT | \
	(((value32))&FIFO_VALUE32_MASK) )

static void resetAndLoop()
{
    // Interrupt
    REG_IME = 0;
    REG_IE = 0;
    REG_IF = ~0;

    DC_FlushAll();
    DC_InvalidateAll();

    fifoSendValue32(FIFO_USER_01,MENU_MSG_ARM7_REBOOT);
    while(true)
    {
      while(REG_IPC_FIFO_CR&IPC_FIFO_RECV_EMPTY);
      u32 res=REG_IPC_FIFO_RX;
      if(FIFO_PACK_VALUE32(FIFO_USER_01,MENU_MSG_ARM7_READY_BOOT)==res) break;
    }

    swiSoftReset();
}

bool loadRom( const std::string & filename, const std::string & savename, u32 flags, long cheatOffset,size_t cheatSize )
{
    *(u32*)0x23fd900=flags;
    *(u32*)0x23fd904=cheatOffset;
    *(u32*)0x23fd908=cheatSize;
    memset((void*)0x23fda00,0,PATH_MAX*2);
    strcpy((char*)0x23fda00,filename.c_str());
    strcpy((char*)(0x23fda00+PATH_MAX),savename.c_str());

    dbg_printf( "load %s\n", filename.c_str() );

    // copy loader's arm7 code
//    memcpy( (void *)0x023FA000, akloader_arm7_bin, akloader_arm7_bin_size );
    __NDSHeader->arm7executeAddress = (void*)0x023FA000;

    // copy loader's arm9 code
//    memcpy( (void *)0x023c0000, akloader_arm9_bin, akloader_arm9_bin_size );
    __NDSHeader->arm9executeAddress = (void*)0x023c0000;

    dbg_printf( "load done\n" );

    resetAndLoop();
    return true;
}
