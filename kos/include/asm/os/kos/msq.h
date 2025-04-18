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
/*!replace_with_include <asm/os/msq.h>*/
#ifndef _ASM_OS_KOS_MSQ_H
#define _ASM_OS_KOS_MSQ_H 1

#include <__stdinc.h>

/* Define options for message queue functions. */
#define __MSG_NOERROR 010000 /* ??? */
#define __MSG_EXCEPT  020000 /* ??? */
#define __MSG_COPY    040000 /* ??? */

/* ipcs ctl commands */
#define __MSG_STAT 11 /* ??? */
#define __MSG_INFO 12 /* ??? */

#endif /* _ASM_OS_KOS_MSQ_H */
