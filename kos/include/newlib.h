/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin (/newlib/libc/include/newlib.h) */
/* (#) Portability: Newlib (/newlib/libc/include/newlib.h) */
#ifndef __NEWLIB_H__

/* DISCLAIMER: This file is based off of cygwin's `/usr/include/newlib.h' */

#include <__stdinc.h>
#ifdef __KOS__
#define _WANT_IO_C99_FORMATS             1
#define _WANT_IO_LONG_LONG               1
#define _WANT_IO_LONG_DOUBLE             1
#define _WANT_IO_POS_ARGS                1
#define _MB_CAPABLE                      1
#define _MB_LEN_MAX                      8
#define _ATEXIT_DYNAMIC_ALLOC            1
#define _HAVE_LONG_DOUBLE                1
#define _HAVE_CC_INHIBIT_LOOP_TO_LIBCALL 1
#define _FVWRITE_IN_STREAMIO             1
#define _FSEEK_OPTIMIZATION              1
#define _WIDE_ORIENT                     1
#define _UNBUF_STREAM_OPT                1
#elif __has_include("/usr/local/include/newlib.h")
#include "/usr/local/include/newlib.h"
#elif __has_include("/usr/include/newlib.h")
#include "/usr/include/newlib.h"
#else
/* Generic settings, as seen in a default installation of cygwin. */
#define _WANT_IO_C99_FORMATS             1
#define _WANT_IO_LONG_LONG               1
#define _WANT_IO_LONG_DOUBLE             1
#define _WANT_IO_POS_ARGS                1
#define _MB_CAPABLE                      1
#define _MB_LEN_MAX                      8
#define _ATEXIT_DYNAMIC_ALLOC            1
#define _HAVE_LONG_DOUBLE                1
#define _HAVE_CC_INHIBIT_LOOP_TO_LIBCALL 1
#define _FVWRITE_IN_STREAMIO             1
#define _FSEEK_OPTIMIZATION              1
#define _WIDE_ORIENT                     1
#define _UNBUF_STREAM_OPT                1
#endif

#ifndef __NEWLIB_H__
#define __NEWLIB_H__ 1
#endif /* !__NEWLIB_H__ */
#endif /* !__NEWLIB_H__ */
