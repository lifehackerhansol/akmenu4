/*
    datetime.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "datetime.h"
#include <string.h>  //memset

const char* cDateTime::weekdayStrings[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void cDateTime::FillTimeParts(void) {
    time_t epochTime;
    if (time(&epochTime) == (time_t)-1) {
        memset(&iTimeParts, 0, sizeof(iTimeParts));
    } else {
        localtime_r(&epochTime, &iTimeParts);
    }
}

u16 cDateTime::year() {
    FillTimeParts();
    return iTimeParts.tm_year + 1900;
}

u8 cDateTime::month() {
    FillTimeParts();
    return iTimeParts.tm_mon + 1;
}

u8 cDateTime::day() {
    FillTimeParts();
    return iTimeParts.tm_mday;
}

u8 cDateTime::weekday() {
    FillTimeParts();
    return iTimeParts.tm_wday;
}

u8 cDateTime::hours() {
    FillTimeParts();
    return iTimeParts.tm_hour;
}

u8 cDateTime::minutes() {
    FillTimeParts();
    return iTimeParts.tm_min;
}

u8 cDateTime::seconds() {
    FillTimeParts();
    return iTimeParts.tm_sec;
}

std::string cDateTime::getDateString() {
    // FillTimeParts();
    return formatString("%d/%d%/%d %s\n", year(), month(), day(), weekdayStrings[weekday()]);
}

std::string cDateTime::getTimeString() {
    // FillTimeParts();
    return formatString("%d:%d%:%d\n", hours(), minutes(), seconds());
}

std::string cDateTime::getTimeStampString() {
    // FillTimeParts();
    return formatString("%04d%02d%02d%02d%02d%02d", year(), month(), day(), hours(), minutes(),
                        seconds());
}
