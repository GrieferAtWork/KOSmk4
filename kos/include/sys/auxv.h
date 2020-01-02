/* HASH CRC-32:0xe6920b5b */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _SYS_AUXV_H
#define _SYS_AUXV_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <elf.h>
#include <bits/auxv.h>
#include <bits/hwcap.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifdef __CRT_HAVE_getauxval
/* Return the value associated with an Elf*_auxv_t type from the auxv list
 * passed to the program on startup.  If TYPE was not present in the auxv
 * list, returns zero and sets errno to ENOENT */
__CDECLARE(,__ULONGPTR_TYPE__,__NOTHROW_NCX,getauxval,(__ULONGPTR_TYPE__ __type),(__type))
#elif defined(__CRT_HAVE___getauxval)
/* Return the value associated with an Elf*_auxv_t type from the auxv list
 * passed to the program on startup.  If TYPE was not present in the auxv
 * list, returns zero and sets errno to ENOENT */
__CREDIRECT(,__ULONGPTR_TYPE__,__NOTHROW_NCX,getauxval,(__ULONGPTR_TYPE__ __type),__getauxval,(__type))
#endif /* getauxval... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_AUXV_H */
