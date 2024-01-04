/* HASH CRC-32:0x844c95ba */
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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/prctl.h) */
/* (#) Portability: diet libc     (/include/sys/prctl.h) */
/* (#) Portability: musl libc     (/include/sys/prctl.h) */
#ifndef _SYS_PRCTL_H
#define _SYS_PRCTL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <linux/prctl.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_prctl
/* >> prctl(2)
 * System process control interface. (Linux compatible)
 * @param: command: One of `PR_*' (from <linux/prctl.h>)
 * @param: ... :    Up  to 4 additional arguments (dependent on `command')
 *                  Note that some control codes  require you to pass  `0'
 *                  for  all seemingly "unused" arguments. In these cases,
 *                  the documentation for that command includes the number
 *                  of unused, but required trailing 0s in its comment.
 * @return: * :     Return value depends on `command'
 * @return: -1:     Error (s.a. `errno'; depends on `command')
 * @return: -1:     [errno=EINVAL] Unsupported `command' (including unsupported-on-this-arch) */
__LIBC int __NOTHROW_NCX(__VLIBCCALL prctl)(__STDC_INT_AS_UINT_T __command, ...) __CASMNAME_SAME("prctl");
#endif /* __CRT_HAVE_prctl */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_PRCTL_H */
