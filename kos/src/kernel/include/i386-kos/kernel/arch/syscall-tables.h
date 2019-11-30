/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_TABLES_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_TABLES_H 1

#include <kernel/compiler.h>

#include <asm/unistd.h>

#ifndef __NR32FEAT_SYSCALL_TABLE_COUNT
#include <asm/syscalls32_d.h>
#endif /* !__NR32FEAT_SYSCALL_TABLE_COUNT */

#ifdef __CC__
DECL_BEGIN


/* Define tables used during system call routing. */
#ifdef __x86_64__
#define DEFINE_KERNEL_SYSCALL_ROUTES(id)                                                                          \
	DATDEF void *const x86_sysroute##id##_c[__NR_syscall##id##_cnt];                /* sys_XXX */                 \
	DATDEF void *const x86_sysroute##id##_asm64_syscall[__NR32_syscall##id##_cnt];  /* __x86_asm64_syscall_XXX */ \
	DATDEF void *const x86_sysroute##id##_c32[__NR_syscall##id##_cnt];              /* sys32_XXX */               \
	DATDEF void *const x86_sysroute##id##_asm32_int80[__NR32_syscall##id##_cnt];    /* __x86_asm32_int80_XXX */   \
	DATDEF void *const x86_sysroute##id##_asm32_sysenter[__NR32_syscall##id##_cnt]; /* __x86_asm32_sysenter_XXX */
#else /* __x86_64__ */
#define DEFINE_KERNEL_SYSCALL_ROUTES(id)                                                                        \
	DATDEF void *const x86_sysroute##id##_c[__NR_syscall##id##_cnt];                /* sys_XXX */               \
	DATDEF void *const x86_sysroute##id##_asm32_int80[__NR32_syscall##id##_cnt];    /* __x86_asm32_int80_XXX */ \
	DATDEF void *const x86_sysroute##id##_asm32_sysenter[__NR32_syscall##id##_cnt]; /* __x86_asm32_sysenter_XXX */
#endif /* !__x86_64__ */
__NRFEAT_SYSCALL_TABLE_FOREACH(DEFINE_KERNEL_SYSCALL_ROUTES)
#undef DEFINE_KERNEL_SYSCALL_ROUTES


/* Define some system call routing aliases. */
#ifdef __x86_64__
#define x86_sysroute0_c64 x86_sysroute0_c
#define x86_sysroute1_c64 x86_sysroute1_c
#else /* __x86_64__ */
#define x86_sysroute0_c32 x86_sysroute0_c
#define x86_sysroute1_c32 x86_sysroute1_c
#endif /* !__x86_64__ */


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_TABLES_H */
