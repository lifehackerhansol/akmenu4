/*
    animation.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "animation.h"

cAnimation::cAnimation() {
    _visible = false;
}

cAnimation::~cAnimation() {}

void cAnimation::show() {
    _visible = true;
}

void cAnimation::hide() {
    _visible = false;
}

cAnimationManager::cAnimationManager() {}

cAnimationManager::~cAnimationManager() {}

void cAnimationManager::update() {
    std::list<cAnimation*>::iterator itr = _animations.begin();
    while (itr != _animations.end()) {
        (*itr)->update();
        ++itr;
    }
}

void cAnimationManager::addAnimation(cAnimation* animation) {
    _animations.push_back(animation);
}

void cAnimationManager::removeAnimation(cAnimation* animation) {
    _animations.remove(animation);
}
