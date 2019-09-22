/* HASH CRC-32:0xe6c9a840 */
/* Copyright (c) 2019 Griefer@Work                                            *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBC_PARTS_UCHAR_STRING_H
#define _LIBC_PARTS_UCHAR_STRING_H 1

#include <__stdinc.h>
#include <__crt.h>
#include "slow/parts.uchar.string.h"

/* Same as `STR+c16len(STR)' */
#define __libc_c16end __libc_slow_c16end
/* Same as `STR+c32len(STR)' */
#define __libc_c32end __libc_slow_c32end
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
#define __libc_c16nend __libc_slow_c16nend
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
#define __libc_c32nend __libc_slow_c32nend
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __libc_c16len __libc_slow_c16len
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __libc_c32len __libc_slow_c32len
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __libc_c16nlen __libc_slow_c16nlen
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __libc_c32nlen __libc_slow_c32nlen
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_c16cmp __libc_slow_c16cmp
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_c32cmp __libc_slow_c32cmp
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
#define __libc_c16ncmp __libc_slow_c16ncmp
/* Same as `c32cmp', but compare at most `MAXLEN' characters from either string */
#define __libc_c32ncmp __libc_slow_c32ncmp

#endif /* !_LIBC_PARTS_UCHAR_STRING_H */
