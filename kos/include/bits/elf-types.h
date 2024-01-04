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
#ifndef _BITS_ELF_TYPES_H
#define _BITS_ELF_TYPES_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

#define __SIZEOF_ELF32_HALF__     2
#define __SIZEOF_ELF64_HALF__     2
#define __SIZEOF_ELF32_WORD__     4
#define __SIZEOF_ELF32_SWORD__    4
#define __SIZEOF_ELF64_WORD__     4
#define __SIZEOF_ELF64_SWORD__    4
#define __SIZEOF_ELF32_XWORD__    8
#define __SIZEOF_ELF32_SXWORD__   8
#define __SIZEOF_ELF64_XWORD__    8
#define __SIZEOF_ELF64_SXWORD__   8
#define __SIZEOF_ELF32_ADDR__     4
#define __SIZEOF_ELF64_ADDR__     8
#define __SIZEOF_ELF32_OFF__      4
#define __SIZEOF_ELF64_OFF__      8
#define __SIZEOF_ELF32_SECTION__  2
#define __SIZEOF_ELF64_SECTION__  2
#define __SIZEOF_ELF32_VERSYM__   __SIZEOF_ELF32_HALF__
#define __SIZEOF_ELF64_VERSYM__   __SIZEOF_ELF64_HALF__

#ifdef __CC__
__DECL_BEGIN

#ifndef _ELF_TYPES_DEFINED
#define _ELF_TYPES_DEFINED 1
/* Type for a 16-bit quantity. */
typedef __UINT16_TYPE__ Elf32_Half;
typedef __UINT16_TYPE__ Elf64_Half;

/* Types for signed and unsigned 32-bit quantities. */
typedef __UINT32_TYPE__ Elf32_Word;
typedef __INT32_TYPE__  Elf32_Sword;
typedef __UINT32_TYPE__ Elf64_Word;
typedef __INT32_TYPE__  Elf64_Sword;

/* Types for signed and unsigned 64-bit quantities. */
typedef __UINT64_TYPE__ Elf32_Xword;
typedef __INT64_TYPE__  Elf32_Sxword;
typedef __UINT64_TYPE__ Elf64_Xword;
typedef __INT64_TYPE__  Elf64_Sxword;

/* Type of addresses. */
typedef __UINT32_TYPE__ Elf32_Addr;
typedef __UINT64_TYPE__ Elf64_Addr;

/* Type of file offsets. */
typedef __UINT32_TYPE__ Elf32_Off;
typedef __UINT64_TYPE__ Elf64_Off;

/* Type for section indices, which are 16-bit quantities. */
typedef __UINT16_TYPE__ Elf32_Section;
typedef __UINT16_TYPE__ Elf64_Section;

/* Type for version symbol information. */
typedef Elf32_Half Elf32_Versym;
typedef Elf64_Half Elf64_Versym;
#endif /* !_ELF_TYPES_DEFINED */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_ELF_TYPES_H */
