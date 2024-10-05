/*
    keymessage.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "message.h"

namespace akui {

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//! Message caused by interevent with the keyboard
class cKeyMessage : public cMessage {
    // ---------------------------------------------------------------------------------------------
    //  Construction / Destruction
    // ---------------------------------------------------------------------------------------------
  public:
    //! constructor
    cKeyMessage(Id anId, unsigned char aKeyCode, unsigned char aShift)
        : cMessage(anId), _keyCode(aKeyCode), _shift(aShift) {}

    //! destructor
    virtual ~cKeyMessage() {}

    // ---------------------------------------------------------------------------------------------
    //  Accessors
    // ---------------------------------------------------------------------------------------------
  public:
    //! returns the code of the key pressed in a keyPressed message
    unsigned short keyCode() const { return _keyCode; }
    //! returns the shift state
    unsigned short shift() const { return _shift; }

    // ---------------------------------------------------------------------------------------------
    //  Implementation
    // ---------------------------------------------------------------------------------------------
  public:
    static const unsigned char UI_KEY_A = 1;       //!< Keypad A button.
    static const unsigned char UI_KEY_B = 2;       //!< Keypad B button.
    static const unsigned char UI_KEY_SELECT = 3;  //!< Keypad SELECT button.
    static const unsigned char UI_KEY_START = 4;   //!< Keypad START button.
    static const unsigned char UI_KEY_RIGHT = 5;   //!< Keypad RIGHT button.
    static const unsigned char UI_KEY_LEFT = 6;    //!< Keypad LEFT button.
    static const unsigned char UI_KEY_UP = 7;      //!< Keypad UP button.
    static const unsigned char UI_KEY_DOWN = 8;    //!< Keypad DOWN button.
    static const unsigned char UI_KEY_R = 9;       //!< Right shoulder button.
    static const unsigned char UI_KEY_L = 10;      //!< Left shoulder button.
    static const unsigned char UI_KEY_X = 11;      //!< Keypad X button.
    static const unsigned char UI_KEY_Y = 12;      //!< Keypad Y button.
    static const unsigned char UI_KEY_TOUCH = 13;  //!< Touchscreen pendown.
    static const unsigned char UI_KEY_LID = 14;    //!< Lid state.

    static const unsigned char UI_SHIFT_L = 1;  //!< Left shoulder button.

  protected:
    // the code of the key pressed in a keyPressed message
    unsigned char _keyCode;
    unsigned char _shift;
};

// const unsigned char cKeyMessage::UI_KEY_A            =    1;  //!< Keypad A button.
// const unsigned char cKeyMessage::UI_KEY_B            =    2;  //!< Keypad B button.
// const unsigned char cKeyMessage::UI_KEY_SELECT        =    3;  //!< Keypad SELECT button.
// const unsigned char cKeyMessage::UI_KEY_START        =    4;  //!< Keypad START button.
// const unsigned char cKeyMessage::UI_KEY_RIGHT        =    5;  //!< Keypad RIGHT button.
// const unsigned char cKeyMessage::UI_KEY_LEFT        =    6;  //!< Keypad LEFT button.
// const unsigned char cKeyMessage::UI_KEY_UP            =    7;  //!< Keypad UP button.
// const unsigned char cKeyMessage::UI_KEY_DOWN        =    8;  //!< Keypad DOWN button.
// const unsigned char cKeyMessage::UI_KEY_R            =    9;  //!< Right shoulder button.
// const unsigned char cKeyMessage::UI_KEY_L            =    10; //!< Left shoulder button.
// const unsigned char cKeyMessage::UI_KEY_X            =    11; //!< Keypad X button.
// const unsigned char cKeyMessage::UI_KEY_Y            =    12; //!< Keypad Y button.
// const unsigned char cKeyMessage::UI_KEY_TOUCH        =    13; //!< Touchscreen pendown.
// const unsigned char cKeyMessage::UI_KEY_LID            =    14; //!< Lid state.

}  // namespace akui
