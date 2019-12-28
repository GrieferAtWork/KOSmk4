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
#ifndef _BITS_NAN_H
#define _BITS_NAN_H 1

/* `NAN' constant for IEEE 754 machines.
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

#include <__stdinc.h>

#ifdef __CC__
__SYSDECL_BEGIN

#if __has_builtin(__builtin_nanf)
#define NAN __builtin_nanf("")
#elif defined(__GNUC__)
#define NAN (__extension__((union { unsigned __l __attribute__((__mode__(__SI__))); float __d; }) { 0x7fc00000UL }).__d)
#else /* ... */
#include <hybrid/__byteorder.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA union {
	__BYTE_TYPE__ __c[4];
	float         __d;
} const __qnan_union = {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ 0x7f, 0xc0, 0, 0 }
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ 0, 0, 0xc0, 0x7f }
#else
#error "Unsupported __BYTE_ORDER__"
#endif
};
__NAMESPACE_LOCAL_END
#define NAN (__NAMESPACE_LOCAL_SYM __qnan_union.__d)
#endif /* !... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_NAN_H */
