/*
    unicode.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2008 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "unicode.h"

std::string unicode_to_local_string(const u16* unicode_string, size_t length, bool* defCharUsed) {
    if (defCharUsed) *defCharUsed = false;
    std::string ret;
    const u16* end = unicode_string + length;
    while (*unicode_string && unicode_string < end) {
        u16 data = *unicode_string++;
        if (data < 0x80) {
            ret.push_back(data);
        } else if (data < 0x800) {
            ret.push_back(0xc0 | ((data >> 6) & 0x1f));
            ret.push_back(0x80 | (data & 0x3f));
        } else {
            ret.push_back(0xe0 | ((data >> 12) & 0x0f));
            ret.push_back(0x80 | ((data >> 6) & 0x3f));
            ret.push_back(0x80 | (data & 0x3f));
        }
    }
    return ret;
}
