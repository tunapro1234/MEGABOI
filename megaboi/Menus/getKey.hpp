#ifndef __GETKEY_H
#define __GETKEY_H

#include "../header.hpp"

inline byte getKey() {
    if (analogRead(BUTTON_DOWN) < BUTTON_TOLERANCE)
        return KEY_DOWN;

    else if (analogRead(BUTTON_UP) < BUTTON_TOLERANCE)
        return KEY_UP;

    else if (analogRead(BUTTON_RIGHT) < BUTTON_TOLERANCE)
        return KEY_RIGHT;

    else if (analogRead(BUTTON_LEFT) < BUTTON_TOLERANCE)
        return KEY_LEFT;

    else if (analogRead(BUTTON_NEXT) < BUTTON_TOLERANCE)
        return KEY_NEXT;

    else if (analogRead(BUTTON_BACK) < BUTTON_TOLERANCE)
        return KEY_BACK;

    return KEY_NONE;
}

#endif