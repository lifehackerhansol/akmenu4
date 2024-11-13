/*
    main.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <calico.h>
#include <nds.h>
#include <cstdio>
#include <list>
#include <map>
#include <vector>

#include <fat.h>

#include "dbgtool.h"
#include "gdi.h"
#include "ui.h"

#include "mainlist.h"
#include "mainwnd.h"
#include "startmenu.h"
#include "systemfilenames.h"
#include "timer.h"

#include "bigclock.h"
#include "calendar.h"
#include "calendarwnd.h"
#include "datetime.h"

#include "inifile.h"
#include "irqs.h"

#include "diskicon.h"
#include "fontfactory.h"
#include "language.h"
#include "progresswnd.h"

#include "romlauncher.h"
#include "userwnd.h"

using namespace akui;

#ifdef __cplusplus
extern "C" {
#endif
void __libnds_exit(int rc) {}
#ifdef __cplusplus
}
#endif

int main(void) {
    irq().init();

    windowManager();

    // init tick timer/fps counter
    timer().initTimer();

    // init inputs
    initInput();

    // turn led on
    pmSetPowerLed(PmLedMode_Steady);

    // init graphics
    gdi().init();
#ifdef DEBUG
    gdi().switchSubEngineMode();
#endif  // DEBUG
    dbg_printf("gdi ok\n");

    // wait_press_b();
    //  init fat
    bool succ = fatInitDefault();
    if (!succ) dbg_printf("init fat %d\n", succ);

    // wait_press_b();

    // setting scripts
    gs().loadSettings();

    // init unicode
    // if( initUnicode() )
    //    _FAT_unicode_init( unicodeL2UTable, unicodeU2LTable, unicodeAnkTable );
    cwl();

    lang();  // load language file
    gs().language = lang().GetInt("font", "language", gs().language);
    fontFactory().makeFont();  // load font file
    uiSettings().loadSettings();

    bool saveListOK = saveManager().importSaveList(SFN_CUSTOM_SAVELIST, SFN_OFFICIAL_SAVELIST);
    if (!saveListOK) {
        // messageBox( NULL,
        //     LANG("no savelist","title"),
        //     LANG("no savelist", "text"), MB_OK );
        dbg_printf("WARNING: savelist.bin missed\n");
    }

    gdi().initBg(SFN_LOWER_SCREEN_BG);

    cMainWnd* wnd = new cMainWnd(0, 0, 256, 192, NULL, "main window");
    wnd->init();

    progressWnd().init();

    diskIcon().loadAppearance(SFN_CARD_ICON_BLUE);
    diskIcon().show();

    windowManager().update();
    timer().updateFps();

    calendarWnd().init();
    calendarWnd().draw();
    calendar().init();
    calendar().draw();
    bigClock().init();
    bigClock().draw();

    userWindow().draw();

    gdi().present(GE_MAIN);
    gdi().present(GE_SUB);

    dbg_printf("loop start\n");

    irq().vblankStart();

    // enter last directory
    std::string lastDirectory = "...", lastFile = "...";
    if (gs().enterLastDirWhenBoot || gs().autorunWithLastRom) {
        CIniFile f;
        if (f.LoadIniFile(SFN_LAST_SAVEINFO)) {
            lastFile = f.GetString("Save Info", "lastLoaded", "");
            if ("" == lastFile) {
                lastFile = "...";
            } else if (gs().enterLastDirWhenBoot) {
                size_t slashPos = lastFile.find_last_of('/');
                if (lastFile.npos != slashPos) lastDirectory = lastFile.substr(0, slashPos + 1);
            }
        }
    }

    if (gs().autorunWithLastRom && "..." != lastFile) {
        INPUT& inputs = updateInput();
        if (!(inputs.keysHeld & KEY_B)) autoLaunchRom(lastFile);
    }

    dbg_printf("lastDirectory '%s'\n", lastDirectory.c_str());
    if (!wnd->_mainList->enterDir("..." != lastDirectory ? lastDirectory : gs().startupFolder))
        wnd->_mainList->enterDir("...");

    if (*(u32*)0x04000604) goto shutdown;

    while (pmMainLoop()) {
        timer().updateFps();

        INPUT& inputs = updateInput();

        processInput(inputs);

        // swiWaitForVBlank();

        windowManager().update();

        gdi().present(GE_MAIN);
    }

shutdown:
    return 0;
}
