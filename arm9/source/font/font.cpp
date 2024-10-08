/*
    font.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "font.h"
#include <nds.h>
#include <string.h>
#include "dbgtool.h"
#include "systemfilenames.h"

cFont::cFont() {}

cFont::~cFont() {}

u32 cFont::getStringScreenWidth(const char* str, size_t len) {
    if (NULL == str || 0 == len) return 0;

    size_t strLen = strlen(str);
    if (len > strLen) len = strLen;

    const char* endstr = str + len;
    u32 width = 0;
    const char* p = str;
    while (*p != 0 && p < endstr) {
        u32 ww, add;
        Info(p, &ww, &add);
        width += ww;
        p += add;
    }
    return width;
}

std::string cFont::breakLine(const std::string& text, u32 maxLineWidth) {
    if (0 == maxLineWidth) return text;

    std::string ret;

    // 找空格
    // 找到之后，和上次空格相减，传入 计算width 函数
    // 如果tempwdith超过 maxwidth，把上次的空格换成 \n
    // tempwidth 清零，继续

    const char* p = text.c_str();
    bool hasSpace = false;
    u32 tempWidth = 0;

    while (*p != 0) {
        u32 ww, add;
        Info(p, &ww, &add);

        if (' ' == *p) hasSpace = true;
        tempWidth += ww;
        if (tempWidth > maxLineWidth) {
            if (hasSpace) {
                u32 lastSpacePos = ret.find_last_of(' ');
                ret[lastSpacePos] = '\n';
                tempWidth = getStringScreenWidth(text.c_str() + lastSpacePos,
                                                 (size_t)(p - text.c_str()) - lastSpacePos);
                hasSpace = false;
            } else {
                ret.push_back('\n');
                tempWidth = 0;
            }
        }
        for (u32 ii = 0; ii < add; ii++) ret.push_back(*p++);
    }
    if (ret[ret.length() - 1] != '\n') ret.push_back('\n');

    return ret;
}

u32 cFont::FontRAM(void) {
    return 0;
}
