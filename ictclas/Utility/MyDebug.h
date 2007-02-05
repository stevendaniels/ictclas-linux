#ifndef MY_DEBUG_H
#define MY_DEBUG_H

#include <stdio.h>
#include <stdarg.h>

extern int debug_level;
extern void __debug(const char *fmt, ...);


#define my_debug(level, fmt, arg...) \
    if (level <= debug_level) __debug(fmt, ##arg)

#endif
