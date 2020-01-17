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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_EXEC_LIBDL_COMPAT_S
#define GUARD_KERNEL_CORE_ARCH_I386_EXEC_LIBDL_COMPAT_S 1

.section .rodata.elfexec_system_rtld32
	.global elfexec_system_rtld32
	.type   elfexec_system_rtld32, @object
	.align  4096 /* PAGESIZE */
elfexec_system_rtld32:
	.incbin "bin/x86_64-kos/lib/libdl.rtld-flat.bin"
	.align  4096 /* PAGESIZE */
.global elfexec_system_rtld32_size
.type   elfexec_system_rtld32_size, @object
	elfexec_system_rtld32_size = . - elfexec_system_rtld32
.size elfexec_system_rtld32, . - elfexec_system_rtld32

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_EXEC_LIBDL_COMPAT_S */
