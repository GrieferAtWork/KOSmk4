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
/*!replace_with_include <asm/os/sigstack.h>*/
#ifndef _ASM_OS_KOS_SIGSTACK_H
#define _ASM_OS_KOS_SIGSTACK_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

/* Possible values for `struct sigaltstack::ss_flags.'. */
#define __SS_ONSTACK    __UINT32_C(0x00000001) /* out.flag: Currently executing from the alternate signal stack. */
#define __SS_DISABLE    __UINT32_C(0x00000002) /* in.flag: Disable the alternate signal stack. (all other flags are ignored when set)
                                                * out.flag: The alternate signal stack is currently disabled. */
#define __SS_AUTODISARM __UINT32_C(0x80000000) /* flag:     Disable  the  alternate signal  stack upon  signal handler
                                                *           entry by  saving its  old configuration  and disabling  it
                                                *           by  means  of  `SS_DISABLE',  before  restoring  its prior
                                                *           setting  once the signal  handler returns, thus preventing
                                                *           other signal handlers from recursing onto an in-use stack. */

#define __MINSIGSTKSZ 2048 /* Minimum stack size for a signal handler. */
#define __SIGSTKSZ    8192 /* System default stack size. */

#endif /* !_ASM_OS_KOS_SIGSTACK_H */
