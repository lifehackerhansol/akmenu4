/*
    unicode.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>
#include <string>

std::string unicode_to_local_string(const u16* unicode_string, size_t length,
                                    bool* defCharUsed = NULL);
