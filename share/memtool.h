/*
    Copyright (C) 2007 Acekard, www.acekard.com

    SPDX-License-Identifier: MIT
*/

#pragma once

#include <calico/types.h>
#include "tonccpy.h"

inline void fillMemory(void* addr, u32 count, u32 value) {
    toncset(addr, value, count);
}

inline void zeroMemory(void* addr, u32 count) {
    toncset(addr, 0, count);
}
