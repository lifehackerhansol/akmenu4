/*
    button.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "bmp15.h"
#include "rectangle.h"
#include "renderdesc.h"
#include "window.h"

namespace akui {

class cButtonDesc;

class cButton : public cWindow {
  public:
    enum State { up = 0, down = 1 };

    enum Style { single = 0, press = 1, toggle = 2 };

    enum Alignment { left, center, right };

    cButton(s32 x, s32 y, u32 w, u32 h, cWindow* parent, const std::string& text);

    ~cButton();

  public:
    void draw();

    cWindow& loadAppearance(const std::string& aFileName);

    bool process(const cMessage& msg);

    State state() { return _state; }

    void setTextColor(COLOR color) { _textColor = color; }

    COLOR textColor() { return _textColor; }

    void setStyle(Style style) { _style = style; }

    Style style() { return _style; }

    void setAlignment(Alignment alignment) { _alignment = alignment; }

    Alignment alignment() { return _alignment; }

    void onPressed();

    void onReleased();

    void onClicked();

    Signal0 clicked;

    Signal0 pressed;

  protected:
    bool processTouchMessage(const akui::cTouchMessage& msg);

    bool _captured;

    State _state;

    COLOR _textColor;

    cButtonDesc* _renderDesc;

    Style _style;

    Alignment _alignment;
};

// form desc，只负责画背景
class cButtonDesc : public cRenderDesc {
  public:
    cButtonDesc();

    ~cButtonDesc();

  public:
    cButtonDesc& setButton(cButton* button) {
        _button = button;
        return *this;
    }

    void draw(const cRect& area, GRAPHICS_ENGINE engine) const;

    void loadData(const std::string& filename);

  protected:
    cButton* _button;
    cBMP15 _background;
    COLOR _textColor;
};
}  // namespace akui
