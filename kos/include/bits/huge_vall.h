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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_HUGE_VALL_H
#define _BITS_HUGE_VALL_H 1

#include <__stdinc.h>

/* `HUGE_VALL' constant for ix86 (where it is infinity).
   Used by <stdlib.h> and <math.h> functions for overflow.
   Copyright (C) 1992-2016 Free Software Foundation, Inc.
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

#ifdef __CC__
#ifdef __COMPILER_HAVE_LONGDOUBLE
__SYSDECL_BEGIN

#if __has_builtin(__builtin_huge_vall)
#define HUGE_VALL (__builtin_huge_vall())
#else /* ... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_DOUBLE__ == 12
#if defined(__GNUC__) && __GCC_VERSION_NUM >= 29600
#define HUGE_VALL (__extension__ 0x1.0p32767L)
#elif defined(__GNUC__)
#define HUGE_VALL (__extension__((union { __BYTE_TYPE__ __c[12]; long double __ld; }) { { 0, 0, 0, 0, 0, 0, 0, 0x80, 0xff, 0x7f, 0, 0 } }).__ld)
#else /* ... */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA union {
	__BYTE_TYPE__ __c[12];
	long double   __ld;
} const __huge_valf = {
	{ 0, 0, 0, 0, 0, 0, 0, 0x80, 0xff, 0x7f, 0, 0 }
};
__NAMESPACE_LOCAL_END
#define HUGE_VALL (__NAMESPACE_LOCAL_SYM __huge_valf.__ld)
#endif /* !... */
#elif __SIZEOF_LONG_DOUBLE__ == 8
#if defined(__GNUC__) && __GCC_VERSION_NUM >= 29600
#define HUGE_VALL (__extension__ 0x1.0p2047)
#elif defined(__GNUC__)
#define HUGE_VALL (__extension__((union { __UINT64_TYPE__ __l; long double __ld; }) { 0x7ff0000000000000ULL }).__ld)
#else /* ... */
#include <hybrid/__byteorder.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA union {
	__BYTE_TYPE__ __c[8];
	long double   __ld;
} const __huge_valf = {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ 0x7f, 0xf0, 0, 0, 0, 0, 0, 0 }
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ 0, 0, 0, 0, 0, 0, 0xf0, 0x7f }
#else
#error "Unsupported __BYTE_ORDER__"
#endif
};
__NAMESPACE_LOCAL_END
#define HUGE_VALL (__NAMESPACE_LOCAL_SYM __huge_valf.__ld)
#endif /* !... */
#elif __SIZEOF_LONG_DOUBLE__ == 4
#if defined(__GNUC__) && __GCC_VERSION_NUM >= 29600
#define HUGE_VALL (__extension__ 0x1.0p255f)
#elif defined(__GNUC__)
#define HUGE_VALL (__extension__((union { __UINT32_TYPE__ __l; long double __ld; }) { 0x7f800000UL }).__ld)
#else /* ... */
#include <hybrid/__byteorder.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA union {
	__BYTE_TYPE__ __c[4];
	long double   __ld;
} const __huge_valf = {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ 0x7f, 0x80, 0, 0 }
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ 0, 0, 0x80, 0x7f }
#else
#error "Unsupported __BYTE_ORDER__"
#endif
};
__NAMESPACE_LOCAL_END
#define HUGE_VALL (__NAMESPACE_LOCAL_SYM __huge_valf.__ld)
#endif /* !... */
#else  /* __SIZEOF_LONG_DOUBLE__... */
#error "Unsupported __SIZEOF_LONG_DOUBLE__"
#endif /* !__SIZEOF_LONG_DOUBLE__... */
#endif /* !... */

__SYSDECL_END
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __CC__ */


#endif /* !_BITS_HUGE_VALL_H */
