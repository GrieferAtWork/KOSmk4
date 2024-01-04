/* HASH CRC-32:0xf2420eca */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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
#define __libc_c16end __libc_core_c16end
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
#define __libc_c32end __libc_core_c32end
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
#define __libc_c16nend __libc_core_c16nend
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
#define __libc_c32nend __libc_core_c32nend
/* >> wcslen(3) */
#define __libc_c16len __libc_core_c16len
/* >> wcslen(3) */
#define __libc_c32len __libc_core_c32len
/* >> wcsnlen(3) */
#define __libc_c16nlen __libc_core_c16nlen
/* >> wcsnlen(3) */
#define __libc_c32nlen __libc_core_c32nlen
/* >> wcscmp(3) */
#define __libc_c16cmp __libc_core_c16cmp
/* >> wcscmp(3) */
#define __libc_c32cmp __libc_core_c32cmp
/* >> wcsncmp(3) */
#define __libc_c16ncmp __libc_core_c16ncmp
/* >> wcsncmp(3) */
#define __libc_c32ncmp __libc_core_c32ncmp

#endif /* __CC__ */

#endif /* !_LIBC_PARTS_UCHAR_STRING_H */
