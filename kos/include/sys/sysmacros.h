/* HASH CRC-32:0xbf01a6d7 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/sysmacros.h) */
/* (#) Portability: DJGPP         (/include/sys/sysmacros.h) */
/* (#) Portability: GNU C Library (/misc/sys/sysmacros.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sysmacros.h) */
/* (#) Portability: diet libc     (/include/sys/sysmacros.h) */
/* (#) Portability: libc4/5       (/include/sys/sysmacros.h) */
/* (#) Portability: mintlib       (/include/sys/sysmacros.h) */
/* (#) Portability: musl libc     (/include/sys/sysmacros.h) */
/* (#) Portability: uClibc        (/include/sys/sysmacros.h) */
#ifndef _SYS_SYSMACROS_H
#define _SYS_SYSMACROS_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_gnu_dev_major
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__major_t,__NOTHROW,gnu_dev_major,(__dev_t __dev),(__dev))
#else /* __CRT_HAVE_gnu_dev_major */
#include <libc/local/sys.sysmacros/gnu_dev_major.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gnu_dev_major, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __major_t __NOTHROW(__LIBCCALL gnu_dev_major)(__dev_t __dev) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gnu_dev_major))(__dev); })
#endif /* !__CRT_HAVE_gnu_dev_major */
#ifdef __CRT_HAVE_gnu_dev_minor
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__minor_t,__NOTHROW,gnu_dev_minor,(__dev_t __dev),(__dev))
#else /* __CRT_HAVE_gnu_dev_minor */
#include <libc/local/sys.sysmacros/gnu_dev_minor.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gnu_dev_minor, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __minor_t __NOTHROW(__LIBCCALL gnu_dev_minor)(__dev_t __dev) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gnu_dev_minor))(__dev); })
#endif /* !__CRT_HAVE_gnu_dev_minor */
#ifdef __CRT_HAVE_gnu_dev_makedev
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__dev_t,__NOTHROW,gnu_dev_makedev,(__major_t __major, __minor_t __minor),(__major,__minor))
#else /* __CRT_HAVE_gnu_dev_makedev */
#include <libc/local/sys.sysmacros/gnu_dev_makedev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gnu_dev_makedev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __dev_t __NOTHROW(__LIBCCALL gnu_dev_makedev)(__major_t __major, __minor_t __minor) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gnu_dev_makedev))(__major, __minor); })
#endif /* !__CRT_HAVE_gnu_dev_makedev */

/* Access the functions with their traditional names.  */
#define major(dev)        gnu_dev_major(dev)
#define minor(dev)        gnu_dev_minor(dev)
#define makedev(maj, min) gnu_dev_makedev(maj, min)

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_SYSMACROS_H */
