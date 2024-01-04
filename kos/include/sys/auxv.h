/* HASH CRC-32:0xbf96f7c5 */
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
/* (#) Portability: FreeBSD       (/sys/sys/auxv.h) */
/* (#) Portability: GNU C Library (/misc/sys/auxv.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/auxv.h) */
/* (#) Portability: diet libc     (/include/sys/auxv.h) */
/* (#) Portability: musl libc     (/include/sys/auxv.h) */
#ifndef _SYS_AUXV_H
#define _SYS_AUXV_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <elf.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_getauxval
/* >> getauxval(3)
 * Return the value associated with  a named `type' from  the
 * auxiliary information vector passed to the calling program
 * by the kernel.
 * @param: type: One of `AT_*' from <elf.h> */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__ULONGPTR_TYPE__,__NOTHROW_NCX,getauxval,(__ULONGPTR_TYPE__ __type),(__type))
#elif defined(__CRT_HAVE___getauxval)
/* >> getauxval(3)
 * Return the value associated with  a named `type' from  the
 * auxiliary information vector passed to the calling program
 * by the kernel.
 * @param: type: One of `AT_*' from <elf.h> */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__ULONGPTR_TYPE__,__NOTHROW_NCX,getauxval,(__ULONGPTR_TYPE__ __type),__getauxval,(__type))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_AUXV_H */
