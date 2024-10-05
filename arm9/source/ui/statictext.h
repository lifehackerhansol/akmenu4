/*
    statictext.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "bmp15.h"
#include "window.h"

namespace akui {

class cStaticText : public cWindow {
  public:
    cStaticText(s32 x, s32 y, u32 w, u32 h, cWindow* parent, const std::string& text);

    ~cStaticText();

  public:
    void draw();

    cWindow& loadAppearance(const std::string& aFileName);

    void setTextColor(COLOR color);

  protected:
    COLOR _textColor;
};

}  // namespace akui
