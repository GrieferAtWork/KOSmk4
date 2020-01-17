/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef	_BITS_POSIX2_LIM_H
#define	_BITS_POSIX2_LIM_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/i386-linux-gnu/bits/posix2_lim.h' */

#include <__stdinc.h>

/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _POSIX2_BC_BASE_MAX
#define _POSIX2_BC_BASE_MAX        99   /* The maximum `ibase' and `obase' values allowed by the `bc' utility. */
#endif /* !_POSIX2_BC_BASE_MAX */
#ifndef _POSIX2_BC_DIM_MAX
#define _POSIX2_BC_DIM_MAX         2048 /* The maximum number of elements allowed in an array by the `bc' utility. */
#endif /* !_POSIX2_BC_DIM_MAX */
#ifndef _POSIX2_BC_SCALE_MAX
#define _POSIX2_BC_SCALE_MAX       99   /* The maximum `scale' value allowed by the `bc' utility. */
#endif /* !_POSIX2_BC_SCALE_MAX */
#ifndef _POSIX2_BC_STRING_MAX
#define _POSIX2_BC_STRING_MAX      1000 /* The maximum length of a string constant accepted by the `bc' utility. */
#endif /* !_POSIX2_BC_STRING_MAX */
#ifndef _POSIX2_COLL_WEIGHTS_MAX
#define _POSIX2_COLL_WEIGHTS_MAX   2    /* The maximum number of weights that can be assigned to an entry of the LC_COLLATE `order' keyword in the locale definition file. */
#endif /* !_POSIX2_COLL_WEIGHTS_MAX */
#ifndef _POSIX2_EXPR_NEST_MAX
#define _POSIX2_EXPR_NEST_MAX      32   /* The maximum number of expressions that can be nested within parentheses by the `expr' utility. */
#endif /* !_POSIX2_EXPR_NEST_MAX */
#ifndef _POSIX2_LINE_MAX
#define _POSIX2_LINE_MAX           2048 /* The maximum length, in bytes, of an input line. */
#endif /* !_POSIX2_LINE_MAX */
#ifndef _POSIX2_RE_DUP_MAX
#define _POSIX2_RE_DUP_MAX         255  /* The maximum number of repeated occurrences of a regular expression permitted when using the interval notation `\{M,N\}'. */
#endif /* !_POSIX2_RE_DUP_MAX */
#ifndef _POSIX2_CHARCLASS_NAME_MAX
#define _POSIX2_CHARCLASS_NAME_MAX 14   /* The maximum number of bytes in a character class name.  We have no fixed limit, 2048 is a high number. */
#endif /* !_POSIX2_CHARCLASS_NAME_MAX */
/* These values are implementation-specific, and may vary within the implementation. Their precise values can be obtained from sysconf. */
#ifndef BC_BASE_MAX
#define BC_BASE_MAX                _POSIX2_BC_BASE_MAX
#endif /* !BC_BASE_MAX */
#ifndef BC_DIM_MAX
#define BC_DIM_MAX                 _POSIX2_BC_DIM_MAX
#endif /* !BC_DIM_MAX */
#ifndef BC_SCALE_MAX
#define BC_SCALE_MAX               _POSIX2_BC_SCALE_MAX
#endif /* !BC_SCALE_MAX */
#ifndef BC_STRING_MAX
#define BC_STRING_MAX              _POSIX2_BC_STRING_MAX
#endif /* !BC_STRING_MAX */
#ifndef COLL_WEIGHTS_MAX
#define COLL_WEIGHTS_MAX           255
#endif /* !COLL_WEIGHTS_MAX */
#ifndef EXPR_NEST_MAX
#define EXPR_NEST_MAX              _POSIX2_EXPR_NEST_MAX
#endif /* !EXPR_NEST_MAX */
#ifndef LINE_MAX
#define LINE_MAX                   _POSIX2_LINE_MAX
#endif /* !LINE_MAX */
#ifndef CHARCLASS_NAME_MAX
#define CHARCLASS_NAME_MAX         2048
#endif /* !CHARCLASS_NAME_MAX */
#ifndef RE_DUP_MAX
#define RE_DUP_MAX                (0x7fff) /* This value is defined like this in regex.h. */
#endif /* !RE_DUP_MAX */

#endif /* !_BITS_POSIX2_LIM_H */
