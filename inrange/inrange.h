/*
 * rutils/inrange.h - A simple library for checking whether a number is within
 *                    a certain range.
 * -------------------------------------------------------------------------------
 * I dedicate any and all copyright interest in this software to the
 * public domain. I make this dedication for the benefit of the public at
 * large and to the detriment of my heirs and successors. I intend this
 * dedication to be an overt act of relinquishment in perpetuity of all
 * present and future rights to this software under copyright law.
 */

#ifndef RUTILS_INRANGE_H
#define RUTILS_INRANGE_H

#include <stdarg.h>

#ifndef RUTILS_RANGE_NUMTYPE
    #define RUTILS_RANGE_NUMTYPE double
#endif /* RUTILS_RANGE_NUMTYPE */

#define RANGE(name, min_, max_) \
    struct rutils_range_s name = { .min = min_, .max = max_ };

struct rutils_range_s {
    RUTILS_RANGE_NUMTYPE min, max;
};

struct rutils_range_s rutils_range_slice(int ranges_count, ...);
struct rutils_range_s rutils_va_range_slice(int ranges_count, va_list arglist);

int rutils_isinranges(RUTILS_RANGE_NUMTYPE value, int rngcnt, ...);
int rutils_va_isinranges(RUTILS_RANGE_NUMTYPE value, int rngcnt, va_list va);

int rutils_isinrange(RUTILS_RANGE_NUMTYPE value, struct rutils_range_s range);

#ifdef RUTILS_INRANGE_IMPL

struct rutils_range_s rutils_va_range_slice(int ranges_count, va_list va) {
    int i;
    struct rutils_range_s item, ret;
    RUTILS_RANGE_NUMTYPE calc_min, calc_max;

    /* Find the minimum and maximum of all ranges.
     * That is the sliced range */
    item = va_arg(va, struct rutils_range_s);
    ret.min = item.min;
    ret.max = item.max;

    for (i = 1; i < ranges_count; i++) {
        item = va_arg(va, struct rutils_range_s);
	if (ret.min < calc_min && item.max > ret.max) {
	    ret.max = item.max;
	    ret.min = item.min;
	}
    }

    return ret;
}

struct rutils_range_s rutils_range_slice(int ranges_count, ...) {
    va_list va;
    struct rutils_range_s sliced;

    va_start(va, ranges_count);
    sliced = rutils_va_range_slice(ranges_count, va);
    va_end(va);

    return sliced;
}

int rutils_va_isinranges(RUTILS_RANGE_NUMTYPE value, int rngcnt, va_list va) {
    int i, retflag;
    struct rutils_range_s seen_range = rutils_va_range_slice(rngcnt, va);

    return rutils_isinrange(value, seen_range);
}

int rutils_isinranges(RUTILS_RANGE_NUMTYPE value, int rngcnt, ...) {
    va_list va;
    int result;

    va_start(va, rngcnt);
    result = rutils_va_isinranges(value, rngcnt, va);
    va_end(va);

    return result;
}

int rutils_isinrange(RUTILS_RANGE_NUMTYPE value, struct rutils_range_s range) {
    return (value >= range.min && value <= range.max);
}

#endif /* RUTILS_INRANGE_IMPL */

#endif /* RUTILS_INRANGE_H */
