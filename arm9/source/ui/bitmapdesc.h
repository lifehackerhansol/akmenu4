/*
    bitmapdesc.h
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

// bitmap desc，只负责画背景
enum BLTMODE { BM_BITBLT, BM_MASKBLT };

class cBitmapDesc : public cRenderDesc {
  public:
    cBitmapDesc();

    ~cBitmapDesc();

  public:
    void setBltMode(BLTMODE bltmode) { _bltmode = bltmode; }

    void draw(const cRect& area, GRAPHICS_ENGINE engine) const;

    void loadData(const std::string& filename);

    cSize size();

  protected:
    cBMP15 _background;

    BLTMODE _bltmode;
};

}  // namespace akui
