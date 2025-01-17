/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ARM_KOS_KOS_EXEC_ASM_ELF_H
#define _ARM_KOS_KOS_EXEC_ASM_ELF_H 1

#include <__stdinc.h>

#include <hybrid/byteorder.h>
#include <hybrid/host.h>

#include <elf.h>

#ifdef __arm__
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define ELF_ARCH_DATA     ELFDATA2MSB
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define ELF_ARCH_DATA     ELFDATA2LSB
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#define ELF_ARCH_CLASS    ELF_ARCHARM_CLASS
#define ELF_ARCH_MACHINE  ELF_ARCHARM_MACHINE
#define ELF_ARCH_USESRELA ELF_ARCHARM_USESRELA
#define ELF_ARCH_LAZYINDX ELF_ARCHARM_LAZYINDX
#endif /* __arm__ */

#define ELF_ARCHARM_CLASS    ELFCLASS32
#define ELF_ARCHARM_MACHINE  EM_ARM
#define ELF_ARCHARM_USESRELA 0 /* arm doesn't use addend-relocations */
#define ELF_ARCHARM_LAZYINDX 0 /* Lazy relocations use offsets, rather than indices */

#endif /* !_ARM_KOS_KOS_EXEC_ASM_ELF_H */
