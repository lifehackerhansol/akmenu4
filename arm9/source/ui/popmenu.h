/*
    popmenu.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>
#include <vector>
#include "form.h"
#include "point.h"
#include "sigslot.h"
#include "window.h"

namespace akui {

class cPopMenu : public cWindow {
  public:
    cPopMenu(s32 x, s32 y, u32 w, u32 h, cWindow* parent, const std::string& text);

    ~cPopMenu();

  public:
    void draw();

    bool process(const cMessage& msg);

    // 返回选中的项
    void popup();

    void addItem(size_t index, const std::string& itemText);

    void removeItem(size_t index);

    size_t itemCount();

    void clearItem();

    Signal1<s16> itemClicked;

  protected:
    void onShow();

    bool processKeyMessage(const cKeyMessage& msg);

    bool processTouchMessage(const cTouchMessage& msg);

    size_t itemBelowPoint(const cPoint& pt);

    void drawItems();

    s16 barWidth(void);

    cPoint _itemTopLeftPoint;

    std::vector<std::string> _items;

    s16 _selectedItemIndex;

    s16 _itemHeight;
    s16 _itemWidth;
    s16 _barLeft;

    COLOR _textColor;
    COLOR _textHighLightColor;
    COLOR _barColor;

    cBitmapDesc* _renderDesc;
    bool _skipTouch;
};

}  // namespace akui
