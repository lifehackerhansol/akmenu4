/*
    windowmanager.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <list>
#include <string>
#include "userinput.h"
#include "window.h"

namespace akui {
class cWindowManager {
  private:
    struct cWindowRec {
        cWindow* _window;
        cWindow* _focused;
        cWindowRec(cWindow* window, cWindow* focused = NULL) : _window(window), _focused(focused) {}
        cWindow* operator()(void) const { return _window; }
    };
    typedef std::list<cWindowRec> cWindows;

  private:
    cWindows _backgroundWindows;
    cWindowRec _currentWindow;
    cWindow* _focusedWindow;
    cWindow* _windowBelowPen;
    cWindow* _capturedWindow;  // process touch for non-focusable window
  protected:
    cWindowManager& checkForWindowBelowPen(const cPoint& touchPoint);
    cWindow* windowBelowPen(void) const { return _windowBelowPen; }
    void updateFocusIfNecessary(const cPoint& touchPoint);
    bool process(cMessage& message) const;
    bool processTouchMessage(cTouchMessage& message);
    const cWindowManager& updateBackground(void);

  public:
    cWindowManager();
    ~cWindowManager();
    cWindow* focusedWindow(void) const { return _focusedWindow; }
    void setFocusedWindow(cWindow* aWindow);
    cWindowManager& addWindow(cWindow* aWindow);
    cWindowManager& removeWindow(cWindow* aWindow);
    cWindow* currentWindow(void) const { return _currentWindow(); }
    const cWindowManager& update(void);
    bool onKeyDown(unsigned char keyCode, unsigned char shift);
    bool onKeyUp(unsigned char keyCode, unsigned char shift);
    bool onTouchDown(int x, int y);
    bool onTouchUp(int x, int y);
    bool onTouchMove(int x, int y);
};

typedef t_singleton<cWindowManager> cWindowManager_s;
inline cWindowManager& windowManager(void) {
    return cWindowManager_s::instance();
}
}  // namespace akui
