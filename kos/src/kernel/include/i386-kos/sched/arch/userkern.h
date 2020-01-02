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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_USERKERN_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_USERKERN_H 1

#include <kernel/compiler.h>

#include <kernel/gdt.h>

#include <hybrid/host.h>

#ifndef USERKERN_SEGMENT_ALIGN
#define USERKERN_SEGMENT_ALIGN 16
#endif /* !USERKERN_SEGMENT_ALIGN */


/* Get/set the base address of the userkern segment. */
#ifdef __x86_64__
#define get_userkern_base()  get_user_gsbase()
#define set_userkern_base(v) set_user_gsbase(v)
#else /* __x86_64__ */
#define get_userkern_base()  get_user_fsbase()
#define set_userkern_base(v) set_user_fsbase(v)
#endif /* !__x86_64__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_USERKERN_H */
