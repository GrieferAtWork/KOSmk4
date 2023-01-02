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
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/termiox.h) */
#ifndef _SYS_TERMIOX_H
#define _SYS_TERMIOX_H 1

#include <asm/os/tty.h> /* TCGETX, TCSETX, TCSETXW, TCSETXF */
#include <bits/os/termiox.h> /* struct termiox */

#if !defined(TCGETX) && defined(__TCGETX)
#define TCGETX  __TCGETX  /* SYS5 TCGETX compatibility */
#endif /* !TCGETX && __TCGETX */
#if !defined(TCSETX) && defined(__TCSETX)
#define TCSETX  __TCSETX  /* ... */
#endif /* !TCSETX && __TCSETX */
#if !defined(TCSETXF) && defined(__TCSETXF)
#define TCSETXF __TCSETXF /* ... */
#endif /* !TCSETXF && __TCSETXF */
#if !defined(TCSETXW) && defined(__TCSETXW)
#define TCSETXW __TCSETXW /* ... */
#endif /* !TCSETXW && __TCSETXW */

#endif /* !_SYS_TERMIOX_H */
