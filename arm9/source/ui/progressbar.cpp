/*
    progressbar.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "progressbar.h"

namespace akui {

cProgressBar::cProgressBar(s32 x, s32 y, u32 w, u32 h, cWindow* parent, const std::string& text)
    : cWindow(parent, text) {
    setSize(cSize(w, h));
    setPosition(cPoint(x, y));
}

cProgressBar::~cProgressBar() {}

void cProgressBar::draw() {
    // draw frame

    // draw left

    // draw right

    // draw bar body
    u8 width = _percent * size().x / 100;
    if (_barBmp.valid()) {
        gdi().maskBlt(_barBmp.buffer(), _barBmp.pitch() >> 1, _barBmp.height(), _position.x,
                      _position.y, width, _barBmp.height(), _engine);
    } else {
        u16 color1 = 0xfc00;
        u16 color2 = 0x800f;
        for (u8 i = 0; i < size().y; ++i) {
            if (i & 1)
                gdi().fillRect(color1, color2, position().x, position().y + i, width, 1, _engine);
            else
                gdi().fillRect(color2, color1, position().x, position().y + i, width, 1, _engine);
        }
    }
}

cWindow& cProgressBar::loadAppearance(const std::string& aFileName) {
    _barBmp = createBMP15FromFile(aFileName);
    setSize(cSize(_barBmp.width(), _barBmp.height()));
    return *this;
}

void cProgressBar::setPercent(u8 percent) {
    _percent = percent;
}

}  // namespace akui
