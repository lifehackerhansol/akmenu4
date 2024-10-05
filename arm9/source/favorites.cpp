/*
    favorites.cpp
    Copyright (C) 2008 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "favorites.h"
#include "inifile.h"
#include "systemfilenames.h"

bool cFavorites::AddToFavorites(const std::string& aFileName) {
    CIniFile ini(SFN_FAVORITES);
    std::vector<std::string> items;
    ini.GetStringVector("main", "list", items, '|');
    for (size_t ii = 0; ii < items.size(); ++ii) {
        if (items[ii] == aFileName) return false;
    }
    items.push_back(aFileName);
    ini.SetStringVector("main", "list", items, '|');
    ini.SaveIniFile(SFN_FAVORITES);
    return true;
}

bool cFavorites::UpdateFavorites(const std::string& aOldFileName, const std::string& aNewFileName) {
    CIniFile ini(SFN_FAVORITES);
    std::vector<std::string> items;
    ini.GetStringVector("main", "list", items, '|');
    for (size_t ii = 0; ii < items.size(); ++ii) {
        if (items[ii] == aOldFileName) {
            items[ii] = aNewFileName;
            ini.SetStringVector("main", "list", items, '|');
            ini.SaveIniFile(SFN_FAVORITES);
            return true;
        }
    }
    return false;
}

bool cFavorites::RemoveFromFavorites(const std::string& aFileName) {
    CIniFile ini(SFN_FAVORITES);
    std::vector<std::string> items;
    ini.GetStringVector("main", "list", items, '|');
    for (size_t ii = 0; ii < items.size(); ++ii) {
        if (items[ii] == aFileName) {
            items.erase(items.begin() + ii);
            ini.SetStringVector("main", "list", items, '|');
            ini.SaveIniFile(SFN_FAVORITES);
            return true;
        }
    }
    return false;
}
