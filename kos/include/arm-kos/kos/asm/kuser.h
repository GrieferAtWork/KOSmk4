/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ARM_KOS_KOS_ASM_KUSER_H
#define _ARM_KOS_KOS_ASM_KUSER_H 1

#include <__stdinc.h>

/* Special user-space helper functions */
#ifdef __CC__
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

/* The version KUSER helper version. */
#define __kuser_helper_version (*(__UINT32_TYPE__ const *)0xffff0ffc)


/* Return the calling thread's TLS pointer.
 * @return: * : The calling thread's TLS pointer.
 * @requires: __kuser_helper_version >= 1 */
#define __kuser_get_tls (*(__kuser_get_tls_t *)0xffff0fe0)
typedef void *(__kuser_get_tls_t)(void);


/* Do a 32-bit atomic-compare-exchange
 * @param: oldval: Old (expected) value
 * @param: newval: New (desired) value
 * @param: ptr:    Address to modify
 * @return: * :    Old value stored in `*ptr'
 * @requires: __kuser_helper_version >= 2 */
#define __kuser_cmpxchg (*(__kuser_cmpxchg_t *)0xffff0fc0)
typedef __UINT32_TYPE__ (__kuser_cmpxchg_t)(__UINT32_TYPE__ __oldval,
                                            __UINT32_TYPE__ __newval,
                                            __UINT32_TYPE__ volatile *__ptr);


/* DataMemoryBarrier
 * @requires: __kuser_helper_version >= 3 */
#define __kuser_dmb (*(__kuser_dmb_t *)0xffff0fa0)
typedef void (__kuser_dmb_t)(void);


/* Do a 64-bit atomic-compare-exchange
 * @param: p_oldval: Pointer to the old (expected) value
 * @param: p_newval: Pointer to the new (desired) value
 * @param: ptr:      Address to modify
 * @return: == 0:    Success (*ptr was modified)
 * @return: != 0:    Failure (*ptr wasn't modified)
 * @requires: __kuser_helper_version >= 5 */
#define __kuser_cmpxchg64 (*(__kuser_cmpxchg64_t *)0xffff0f60)
typedef int (__kuser_cmpxchg64_t)(__UINT64_TYPE__ const *__p_oldval,
                                  __UINT64_TYPE__ const *__p_newval,
                                  __UINT64_TYPE__ volatile *__ptr);

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ARM_KOS_KOS_ASM_KUSER_H */
