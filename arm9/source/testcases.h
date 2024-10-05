/*
    testcases.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

int PrintFreeMem(void);

void testIni();

void testUnicode();

void testCopy();

void testWrite();

void testWriteFile();

void testViolenceEEP4Kauto(u32 count);

void testViolenceEEP512Kauto(u32 count);

void testViolenceEEP8Mauto(u32 count);

void testEEPReadStatus();
