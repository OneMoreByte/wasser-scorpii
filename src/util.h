#ifndef UTIL_H
#define UTIL_H

// delay n milliseconds (41.94MHz CPU clock)
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3180; j++)
            {}  // do nothing
}

#endif
