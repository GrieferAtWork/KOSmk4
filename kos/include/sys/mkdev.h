/* HASH CRC-32:0xf3f7f4e9 */
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
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/mkdev.h) */
#ifndef _SYS_MKDEV_H
#define _SYS_MKDEV_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <asm/os/mkdev.h>
#include <hybrid/typecore.h>


/* Bad/invalid device number */
#if !defined(MKDEV_BADDEV) && defined(__MKDEV_BADDEV)
#define MKDEV_BADDEV __CCAST(dev_t)__MKDEV_BADDEV
#endif /* !MKDEV_BADDEV && __MKDEV_BADDEV */

/* First major device number for automatically assigned devno-s */
#if !defined(MKDEV_MAJOR_AUTO) && defined(__MKDEV_MAJOR_AUTO)
#define MKDEV_MAJOR_AUTO __CCAST(major_t)__MKDEV_MAJOR_AUTO
#endif /* !MKDEV_MAJOR_AUTO && __MKDEV_MAJOR_AUTO */


#ifdef __MKDEV_CURRENT_VERSION
/* # of significant bits in major_t */
#define MAJOR_BITS __MKDEV_MAJOR_BITS(__MKDEV_CURRENT_VERSION)

/* # of significant bits in minor_t */
#define MINOR_BITS __MKDEV_MINOR_BITS(__MKDEV_CURRENT_VERSION)

/* max value for major_t */
#if MAJOR_BITS == 8
#define MAJOR_MAX __UINT8_C(0xff)
#elif MAJOR_BITS == 16
#define MAJOR_MAX __UINT16_C(0xffff)
#elif MAJOR_BITS == 32
#define MAJOR_MAX __UINT32_C(0xffffffff)
#elif MAJOR_BITS == 44
#define MAJOR_MAX __UINT64_C(0x00000fffffffffff)
#elif MAJOR_BITS == 12
#define MAJOR_MAX __UINT16_C(0x0fff)
#elif MAJOR_BITS >= 32
#define MAJOR_MAX ((__UINT64_C(1) << MAJOR_BITS) - __UINT64_C(1))
#elif MAJOR_BITS >= 16
#define MAJOR_MAX ((__UINT32_C(1) << MAJOR_BITS) - __UINT32_C(1))
#else /* ... */
#define MAJOR_MAX ((__UINT16_C(1) << MAJOR_BITS) - __UINT16_C(1))
#endif /* !... */

/* max value for minor_t */
#if MINOR_BITS == 8
#define MINOR_MAX __UINT8_C(0xff)
#elif MINOR_BITS == 16
#define MINOR_MAX __UINT16_C(0xffff)
#elif MINOR_BITS == 32
#define MINOR_MAX __UINT32_C(0xffffffff)
#elif MINOR_BITS == 20
#define MINOR_MAX __UINT32_C(0x000fffff)
#elif MINOR_BITS >= 32
#define MINOR_MAX ((__UINT64_C(1) << MINOR_BITS) - __UINT64_C(1))
#elif MINOR_BITS >= 16
#define MINOR_MAX ((__UINT32_C(1) << MINOR_BITS) - __UINT32_C(1))
#else /* ... */
#define MINOR_MAX ((__UINT16_C(1) << MINOR_BITS) - __UINT16_C(1))
#endif /* !... */

/* Solaris names which I really don't like */
#ifndef __USE_KOS_PURE
#define NBITSMAJOR MAJOR_BITS
#define NBITSMINOR MINOR_BITS
#define MAXMAJ     MAJOR_MAX
#define MAXMIN     MINOR_MAX
#endif /* !__USE_KOS_PURE */
#endif /* __MKDEV_CURRENT_VERSION */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __dev_t_defined
#define __dev_t_defined
typedef __dev_t dev_t;
#endif /* !__dev_t_defined */

#ifndef __minor_t_defined
#define __minor_t_defined
typedef __minor_t minor_t;
#endif /* !__minor_t_defined */

#ifndef __major_t_defined
#define __major_t_defined
typedef __major_t major_t;
#endif /* !__major_t_defined */

#ifdef __CRT_HAVE_makedev
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,dev_t,__NOTHROW,makedev,(major_t __maj, minor_t __min),(__maj,__min))
#elif defined(__CRT_HAVE_gnu_dev_makedev)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,dev_t,__NOTHROW,makedev,(major_t __maj, minor_t __min),gnu_dev_makedev,(__maj,__min))
#elif defined(__MKDEV_CURRENT_VERSION)
#include <libc/local/sys.mkdev/makedev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(makedev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED dev_t __NOTHROW(__LIBCCALL makedev)(major_t __maj, minor_t __min) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(makedev))(__maj, __min); })
#endif /* ... */
#ifdef __CRT_HAVE_major
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,major_t,__NOTHROW,major,(dev_t __dev),(__dev))
#elif defined(__CRT_HAVE_gnu_dev_major)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,major_t,__NOTHROW,major,(dev_t __dev),gnu_dev_major,(__dev))
#elif defined(__MKDEV_CURRENT_VERSION)
#include <libc/local/sys.mkdev/major.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(major, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED major_t __NOTHROW(__LIBCCALL major)(dev_t __dev) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(major))(__dev); })
#endif /* ... */
#ifdef __CRT_HAVE_minor
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,minor_t,__NOTHROW,minor,(dev_t __dev),(__dev))
#elif defined(__CRT_HAVE_gnu_dev_minor)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,minor_t,__NOTHROW,minor,(dev_t __dev),gnu_dev_minor,(__dev))
#elif defined(__MKDEV_CURRENT_VERSION)
#include <libc/local/sys.mkdev/minor.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(minor, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED minor_t __NOTHROW(__LIBCCALL minor)(dev_t __dev) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(minor))(__dev); })
#endif /* ... */
#ifdef __CRT_HAVE___makedev
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,dev_t,__NOTHROW,__makedev,(int __version, major_t __maj, minor_t __min),(__version,__maj,__min))
#elif defined(__MKDEV_CURRENT_VERSION)
#include <libc/local/sys.mkdev/__makedev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__makedev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED dev_t __NOTHROW(__LIBCCALL __makedev)(int __version, major_t __maj, minor_t __min) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__makedev))(__version, __maj, __min); })
#endif /* ... */
#ifdef __CRT_HAVE___major
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,major_t,__NOTHROW,__major,(int __version, dev_t __dev),(__version,__dev))
#elif defined(__MKDEV_CURRENT_VERSION)
#include <libc/local/sys.mkdev/__major.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__major, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED major_t __NOTHROW(__LIBCCALL __major)(int __version, dev_t __dev) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__major))(__version, __dev); })
#endif /* ... */
#ifdef __CRT_HAVE___minor
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,minor_t,__NOTHROW,__minor,(int __version, dev_t __dev),(__version,__dev))
#elif defined(__MKDEV_CURRENT_VERSION)
#include <libc/local/sys.mkdev/__minor.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__minor, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED minor_t __NOTHROW(__LIBCCALL __minor)(int __version, dev_t __dev) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__minor))(__version, __dev); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

/* Provide macro implementations in kernel-space. */
#if defined(__MKDEV_CURRENT_VERSION) && defined(__KOS__) && defined(__KERNEL__)
#if __MKDEV_MINOR_SHFT(__MKDEV_CURRENT_VERSION) == 0
#define makedev(maj, min) \
	((__CCAST(dev_t)(maj) << __MKDEV_MAJOR_SHFT(__MKDEV_CURRENT_VERSION)) | __CCAST(dev_t)(min))
#else /* __MKDEV_MINOR_SHFT(__MKDEV_CURRENT_VERSION) == 0 */
#define makedev(maj, min)                                          \
	((__CCAST(dev_t)(maj) << __MKDEV_MAJOR_SHFT(__MKDEV_CURRENT_VERSION)) | \
	 (__CCAST(dev_t)(min) << __MKDEV_MINOR_SHFT(__MKDEV_CURRENT_VERSION)))
#endif /* __MKDEV_MINOR_SHFT(__MKDEV_CURRENT_VERSION) != 0 */
#if ((__MKDEV_MAJOR_SHFT(__MKDEV_CURRENT_VERSION) + __MKDEV_MAJOR_BITS(__MKDEV_CURRENT_VERSION)) == \
     (__SIZEOF_DEV_T__ * __CHAR_BIT__))
#define major(dev) \
	(__CCAST(major_t)((dev) >> __MKDEV_MAJOR_SHFT(__MKDEV_CURRENT_VERSION)))
#else /* ... */
#define major(dev)                                                            \
	(__CCAST(major_t)((dev) >> __MKDEV_MAJOR_SHFT(__MKDEV_CURRENT_VERSION)) & \
	 __CCAST(major_t)((__CCAST(major_t)1 << __MKDEV_MAJOR_BITS(__MKDEV_CURRENT_VERSION)) - 1))
#endif /* !... */
#if __MKDEV_MINOR_SHFT(__MKDEV_CURRENT_VERSION) == 0
#define minor(dev) \
	(__CCAST(minor_t)(dev) & __CCAST(minor_t)((__CCAST(minor_t)1 << __MKDEV_MINOR_BITS(__MKDEV_CURRENT_VERSION)) - 1))
#else /* ... */
#define minor(dev)                                                            \
	(__CCAST(minor_t)((dev) >> __MKDEV_MINOR_SHFT(__MKDEV_CURRENT_VERSION)) & \
	 __CCAST(minor_t)(((minor_t)1 << __MKDEV_MINOR_BITS(__MKDEV_CURRENT_VERSION)) - 1))
#endif /* !... */

#define __makedev(version, major, minor)                      \
	((__CCAST(dev_t)(major) << __MKDEV_MAJOR_SHFT(version)) | \
	 (__CCAST(dev_t)(minor) << __MKDEV_MINOR_SHFT(version)))
#define __major(version, dev)                                 \
	(__CCAST(major_t)((dev) >> __MKDEV_MAJOR_SHFT(version)) & \
	 __CCAST(major_t)(((major_t)1 << __MKDEV_MAJOR_BITS(version)) - 1))
#define __minor(version, dev)                                 \
	(__CCAST(minor_t)((dev) >> __MKDEV_MINOR_SHFT(version)) & \
	 __CCAST(minor_t)(((minor_t)1 << __MKDEV_MINOR_BITS(version)) - 1))
#endif /* __MKDEV_CURRENT_VERSION && __KOS__ && __KERNEL__ */

#endif /* !_SYS_MKDEV_H */
