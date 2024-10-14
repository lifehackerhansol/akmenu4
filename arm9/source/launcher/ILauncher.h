/*
    Copyright (C) 2024 lifehackerhansol

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds/ndstypes.h>
#include "../language.h"
#include "../ui/msgbox.h"

static inline void printLoaderNotFound(std::string loaderPath) {
    akui::messageBox(NULL, LANG("loader", "not found"), loaderPath, MB_OK);
}

class ILauncher {
  public:
    virtual ~ILauncher() {}
    virtual bool launchRom(std::string romPath, std::string savePath, u32 flags, u32 cheatOffset,
                           u32 cheatSize) = 0;
};
