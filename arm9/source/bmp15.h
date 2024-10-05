/*
    bmp15.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>
#include <memory>
#include <string>

class cBMP15 {
    friend cBMP15 createBMP15(u32 width, u32 height);
    friend cBMP15 createBMP15FromFile(const std::string& filename);
    friend cBMP15 createBMP15FromMem(void* mem);
    // friend void destroyBMP15( cBMP15 * bmp );

  public:
    explicit cBMP15();
    explicit cBMP15(u32 width, u32 height);
    ~cBMP15();

  public:
    u32 width() const { return _width; }  // width is memory bitmap's width

    u32 height() const { return _height; }  // height is memory bitmap's height

    u32 pitch() const { return _pitch; }  // pitch returns bytes per line

    u32* buffer() { return _buffer; }

    const u32* buffer() const { return _buffer; }

    bool valid() const { return NULL != _buffer; }

  protected:
    u32 _width;

    u32 _height;

    u32 _pitch;

    u32* _buffer;  // 按 32 位地址对齐，可以在 bitblt 的时候加快速度
};

cBMP15 createBMP15(u32 width, u32 height);
cBMP15 createBMP15FromFile(const std::string& filename);
cBMP15 createBMP15FromMem(void* mem);
// void destroyBMP15( cBMP15 * bmp );
// void destroyBMP15ByFilename( const char * filename );
