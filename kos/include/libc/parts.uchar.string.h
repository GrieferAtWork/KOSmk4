/* HASH CRC-32:0xd85d9e52 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBC_PARTS_UCHAR_STRING_H
#define _LIBC_PARTS_UCHAR_STRING_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include "core/parts.uchar.string.h"

/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
#define __libc_c16send __libc_core_c16send
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
#define __libc_c32send __libc_core_c32send
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
#define __libc_c16snend __libc_core_c16snend
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
#define __libc_c32snend __libc_core_c32snend
/* >> wcslen(3) */
#define __libc_c16slen __libc_core_c16slen
/* >> wcslen(3) */
#define __libc_c32slen __libc_core_c32slen
/* >> wcsnlen(3) */
#define __libc_c16snlen __libc_core_c16snlen
/* >> wcsnlen(3) */
#define __libc_c32snlen __libc_core_c32snlen
/* >> wcscmp(3) */
#define __libc_c16scmp __libc_core_c16scmp
/* >> wcscmp(3) */
#define __libc_c32scmp __libc_core_c32scmp
/* >> wcsncmp(3) */
#define __libc_c16sncmp __libc_core_c16sncmp
/* >> wcsncmp(3) */
#define __libc_c32sncmp __libc_core_c32sncmp

#endif /* __CC__ */

#endif /* !_LIBC_PARTS_UCHAR_STRING_H */
