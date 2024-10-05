/*
    progressbar.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "bmp15.h"
#include "ui.h"

namespace akui {

class cProgressBar : public cWindow {
  public:
    cProgressBar(s32 x, s32 y, u32 w, u32 h, cWindow* parent, const std::string& text);

    ~cProgressBar();

  public:
    void draw();

    cWindow& loadAppearance(const std::string& aFileName);

    void setPercent(u8 percent);

  protected:
    u8 _percent;

    cBMP15 _barBmp;
};

}  // namespace akui
