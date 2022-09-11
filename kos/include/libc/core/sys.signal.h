/* HASH CRC-32:0x3a7a2df1 */
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
#ifndef _LIBC_CORE_SYS_SIGNAL_H
#define _LIBC_CORE_SYS_SIGNAL_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#if !defined(____libc_core_sigblockall_defined) && defined(__CRT_HAVE_sigblockall)
#define ____libc_core_sigblockall_defined
/* >> sigblockall(3)
 * Block all signals (s.a. `setsigmaskfullptr(3)')
 * @return: >1: Signals were already blocked (recursion counter)
 * @return: 1 : Signals were just blocked
 * @return: -1: Error (on KOS, `errno' was modified in this case, but on DragonFly, it isn't) */
__CREDIRECT(,int,__NOTHROW_NCX,__libc_core_sigblockall,(void),sigblockall,())
#endif /* !____libc_core_sigblockall_defined && __CRT_HAVE_sigblockall */
#if !defined(____libc_core_sigunblockall_defined) && defined(__CRT_HAVE_sigunblockall)
#define ____libc_core_sigunblockall_defined
/* >> sigunblockall(3)
 * Unblock all signals, undoing the effects of `sigblockall(3)'
 * @return: & 0x80000000: Signals were marked as pending while they were being blocked
 * @return: & 0x7fffffff != 0: Signals are still blocked (recursion counter)
 * @return: & 0x7fffffff == 0: Signals were just unblocked
 * @return: -1: Error (on KOS, `errno' was modified in this case, but on DragonFly, it isn't) */
__CREDIRECT(,int,__NOTHROW_NCX,__libc_core_sigunblockall,(void),sigunblockall,())
#endif /* !____libc_core_sigunblockall_defined && __CRT_HAVE_sigunblockall */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_SYS_SIGNAL_H */
