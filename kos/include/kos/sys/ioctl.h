/* HASH CRC-32:0x48313062 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_SYS_IOCTL_H
#define _KOS_SYS_IOCTL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <sys/ioctl.h>

#ifdef __CC__
__SYSDECL_BEGIN

#if !defined(__Ioctl_defined) && defined(__CRT_HAVE_Ioctl)
#define __Ioctl_defined
/* >> ioctl(2)
 * Perform the  I/O control  operation specified  by `request'  on  `fd'.
 * Many I/O  control operations  except  an additional  argument,  though
 * this argument's type and meaning  depends on `REQUEST'. If used,  it's
 * usually either a pointer to a larger argument structure, or an integer
 * that fits into a single register.
 * @return: * : The return value depends on the given `request'.
 * @return: 0 : A zero return-value usually indicates success.
 * @return: -1: All ioctl operations use this to indicate error (s.a. `errno') */
__LIBC __SSIZE_TYPE__ (__VLIBCCALL Ioctl)(__fd_t __fd, unsigned long int __request, ...) __THROWS(...) __CASMNAME_SAME("Ioctl");
#endif /* !__Ioctl_defined && __CRT_HAVE_Ioctl */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_SYS_IOCTL_H */
