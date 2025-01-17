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
#ifndef _ASM_CRT_PROCESS_H
#define _ASM_CRT_PROCESS_H 1

#include <__crt.h>

/* `mode' argument values for spawn() functions. */
#define __P_WAIT    0 /* Wait for the process to terminate, and return its exit status */
#define __P_NOWAIT  1 /* Spawn the process asynchronously, and return its PID */
#define __P_OVERLAY 2 /* Don't spawn, but rather try to exec() the new program */
#define __P_NOWAITO 3 /* Same as `P_NOWAIT' */
#define __P_DETACH  4 /* Create the new process as detached and return `0' */

/* `action' argument values for cwait() functions. */
#define __WAIT_CHILD      0 /* Ignored */
#define __WAIT_GRANDCHILD 1 /* Ignored */

#endif /* !_ASM_CRT_PROCESS_H */
