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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_EXEC_LIBDL_COMPAT_S
#define GUARD_KERNEL_CORE_ARCH_I386_EXEC_LIBDL_COMPAT_S 1

.section .rodata.compat_execabi_system_rtld
	.global compat_execabi_system_rtld
	.type   compat_execabi_system_rtld, "object"
	.align  4096 /* PAGESIZE */
compat_execabi_system_rtld:
	.incbin "bin/x86_64-kos/lib/libdl.rtld-flat.bin"
	.align  4096 /* PAGESIZE */
.global compat_execabi_system_rtld_size
.type   compat_execabi_system_rtld_size, "object"
	compat_execabi_system_rtld_size = . - compat_execabi_system_rtld
.size compat_execabi_system_rtld, . - compat_execabi_system_rtld

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_EXEC_LIBDL_COMPAT_S */
