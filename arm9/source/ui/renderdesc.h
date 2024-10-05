/*
    renderdesc.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "gdi.h"
#include "rectangle.h"

namespace akui {

class cRenderDesc {
    // ----------------------------------------------------------------------------------------------
    //  Xstruction
    // ----------------------------------------------------------------------------------------------
  public:
    //! Default Constructor
    cRenderDesc() {}

    //! Destructor
    virtual ~cRenderDesc() {}

    // ----------------------------------------------------------------------------------------------
    //  Public Interface
    // ----------------------------------------------------------------------------------------------
  public:
    //! draws on the passed in area according to the descriptor
    virtual void draw(const cRect& area, GRAPHICS_ENGINE engine) const = 0;
};

}  // namespace akui
