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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ARCH_SYSCALL_H
#define GUARD_KERNEL_INCLUDE_KERNEL_ARCH_SYSCALL_H 1

#include <kernel/compiler.h>
#include <asm/unistd.h>

#define ATTR_SECTION_SYSCALL(name) ATTR_SECTION(".text")

#ifdef __CC__
DECL_BEGIN

#define SYSCALL_RESTART_MODE_AUTO 0 /* Automatic restarting */
#define SYSCALL_RESTART_MODE_DONT 1 /* Don't restart */
#define SYSCALL_RESTART_MODE_MUST 2 /* Always restart */

/* System call restart mode / cancellation point configuration */
#define SYSCALL_RESTART_MODE(sysno)           SYSCALL_RESTART_MODE_AUTO
#define SYSCALL_RESTART_MODE_EX(sysno,error) (error)
#define SYSCALL_IS_CANCELLATION_POINT(sysno)           1
#define SYSCALL_IS_CANCELLATION_POINT_EX(sysno,error) (error)


/* Evaluate the number of registers used by a given system call. */
#define SYSCALL_REGISTER_COUNT(sysno)           6
#define SYSCALL_REGISTER_COUNT_EX(sysno,error) (error)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ARCH_SYSCALL_H */
