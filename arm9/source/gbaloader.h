/*
    gbaloader.h
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds/ndstypes.h>
#include <string>

class CGbaLoader {
  private:
    std::string iFileName;
    u32 iSize;

  private:
    CGbaLoader();
    static void LoadBorder(void);
    static void BootGBA(void);
    bool LoadPSRAM(void);
    bool LoadNor(void);
    bool LoadInternal(bool nor, bool force);
    void InitNor(void);
    void InitPSRAM(void);
    bool StoreOldSave(std::string& aFileName);
    bool CheckLink(void);

  public:
    CGbaLoader(const std::string& aFileName);
    bool Load(bool aForce, bool aNotStart);
    static bool CheckPSRAM(u32 aSize);
    static void StartGBA(void);
};
