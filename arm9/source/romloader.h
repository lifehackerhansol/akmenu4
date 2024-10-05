/*
    romloader.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds/ndstypes.h>
#include <string>

bool loadRom(const std::string& filename, const std::string& savename, u32 flags, long cheatOffset,
             size_t cheatSize);
