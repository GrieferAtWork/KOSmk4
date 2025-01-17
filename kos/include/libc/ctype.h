/* HASH CRC-32:0x847f9491 */
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
#ifndef _LIBC_CTYPE_H
#define _LIBC_CTYPE_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include "core/ctype.h"

/* >> iscntrl(3) */
#define __libc_iscntrl __libc_core_iscntrl
/* >> isspace(3) */
#define __libc_isspace __libc_core_isspace
/* >> isupper(3) */
#define __libc_isupper __libc_core_isupper
/* >> islower(3) */
#define __libc_islower __libc_core_islower
/* >> isalpha(3) */
#define __libc_isalpha __libc_core_isalpha
/* >> isdigit(3) */
#define __libc_isdigit __libc_core_isdigit
/* >> isxdigit(3) */
#define __libc_isxdigit __libc_core_isxdigit
/* >> isalnum(3) */
#define __libc_isalnum __libc_core_isalnum
/* >> ispunct(3) */
#define __libc_ispunct __libc_core_ispunct
/* >> isgraph(3) */
#define __libc_isgraph __libc_core_isgraph
/* >> isprint(3) */
#define __libc_isprint __libc_core_isprint
/* >> tolower(3) */
#define __libc_tolower __libc_core_tolower
/* >> toupper(3) */
#define __libc_toupper __libc_core_toupper
/* >> isblank(3) */
#define __libc_isblank __libc_core_isblank

#endif /* __CC__ */

#endif /* !_LIBC_CTYPE_H */
