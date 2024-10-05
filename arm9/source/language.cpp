/*
    language.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "language.h"

bool stringComp(const std::string& item1, const std::string& item2) {
    return strcasecmp(item1.c_str(), item2.c_str()) < 0;
}
