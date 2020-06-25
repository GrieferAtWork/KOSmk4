/* HASH CRC-32:0xf14ff901 */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _SYS_SIGNALFD_H
#define _SYS_SIGNALFD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <bits/sigset.h>
#include <bits/signalfd.h>
#include <bits/signalfd_siginfo.h>

#ifdef __USE_GLIBC
#include <stdint.h>
#endif /* __USE_GLIBC */

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef __sigset_t sigset_t;
#endif /* !__sigset_t_defined */

/* Request notification for delivery of signals in MASK to be performed using descriptor FD */
__CDECLARE_OPT(__ATTR_NONNULL((2)),__fd_t,__NOTHROW_NCX,signalfd,(__fd_t __fd, sigset_t const *__mask, __STDC_INT_AS_UINT_T __flags),(__fd,__mask,__flags))
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_SIGNALFD_H */
