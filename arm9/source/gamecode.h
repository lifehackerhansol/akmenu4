/*
    gamecode.h
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

inline u32 gamecode(const char* aGameCode) {
    u32 gameCode;
    memcpy(&gameCode, aGameCode, sizeof(gameCode));
    return gameCode;
}
