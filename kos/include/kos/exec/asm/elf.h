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
#ifndef _KOS_EXEC_ASM_ELF_H
#define _KOS_EXEC_ASM_ELF_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <elf.h>

#ifndef ELF_ARCH_CLASS
#if __SIZEOF_POINTER__ > 4
#define ELF_ARCH_CLASS ELFCLASS64
#else /* __SIZEOF_POINTER__ > 4 */
#define ELF_ARCH_CLASS ELFCLASS32
#endif /* __SIZEOF_POINTER__ <= 4 */
#endif /* !ELF_ARCH_CLASS */

#ifndef ELF_ARCH_DATA
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define ELF_ARCH_DATA ELFDATA2LSB
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define ELF_ARCH_DATA ELFDATA2MSB
#else /* ... */
#error "Unsupported endian"
#endif /* !... */
#endif /* !ELF_ARCH_DATA */

#endif /* !_KOS_EXEC_ASM_ELF_H */
