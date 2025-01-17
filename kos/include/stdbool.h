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
/* (>) Standard: ISO C99 (ISO/IEC 9899:1999) */
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: DJGPP         (/include/stdbool.h) */
/* (#) Portability: DragonFly BSD (/include/stdbool.h) */
/* (#) Portability: FreeBSD       (/include/stdbool.h) */
/* (#) Portability: MSVC          (/include/stdbool.h) */
/* (#) Portability: OpenBSD       (/include/stdbool.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdbool.h) */
/* (#) Portability: PDCLib        (/include/stdbool.h) */
/* (#) Portability: diet libc     (/include/stdbool.h) */
/* (#) Portability: musl libc     (/include/stdbool.h) */
#ifndef _STDBOOL_H
#define _STDBOOL_H 1

#include "__stdinc.h"

#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1
#ifndef __cplusplus
#define bool  __BOOL
#define true  1
#define false 0
#endif /* !__cplusplus */
#endif /* !__bool_true_false_are_defined */

#endif /* !_STDBOOL_H */
