/* HASH CRC-32:0xd7be817c */
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
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/signal.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/signal.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/signal.h) */
/* (#) Portability: FreeBSD       (/sys/sys/signal.h) */
/* (#) Portability: GNU C Library (/signal/sys/signal.h) */
/* (#) Portability: NetBSD        (/sys/sys/signal.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/signal.h) */
/* (#) Portability: OpenBSD       (/sys/sys/signal.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/signal.h) */
/* (#) Portability: diet libc     (/include/sys/signal.h) */
/* (#) Portability: libc4/5       (/include/sys/signal.h) */
/* (#) Portability: mintlib       (/include/sys/signal.h) */
/* (#) Portability: musl libc     (/include/sys/signal.h) */
/* (#) Portability: uClibc        (/include/sys/signal.h) */
/*!always_includes <signal.h>*/
#ifndef _SYS_SIGNAL_H
#define _SYS_SIGNAL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <signal.h>

#ifdef __CC__
__SYSDECL_BEGIN


/* From DragonFly BSD: functions to quickly mask/unmask all  signals
 * Note that on KOS, these are implemented in terms of userprocmask,
 * and the `setsigmaskptr(3)' function.
 * Note that as such, trying to combining the two may result in bad
 * or  unpredictable behavior (though  that shouldn't really matter
 * since this one originates from DragonFly, and `setsigmaskptr(3)'
 * is a kos-specific invention) */
#ifdef __USE_BSD
/* >> sigblockall(3)
 * Block all signals (s.a. `setsigmaskfullptr(3)')
 * @return: >1: Signals were already blocked (recursion counter)
 * @return: 1 : Signals were just blocked
 * @return: -1: Error (on KOS, `errno' was modified in this case, but on DragonFly, it isn't) */
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigblockall,(void),())
/* >> sigunblockall(3)
 * Unblock all signals, undoing the effects of `sigblockall(3)'
 * @return: & 0x80000000: Signals were marked as pending while they were being blocked
 * @return: & 0x7fffffff != 0: Signals are still blocked (recursion counter)
 * @return: & 0x7fffffff == 0: Signals were just unblocked
 * @return: -1: Error (on KOS, `errno' was modified in this case, but on DragonFly, it isn't) */
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigunblockall,(void),())
#endif /* __USE_BSD */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_SIGNAL_H */
