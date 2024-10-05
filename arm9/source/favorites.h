/*
    favorites.h
    Copyright (C) 2008 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <string>

class cFavorites {
  public:
    static bool AddToFavorites(const std::string& aFileName);
    static bool UpdateFavorites(const std::string& aOldFileName, const std::string& aNewFileName);
    static bool RemoveFromFavorites(const std::string& aFileName);
};
