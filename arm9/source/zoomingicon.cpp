/*
    zoomingicon.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "zoomingicon.h"
#include "gdi.h"

cZoomingIcon::cZoomingIcon() {
    _x = 0;
    _y = 0;
    _scale = 1.f;
    _needUpdateBuffer = false;

    _sprite.init(0);
    _sprite.setPriority(1);
    _sprite.setAlpha(15);
    _sprite.show();
}

cZoomingIcon::~cZoomingIcon() {}

void cZoomingIcon::setScale(float scale) {
    _scale = scale;
}

void cZoomingIcon::setPosition(u8 x, u8 y) {
    _x = x;
    _y = y;
}

void cZoomingIcon::setBufferChanged() {
    _needUpdateBuffer = true;
}

void cZoomingIcon::update() {
    static float scaleFactor = 0.015;
    if (_visible) {
        _scale += scaleFactor;
        if (_scale > 1.2 || _scale < 0.9) scaleFactor *= -1;
        _sprite.setScale(_scale, _scale);
        if (!_sprite.visible()) _sprite.show();
    } else {
        _scale = 1.0;
        scaleFactor = 0.015;
        _sprite.setScale(1.f, 1.f);
        if (_sprite.visible()) _sprite.hide();
    }

    _sprite.setScale(_scale, _scale);
    _sprite.setPosition(_x, _y);

    if (_needUpdateBuffer) {
        DC_FlushRange(_buffer, 32 * 32 * 2);
        dmaCopy(_buffer, _sprite.buffer(), 32 * 32 * 2);
        DC_InvalidateRange(_sprite.buffer(), 32 * 32 * 2);
        _needUpdateBuffer = false;
    }
}

void cZoomingIcon::show() {
    if (!_visible) {
        _visible = true;
        gdi().maskBlt(_buffer, _x, _y, 32, 32, GE_MAIN);  // sprite only available on main engine
    }
}

void cZoomingIcon::hide() {
    if (_visible) {
        _visible = false;
        gdi().maskBlt(_buffer, _x, _y, 32, 32, GE_MAIN);  // sprite only available on main engine
    }
}

void cZoomingIcon::reset() {
    _scale = 1.f;
}
