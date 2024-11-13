/*---------------------------------------------------------------------------------

	default ARM7 core

		Copyright (C) 2005 - 2010
		Michael Noland (joat)
		Jason Rogers (dovoto)
		Dave Murphy (WinterMute)

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any
	damages arising from the use of this software.

	Permission is granted to anyone to use this software for any
	purpose, including commercial applications, and to alter it and
	redistribute it freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you
		must not claim that you wrote the original software. If you use
		this software in a product, an acknowledgment in the product
		documentation would be appreciated but is not required.

	2.	Altered source versions must be plainly marked as such, and
		must not be misrepresented as being the original software.

	3.	This notice may not be removed or altered from any source
		distribution.

---------------------------------------------------------------------------------*/
#include <calico.h>
#include <calico/nds/arm7/pmic.h>
#include <nds.h>
#include <maxmod7.h>
#include "../../share/pxitool.h"

static Thread AK_Thread7;
alignas(8) static u8 AK_Thread7Stack[1024];

static int AK_ThreadMain(void* arg) {
	// Set up PXI mailbox, used to receive PXI command words
	Mailbox AK_ThreadMailbox;
	u32 AK_ThreadMailboxData[8];
	mailboxPrepare(&AK_ThreadMailbox, AK_ThreadMailboxData, sizeof(AK_ThreadMailboxData)/sizeof(u32));
	pxiSetMailbox(PxiChannel_User0, &AK_ThreadMailbox);

	// Main PXI message loop
	for (;;) {
		// Receive a message
		u32 msg = mailboxRecv(&AK_ThreadMailbox) & 0xFF;
		// default to EINVAL in case of invalid commands
		u32 rc = -1;
		switch (msg) {
			case MENU_MSG_BRIGHTNESS_GET: {
                if (g_envExtraInfo->nvram_console_type == EnvConsoleType_DSLite) {
                    rc = pmicReadRegister(PmicReg_BacklightLevel) & PMIC_BL_LEVEL_MASK;
                }

				break;
			}
            case MENU_MSG_BRIGHTNESS_SET0:
            case MENU_MSG_BRIGHTNESS_SET1:
            case MENU_MSG_BRIGHTNESS_SET2:
            case MENU_MSG_BRIGHTNESS_SET3:
            {
                if (g_envExtraInfo->nvram_console_type == EnvConsoleType_DSLite) {
                    u8 data = pmicReadRegister(PmicReg_BacklightLevel);
                    data &= ~PMIC_BL_LEVEL_MASK;
                    data |= PMIC_BL_LEVEL(msg & 3);
                    pmicWriteRegister(PmicReg_BacklightLevel, data);
                    rc = 0;
                }

                break;
            }

			default:
				break;
		}

		// Send a reply back to the ARM9
		pxiReply(PxiChannel_User0, rc);
	}

	return 0;
}

//---------------------------------------------------------------------------------
int main() {
//---------------------------------------------------------------------------------

	// Read settings from NVRAM
	envReadNvramSettings();

	// Set up extended keypad server (X/Y/hinge)
	keypadStartExtServer();

	// Configure and enable VBlank interrupt
	lcdSetIrqMask(DISPSTAT_IE_ALL, DISPSTAT_IE_VBLANK);
	irqEnable(IRQ_VBLANK);

	// Set up RTC
	rtcInit();
	rtcSyncTime();

	// Initialize power management
	pmInit();

	// Set up block device peripherals
	blkInit();

	// Set up touch screen driver
	touchInit();
	touchStartServer(80, MAIN_THREAD_PRIO);

	// Set up server thread
	threadPrepare(&AK_Thread7, AK_ThreadMain, NULL, &AK_Thread7Stack[sizeof(AK_Thread7Stack)], MAIN_THREAD_PRIO);
	threadStart(&AK_Thread7);

	// Keep the ARM7 mostly idle
	while (pmMainLoop()) {
		threadWaitForVBlank();
	}

	return 0;
}
