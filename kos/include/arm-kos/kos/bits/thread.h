/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ARM_KOS_KOS_BITS_THREAD_H
#define _ARM_KOS_KOS_BITS_THREAD_H 1

#include <__stdinc.h>

#ifndef __KERNEL__
#if defined(__KOS__) || defined(__linux__)
#include <kos/asm/kuser.h>
#include <kos/syscalls.h>

#define RD_TLS_BASE_REGISTER(l_result) (void)((l_result) = __kuser_get_tls())
#ifdef __KOS__
#define RD_TLS_BASE_REGISTER_S(l_result) (void)((l_result) = sys_Xget_tls())
#define WR_TLS_BASE_REGISTER(value)      (void)sys_Xset_tls((void const *)(value))
#else /* __KOS__ */
#define RD_TLS_BASE_REGISTER_S(l_result) (void)((l_result) = sys_get_tls())
#define WR_TLS_BASE_REGISTER(value)      (void)sys_set_tls((void const *)(value))
#endif /* !__KOS__ */
#endif /* __KOS__ || __linux__ */
#endif /* !__KERNEL__ */

#endif /* !_ARM_KOS_KOS_BITS_THREAD_H */
