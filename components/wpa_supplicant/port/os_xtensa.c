/*
 * wpa_supplicant/hostapd / Internal implementation of OS specific functions
 * Copyright (c) 2005-2006, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 *
 * This file is an example of operating system specific  wrapper functions.
 * This version implements many of the functions internally, so it can be used
 * to fill in missing functions from the target system C libraries.
 *
 * Some of the functions are using standard C library calls in order to keep
 * this file in working condition to allow the functions to be tested on a
 * Linux target. Please note that OS_NO_C_LIB_DEFINES needs to be defined for
 * this file to work correctly. Note that these implementations are only
 * examples and are not optimized for speed.
 */
#include <string.h>
#include "FreeRTOS.h"
#include "os.h"

void *_xmalloc(size_t n)
{
    void *return_addr = (void *)__builtin_return_address(0);

    return _heap_caps_malloc(n, MALLOC_CAP_8BIT, return_addr, 0);
}

void _xfree(void *ptr)
{
    void *return_addr = (void *)__builtin_return_address(0);

    _heap_caps_free(ptr, return_addr, 0);
}

void *_xrealloc(void *ptr, size_t n)
{
    void *return_addr = (void *)__builtin_return_address(0);

    return _heap_caps_realloc(ptr, n, MALLOC_CAP_8BIT, return_addr, 0);
}

int os_get_time(struct os_time* t)
{
    int res = 0;
    return res;
}

uint32_t esp_random(void);

int ICACHE_FLASH_ATTR os_get_random(unsigned char* buf, size_t len)
{
    int i, j;
    unsigned long tmp;

    for (i = 0; i < ((len + 3) & ~3) / 4; i++) {
        tmp = esp_random();

        for (j = 0; j < 4; j++) {
            if ((i * 4 + j) < len) {
                buf[i * 4 + j] = (uint8_t)(tmp >> (j * 8));
            } else {
                break;
            }
        }
    }

    return 0;
}
