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
#ifndef _I386_KOS_KOS_EXEC_BITS_ELF_COMPAT_H
#define _I386_KOS_KOS_EXEC_BITS_ELF_COMPAT_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include "elf32.h"
#include "elf64.h"

#ifdef __x86_64__
#define ELF_ARCHCOMPAT_CLASS   ELF_ARCH386_CLASS
#define ELF_ARCHCOMPAT_MACHINE ELF_ARCH386_MACHINE
#define ELF_ARCHCOMPAT_DATA    ELF_ARCH386_DATA
#define COMPAT_ElfW(x) Elf32_##x
#define COMPAT_ELFW(x) ELF32_##x
#endif /* __x86_64__ */

#endif /* !_I386_KOS_KOS_EXEC_BITS_ELF_COMPAT_H */
