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
#include <hybrid/limits.h>
#include <hybrid/host.h>

.section .rodata.kernel_ld_elf
	.hidden kernel_ld_elf
	.global kernel_ld_elf
	.align  PAGESIZE
kernel_ld_elf:
#ifdef __x86_64__
	.incbin "bin/x86_64-kos/lib/libdl.rtld-flat.bin"
#else
	.incbin "bin/i386-kos/lib/libdl.rtld-flat.bin"
#endif
	.align  PAGESIZE
.hidden __x86_kernel_ld_elf_size
.global __x86_kernel_ld_elf_size
	__x86_kernel_ld_elf_size = . - kernel_ld_elf
.size kernel_ld_elf, . - kernel_ld_elf





