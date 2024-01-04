/* HASH CRC-32:0x6ccff44a */
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
/* (#) Portability: Linux (/include/linux/close_range.h) */
#ifndef _LINUX_CLOSE_RANGE_H
#define _LINUX_CLOSE_RANGE_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */


/* Flags for `close_range(2)' */
#if defined(__linux__) || defined(__KOS__)
#define CLOSE_RANGE_UNSHARE 0x0001 /* Unshare handles first (s.a. `handman_fork_and_closerange()') */
#define CLOSE_RANGE_CLOEXEC 0x0002 /* Don't close files. -- Instead, set the `IO_CLOEXEC' bit for them */
#endif /* __linux__ || __KOS__ */

#ifdef __CC__
__SYSDECL_BEGIN

/*
 * Linux doesn't normally define this function here (and Glibc doesn't actually export it by-name),
 * but  3rd party programs exist that already make  use of this function (*cough* glib) and somehow
 * expect this function to magically appear from out-of-nowhere
 *
 * On KOS, we also declare this function in <unistd.h> (in a __USE_BSD section), but we also declare
 * it here since programs that include this header /probably/ will also want to use this function...
 *
 * Also note that <unistd.h> includes this header under __USE_GNU (even though like already stated,
 * Glibc doesn't actually expose this function yet). The reason we do this is once again 3rd  party
 * program compatibility.
 *
 * For some reason, glib expects (in "glib/gspawn.c") that both `CLOSE_RANGE_CLOEXEC' and `close_range'
 * be declared, even though it never bothered to actually include any relevant headers (i.e. this one).
 * The only thing that even comes close is <unistd.h>, and the fact that it defines _GNU_SOURCE. So  we
 * use that combination to include <linux/close_range.h> from <unistd.h> and expose everything it might
 * need in regards to close_range(2)!
 */

#if !defined(__close_range_defined) && defined(__CRT_HAVE_close_range)
#define __close_range_defined
/* >> close_range(2)
 * Close all files handles `>= minfd && <= maxfd' (but see `flags')
 * @param: flags: Set of `0 | CLOSE_RANGE_UNSHARE | CLOSE_RANGE_CLOEXEC'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,close_range,(unsigned int __minfd, unsigned int __maxfd, unsigned int __flags),(__minfd,__maxfd,__flags))
#endif /* !__close_range_defined && __CRT_HAVE_close_range */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LINUX_CLOSE_RANGE_H */
