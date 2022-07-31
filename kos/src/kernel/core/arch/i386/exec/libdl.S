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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_EXEC_LIBDL_S
#define GUARD_KERNEL_CORE_ARCH_I386_EXEC_LIBDL_S 1

#include <hybrid/host.h>

.section .rodata.execabi_system_rtld
	.global execabi_system_rtld
	.type   execabi_system_rtld, "object"
	.align  4096 /* PAGESIZE */
execabi_system_rtld:
#ifdef __x86_64__
	.incbin "bin/x86_64-kos/lib64/libdl.rtld-flat.bin"
#else /* __x86_64__ */
	.incbin "bin/i386-kos/lib/libdl.rtld-flat.bin"
#endif /* !__x86_64__ */
	.align  4096 /* PAGESIZE */
.global execabi_system_rtld_size
.type   execabi_system_rtld_size, "object"
	execabi_system_rtld_size = . - execabi_system_rtld
.size execabi_system_rtld, . - execabi_system_rtld

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_EXEC_LIBDL_S */
