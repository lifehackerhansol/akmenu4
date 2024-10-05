/*
    sprite.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>

enum SPRITE_SIZE {
    SS_SIZE_8 = ATTR1_SIZE_8,
    SS_SIZE_16 = ATTR1_SIZE_16,
    SS_SIZE_32 = ATTR1_SIZE_32,
    SS_SIZE_64 = ATTR1_SIZE_64
};

enum SPRITE_SHAPE {
    SS_SHAPE_SQUARE = ATTR0_SQUARE,
    SS_SHAPE_WIDE = ATTR0_WIDE,
    SS_SHAPE_TALL = ATTR0_TALL
};

class cSprite {
  public:
    cSprite() { init(0); }

    cSprite(u8 id);

    ~cSprite();

    static void sysinit();
    void init(u16 id);
    // void update();
    void setAlpha(u8 alpha);
    void setPosition(u16 x, u8 y);
    void setSize(SPRITE_SIZE size);
    void setShape(SPRITE_SHAPE shape);
    void setBufferOffset(u32 offset);
    void setScale(float scaleX, float scaleY);
    void setRotation(float angle);
    void show();
    void hide();
    bool visible();
    void setPriority(u8 priority);

    u16* buffer();

    // cSprite & operator=( const cSprite & src );

  protected:
    SpriteEntry* _entry;
    SpriteRotation* _affine;
    u8 _id;
    SPRITE_SIZE _size;
    SPRITE_SHAPE _shape;
    u16 _x;
    u8 _y;
    float _scaleX;
    float _scaleY;
    float _rotation;
    u8 _alpha;
    u8 _priority;
    u16 _bufferOffset;
};

// class cSpritePool
//{
// public:
//     cSprite * createSprite( SPRITE_SIZE size, SPRITE_SHAPE shape );
//
//     void destroySprite( cSprite * pointer );
//
// };
