#include <stdio.h>
#include <stdlib.h>

#include "MyDebug.h"

int debug_level = 4;

void __debug(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}


