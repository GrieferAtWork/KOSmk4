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
#ifndef _I386_KOS_KOS_ASM_RTM_H
#define _I386_KOS_KOS_ASM_RTM_H 1

#include <asm/rtm.h>

/* RTM abort reasons. */
#define RTM_ABORT_FAILED   _XABORT_FAILED   /* Transaction cannot be performed atomically. */
#define RTM_ABORT_EXPLICIT _XABORT_EXPLICIT /* Abort was caused by `sys_rtm_abort()' (s.a. `RTM_ABORT_CODE()'). */
#define RTM_ABORT_RETRY    _XABORT_RETRY    /* The transaction may succeed if re-attempted. */
#define RTM_ABORT_CAPACITY _XABORT_CAPACITY /* The internal buffer to track transactions overflowed. */
#define RTM_ABORT_CODE_M   _XABORT_CODE_M   /* [valid_if(RTM_ABORT_EXPLICIT)] XABORT argument. */
#define RTM_ABORT_CODE_S   _XABORT_CODE_S
#define RTM_ABORT_CODE(x)  (((x) & RTM_ABORT_CODE_M) >> RTM_ABORT_CODE_S)

/* Returned by `sys_rtm_begin()' when RTM was entered successfully. */
#define RTM_STARTED _XBEGIN_STARTED


#endif /* !_I386_KOS_KOS_ASM_RTM_H */
