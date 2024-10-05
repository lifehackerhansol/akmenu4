/*
    message.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

namespace akui {

class cMessage {
    // ---------------------------------------------------------------------------------------------
    //  public enumerations
    // ---------------------------------------------------------------------------------------------
  public:
    //! all possible messages have a unique id
    enum Id {
        keyMessageStart = 0,
        keyDown,  //!< \sa KeyMessage
        keyUp,    //!< \sa KeyMessage
        keyMessageEnd,
        touchMessageStart,
        touchMove,  //!< \sa TouchMessage
        touchDown,  //!< \sa TouchMessage
        touchUp,    //!< \sa TouchMessage
        touchMessageEnd
        // more to come...
    };

    // ---------------------------------------------------------------------------------------------
    //  Construction / Destruction
    // ---------------------------------------------------------------------------------------------
  public:
    //! constructor requires id
    cMessage(Id anId) : _id(anId) {}

    //! destructor
    virtual ~cMessage() {}

    // ---------------------------------------------------------------------------------------------
    //  Accessors
    // ---------------------------------------------------------------------------------------------
  public:
    //! returns the id of the message
    Id id() const { return _id; }

    // ---------------------------------------------------------------------------------------------
    //  Implementation
    // ---------------------------------------------------------------------------------------------
  protected:
    Id _id;
};

}  // namespace akui
