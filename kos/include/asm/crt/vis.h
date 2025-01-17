/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_CRT_VIS_H
#define _ASM_CRT_VIS_H 1

#include <__crt.h>

#include <hybrid/typecore.h>

/* Flags for `vis(3)' */
#define __VIS_OCTAL     0x0001 /* Always use octal encoding (e.g. "\123") */
#define __VIS_CSTYLE    0x0002 /* Escape characters by pre-fixing them with a "\" (except where that would result in special meaning) */
#define __VIS_SP        0x0004 /* The character " " (space) needs to be \-escaped */
#define __VIS_TAB       0x0008 /* The character "\t" (tab) needs to be \-escaped */
#define __VIS_NL        0x0010 /* The character "\n" (new-line) needs to be \-escaped */
#define __VIS_SAFE      0x0020 /* Characters "\b", "\a" and "\r" don't need to be \-escaped */
#define __VIS_NOSLASH   0x0040 /* The character "\\" (backslash) doesn't need to be \-escaped */
#define __VIS_HTTPSTYLE 0x0080 /* Enable support for '%AB'-escape sequences */
#define __VIS_MIMESTYLE 0x0100 /* Enable support for '=AB'-escape sequences */
#define __VIS_HTTP1866  0x0200 /* Enable support for '&amp;'-escape sequences */
#define __VIS_NOESCAPE  0x0400 /* Disable support for '\'-escape sequences */
#define __VIS_END       0x0800 /* s.a. `UNVIS_END' */
#define __VIS_GLOB      0x1000 /* Characters >>>*?[#<<<                need to be \-escaped */
#define __VIS_SHELL     0x2000 /* Characters >>>'`";&<>()|{}]\\$!^~<<< need to be \-escaped */
#define __VIS_NOLOCALE  0x4000 /* ??? */
#define __VIS_DQ        0x8000 /* The character '"' (double-quote) needs to be \-escaped */
#define __VIS_WHITE     (__VIS_SP | __VIS_TAB | __VIS_NL) /* Alias for `VIS_SP | VIS_TAB | VIS_NL' */
#define __VIS_META      (__VIS_WHITE | __VIS_GLOB | __VIS_SHELL) /* Alias for `VIS_WHITE | VIS_GLOB | VIS_SHELL' */
#define __VIS_SRCEXTRA  __INT32_C(0x40000000) /* Used by the KOS impl of `strsenvisx': there is 1 extra character at `src[srclen]'
                                               * for look-ahead when  doing octal  encoding, but  that one  shouldn't be  encoded. */

/* Return values for `unvis(3)' */
#define __UNVIS_ERROR     (-2) /* /unused/ */
#define __UNVIS_SYNBAD    (-1) /* Syntax error */
#define __UNVIS_VALID     1    /* Output byte produced; consume input byte */
#define __UNVIS_VALIDPUSH 2    /* Output byte produced */
#define __UNVIS_NOCHAR    3    /* Consume input byte */

/* Extra flags for `unvis(3)' */
#define __UNVIS_END __VIS_END /* Special marker for `unvis()' flush and pending character. */

#endif /* !_ASM_CRT_VIS_H */
