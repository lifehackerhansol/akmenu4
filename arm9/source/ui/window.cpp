/*
    window.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "window.h"
#include "ui.h"
#include "windowmanager.h"

namespace akui {

cWindow::cWindow(cWindow* aParent, const std::string& aText)
    : _parent(aParent),
      _text(aText),
      _size(cSize(0, 0)),
      _position(cPoint(0, 0)),
      _relative_position(cPoint(0, 0)),
      _isVisible(true),
      _isSizeSetByUser(false),
      _isFocusable(true),
      _engine(GE_MAIN) {}

cWindow::~cWindow() {
    if (isFocused()) windowManager().setFocusedWindow(NULL);
}

cWindow& cWindow::setWindowRectangle(const cRect& rect) {
    setSize(rect.size());
    setPosition(rect.position());
    return *this;
}

cRect cWindow::windowRectangle() const {
    return cRect(position(), position() + size());
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

bool cWindow::isFocused() const {
    return windowManager().focusedWindow() == this;
}

cWindow& cWindow::enableFocused() {
    onGainedFocus();
    return *this;
}

cWindow& cWindow::disableFocused() {
    onLostFocus();
    return *this;
}

cWindow* cWindow::windowBelow(const cPoint& p) {
    cWindow* ret = 0;
    if (isVisible()) {
        if (windowRectangle().surrounds(p)) ret = this;
    }
    return ret;
}

cWindow& cWindow::show() {
    _isVisible = true;
    onShow();
    return *this;
}

cWindow& cWindow::hide() {
    _isVisible = false;
    onHide();
    return *this;
}

bool cWindow::doesHierarchyContain(cWindow* aWindow) const {
    return (aWindow == this);
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

cWindow* cWindow::topLevelWindow() const {
    cWindow* ret = (cWindow*)(this);
    cWindow* test = ret;
    while (test != 0) {
        ret = test;
        test = ret->parent();
    }
    return ret;
}

bool cWindow::process(const cMessage& msg) {
    // dbg_printf("%08x call default process()\n", this );
    return false;
}

cWindow& cWindow::render() {
    ////dbg_printf("cWindow::render this is %08x\n", this );
    if (isVisible()) draw();
    return *this;
}

cWindow& cWindow::setSize(const cSize& aSize) {
    _size = aSize;
    onResize();
    _isSizeSetByUser = true;
    return *this;
}

cWindow& cWindow::setPosition(const cPoint& aPosition) {
    _position = aPosition;
    onMove();
    return *this;
}

cWindow& cWindow::setText(const std::string& aText) {
    _text = aText;
    onTextChanged();
    return *this;
}

}  // namespace akui
