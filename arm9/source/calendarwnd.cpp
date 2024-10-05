/*
    calendarwnd.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "calendarwnd.h"
#include "bmp15.h"
#include "gdi.h"
#include "globalsettings.h"
#include "systemfilenames.h"

using namespace akui;

cCalendarWnd::cCalendarWnd() : cForm(0, 0, 256, 192, NULL, "calendar window") {}

cCalendarWnd::~cCalendarWnd() {}

void cCalendarWnd::init() {
    setEngine(GE_SUB);
    loadAppearance(SFN_UPPER_SCREEN_BG);
}

cWindow& cCalendarWnd::loadAppearance(const std::string& aFileName) {
    _background = createBMP15FromFile(aFileName);
    return *this;
}

void cCalendarWnd::draw() {
    if (_background.valid()) gdi().bitBlt(_background.buffer(), 0, 0, 256, 192, selectedEngine());
}
