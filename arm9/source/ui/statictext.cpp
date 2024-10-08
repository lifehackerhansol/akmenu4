/*
    statictext.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "statictext.h"
#include "ui.h"
//#include "gdi.h"

namespace akui {

cStaticText::cStaticText(s32 x, s32 y, u32 w, u32 h, cWindow* parent, const std::string& text)
    : cWindow(parent, text) {
    _position.x = x;
    _position.y = y;
    _size.x = w;
    _size.y = h;
    _textColor = uiSettings().formTextColor;  //(RGB15(31,31,31))
}

cStaticText::~cStaticText() {}

void cStaticText::draw() {
    gdi().setPenColor(_textColor, _engine);
    gdi().textOutRect(_position.x, _position.y, _size.x, _size.y, _text.c_str(), selectedEngine());
}

cWindow& cStaticText::loadAppearance(const std::string& aFileName) {
    return *this;
}

void cStaticText::setTextColor(COLOR color) {
    _textColor = color;
}

}  // namespace akui
