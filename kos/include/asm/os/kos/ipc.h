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
#ifndef _ASM_OS_KOS_IPC_H
#define _ASM_OS_KOS_IPC_H 1

#include <__stdinc.h>

/* Mode flags for `msgget()', `semget()', and `shmget()'. */
#define __IPC_CREAT  01000 /* ??? */
#define __IPC_EXCL   02000 /* ??? */
#define __IPC_NOWAIT 04000 /* ??? */

/* Control commands for `msgctl', `semctl', and `shmctl'. */
#define __IPC_RMID 0 /* ??? */
#define __IPC_SET  1 /* ??? */
#define __IPC_STAT 2 /* ??? */
#define __IPC_INFO 3 /* ??? */

/* Special key values. */
#define __IPC_PRIVATE 0 /* ???. */

#endif /* !_ASM_OS_KOS_IPC_H */
