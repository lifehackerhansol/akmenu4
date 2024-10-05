/*
    testcases.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <fat.h>
#include <nds.h>
#include <string.h>
#include <sys/iosupport.h>
#include <unistd.h>

#include "dbgtool.h"
#include "inifile.h"
#include "savemngr.h"
#include "testcases.h"
#include "unicode.h"

#ifdef DEBUG

void testIni() {
    CIniFile ini;
    ini.LoadIniFile("fat:/moonshl/moonshl.ini");
    int bright = ini.GetInt("System", "NDSLiteDefaultBrightness", 0);
    int WhenStandby = ini.GetInt("BacklightTimeout", "WhenStandby", 0);
    int WhenPicture = ini.GetInt("BacklightTimeout", "WhenPicture", 0);
    int WhenText = ini.GetInt("BacklightTimeout", "WhenText", 0);
    int WhenSound = ini.GetInt("BacklightTimeout", "WhenSound", 0);
    std::string FormatDate = ini.GetString("ClockPlugin", "FormatDate", "");

    dbg_printf(
            "bright %d\nWhenStandby %d\nWhenPicture %d\nWhenText %d\nWhenSound %d\nFormatDate %s\n",
            bright, WhenStandby, WhenPicture, WhenText, WhenSound, FormatDate.c_str());
}

void testSpinBox() {
    //_testSpinBox = new cSpinBox( 0, 0, 64, 18, this, "" );
    //_testSpinBox->loadAppearance( "", "" );
    //_testSpinBox->setSize( cSize(64, 18) );
    //_testSpinBox->setTextColor( RGB15(31,31,31) );
    //_testSpinBox->setRelativePosition( cPoint(100,0) );
    //_testSpinBox->insertItem( "parm1", 0 );
    //_testSpinBox->insertItem( "parm2", 1 );
    //_testSpinBox->insertItem( "parm3", 2 );
    //_testSpinBox->insertItem( "parm4", 3 );
    //_testSpinBox->selectItem( 0 );
    // addChildWindow( _testSpinBox );

    // if( NULL == _renderDesc )
    //     _renderDesc = new cBitmapDesc();
}

void testSettingWnd() {
    //_values.clear();
    //_values.push_back( "YES" );
    //_values.push_back( "NO" );
    // settingWnd.addSettingItem( "active zoom file icon", _values, 4 );

    //_values.clear();
    //_values.push_back( "YES" );
    //_values.push_back( "NO" );
    //_values.push_back( "$1000000" );
    // settingWnd.addSettingItem( "gimme all your money?", _values, 2 );
}

void testUnicode() {
    /*
    u16 uniString[2];
    uniString[0] = 0xfb30;
    uniString[1] = 0;
    std::string localString = unicode_to_local_string( uniString, 1, NULL );

    dbg_printf( "%s", localString.c_str() );
    */
}

void testCopy() {
#define CONTINUOUS_COPY_SIZE 16384
    static ALIGN(4) u8 copyBuffer[CONTINUOUS_COPY_SIZE];

    struct stat srcSt;
    if (0 != stat("fat:/1Mdummy.nds", &srcSt)) {
        printf("copy file error\n");
        return;
    }
    FILE* rf = fopen("fat:/1Mdummy.nds", "rb");
    FILE* wf = fopen("fat:/__rpg/1Mdummy.nds", "wb");

    u32 writeCount = srcSt.st_size / CONTINUOUS_COPY_SIZE;
    if (srcSt.st_size & (CONTINUOUS_COPY_SIZE - 1)) writeCount++;

    u8 percent = 0;
    u32 total = 0;
    for (size_t i = 0; i < writeCount; ++i) {
        if (!(percent & 3)) {
            printf("%d%s", percent, "%");
        }

        u32 readed = fread(copyBuffer, 1, CONTINUOUS_COPY_SIZE, rf);
        u32 written = fwrite(copyBuffer, 1, (int)readed, wf);
        if (written != readed) {
            // printf("err %d\n", errno );
            printf("COPY FILE ERROR! %d/%d\n", readed, written);
            // judge error types in errno
            fclose(rf);
            fclose(wf);
            return;
        }
        total += written;
        percent = total * 100 / srcSt.st_size;
    }
    fclose(rf);
    fclose(wf);
    return;
}

void testWrite() {
#define CONTINUOUS_COPY_SIZE 16384
    static ALIGN(4) u8 copyBuffer[CONTINUOUS_COPY_SIZE];

    FILE* wf = fopen("fat:/__rpg/1mdummy2.bin", "wb");

    u32 writeCount = 1024 * 1024 / CONTINUOUS_COPY_SIZE;

    u8 percent = 0;
    u32 total = 0;
    for (size_t i = 0; i < writeCount; ++i) {
        if (!(percent & 3)) {
            printf("%d%s", percent, "%");
        }
        for (size_t i = 0; i < CONTINUOUS_COPY_SIZE; ++i) {
            copyBuffer[i] = rand() & 0xff;
        }

        u32 written = fwrite(copyBuffer, 1, (int)CONTINUOUS_COPY_SIZE, wf);
        if (written != CONTINUOUS_COPY_SIZE) {
            // printf("err %d\n", errno );
            printf("WRITE FILE ERROR! %d/%d\n", CONTINUOUS_COPY_SIZE, written);
            // judge error types in errno
            fclose(wf);
            return;
        }
        total += written;
        percent = total * 100 / (1024 * 1024);
    }
    fclose(wf);
    return;
}

void testWriteFile() {
    FILE* f = fopen("fat:/testWriteSpeed.bin", "wb");
    // FILE * f = fopen( "fat:/test_nand4.nds", "wb" );
    if (NULL == f) return;
#define SAVEDATA_BUFFER_SIZE (1024 * 1024)
    //#define SAVEDATA_BUFFER_SIZE (116 * 1024)
    u8* saveDataBuffer = new u8[SAVEDATA_BUFFER_SIZE];
    // static ALIGN(4) u8 readNandBuffer[2112];
    memset(saveDataBuffer, 0x5a, SAVEDATA_BUFFER_SIZE);
    // u8 * pSaveDataBuffer = saveDataBuffer;

    u32 written = 0;
    for (u32 i = 0; i < 64; ++i) {
        written = fwrite(saveDataBuffer, 1, SAVEDATA_BUFFER_SIZE, f);
        dbg_printf("%d ", i);
    }
    dbg_printf("64MB WRITE DONE\n");

    fclose(f);
}

void testTextOut() {
    // char msg[32] = {};
    // for( u8 i = 1;i < 16; ++i )
    //{
    //     msg[i-1] = i;
    // }
    // msg[16] = 0xfd;msg[17] = 0xfe;msg[18] = 0xff;msg[19] = 0x1;
    // u32 id = messageBox( NULL, "\x01\x02\x03\x04 blah blah",
    //     msg, MB_OK | MB_CANCEL );// | MB_YES | MB_NO );
    // dbg_printf( "msgbox return %d\n", id );
}

void testLoadWithOutSave() {
    // std::string shortPath = _mainList->getSelectedShortPath();

    // if( shortPath[shortPath.size()-1] == '/' ) {
    //     _mainList->enterDir( shortPath );
    //     return;
    // }

    // DSRomInfo rominfo;
    //_mainList->getRomInfo( _mainList->selectedRowId(), rominfo );

    // if( !rominfo.isDSRom() )
    //     return;

    // std::string fullPath = _mainList->getSelectedFullPath();

    // dbg_printf("(%s)\n", fullPath.c_str() );
    // dbg_printf("%d\n", fullPath[fullPath.size()-1] );

    // saveManager().unlockSave( (SAVE_TYPE)rominfo.saveInfo().saveType, false );

    // loadRom( shortPath );
}

#endif  // DEBUG
