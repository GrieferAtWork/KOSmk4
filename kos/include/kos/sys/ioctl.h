/* HASH CRC-32:0x7e236a6f */
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
#ifndef _KOS_SYS_IOCTL_H
#define _KOS_SYS_IOCTL_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <kos/anno.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <sys/ioctl.h>

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __Ioctl_defined
#define __Ioctl_defined 1
#ifdef __CRT_HAVE_Ioctl
/* Perform the I/O control operation specified by REQUEST on FD.
 * One argument may follow; its presence and type depend on REQUEST.
 * Return value depends on REQUEST. Usually -1 indicates error */
__LIBC __SSIZE_TYPE__ (__VLIBCCALL Ioctl)(__fd_t __fd, unsigned long int __request, ...) __THROWS(...) __CASMNAME_SAME("Ioctl");
#else /* LIBC: Ioctl */
#undef __Ioctl_defined
#endif /* Ioctl... */
#endif /* !__Ioctl_defined */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_KOS_SYS_IOCTL_H */
