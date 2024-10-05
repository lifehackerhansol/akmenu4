/*
    touchmessage.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "message.h"

namespace akui {

//! Message caused by interaction with the mouse
class cTouchMessage : public cMessage {
    // ---------------------------------------------------------------------------------------------
    //  Construction / Destruction
    // ---------------------------------------------------------------------------------------------
  public:
    //! construction requires the id and the mouse position
    cTouchMessage(Id anId, const cPoint& aPosition) : cMessage(anId), _position(aPosition) {}

    //! destructor
    virtual ~cTouchMessage() {}

    // ---------------------------------------------------------------------------------------------
    //  Accessors
    // ---------------------------------------------------------------------------------------------
  public:
    //! returns the position of the mouse cursor when the message occured
    cPoint position() const { return _position; }

    //! convenience method for getting the mouse x position
    s32 x() const { return position().x; }

    //! convenience method for getting the mouse y position
    s32 y() const { return position().y; }

    // ---------------------------------------------------------------------------------------------
    //  Implementation
    // ---------------------------------------------------------------------------------------------
  protected:
    cPoint _position;
};

}  // namespace akui
