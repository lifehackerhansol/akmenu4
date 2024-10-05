/*
    zoomingicon.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>
#include "animation.h"
#include "sprite.h"

class cZoomingIcon : public cAnimation {
  public:
    cZoomingIcon();

    ~cZoomingIcon();

  public:
    void update();

    void show();

    void hide();

    void reset();

    void setScale(float scale);

    void setPosition(u8 x, u8 y);

    void setBufferChanged();

    u16* buffer() { return _buffer; }

  public:
    cSprite _sprite;

    u16 _buffer[32 * 32];
    u16 _x;
    u8 _y;
    float _scale;
    bool _needUpdateBuffer;
};
