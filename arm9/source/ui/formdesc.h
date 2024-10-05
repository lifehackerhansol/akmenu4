/*
    formdesc.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <string>
#include "bmp15.h"
#include "renderdesc.h"

namespace akui {

class cFormDesc : public cRenderDesc {
  public:
    cFormDesc();

    ~cFormDesc();

  public:
    void draw(const cRect& area, GRAPHICS_ENGINE engine) const;

    void loadData(const std::string& topleftBmpFile, const std::string& toprightBmpFile,
                  const std::string& middleBmpFile);

    void setTitleText(const std::string& text);

  protected:
    cBMP15 _topleft;
    cBMP15 _middle;
    cBMP15 _topright;

    COLOR _bodyColor;
    COLOR _frameColor;

    std::string _titleText;
};

}  // namespace akui
