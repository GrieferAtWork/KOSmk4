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
#ifndef _BITS_SEM_H
#define _BITS_SEM_H 1

#include <__stdinc.h>

/* Flags for `semop'. */
#define __SEM_UNDO 0x1000 /* ??? */

/* Commands for `semctl'.  */
#define __GETPID  11 /* ??? */
#define __GETVAL  12 /* ??? */
#define __GETALL  13 /* ??? */
#define __GETNCNT 14 /* ??? */
#define __GETZCNT 15 /* ??? */
#define __SETVAL  16 /* ??? */
#define __SETALL  17 /* ??? */

/* ipcs ctl cmds */
#define __SEM_STAT 18 /* ??? */
#define __SEM_INFO 19 /* ??? */

#endif /* _BITS_SEM_H */
