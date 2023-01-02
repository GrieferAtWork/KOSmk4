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
%(c_prefix){
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/mkdev.h) */
}

%[define_replacement(major_t = __major_t)]
%[define_replacement(minor_t = __minor_t)]
%[define_replacement(dev_t = __dev_t)]
%[default:section(".text.crt{|.dos}.system.utility")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <asm/os/mkdev.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{


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

}

[[const, wunused, nothrow, decl_include("<bits/types.h>")]]
[[export_alias("gnu_dev_makedev")]]
[[requires_include("<asm/os/mkdev.h>")]]
[[requires(defined(__MKDEV_CURRENT_VERSION))]]
dev_t makedev(major_t maj, minor_t min) {
	return ((dev_t)maj << __MKDEV_MAJOR_SHFT(__MKDEV_CURRENT_VERSION)) |
	       ((dev_t)min << __MKDEV_MINOR_SHFT(__MKDEV_CURRENT_VERSION));
}

[[const, wunused, nothrow, decl_include("<bits/types.h>")]]
[[export_alias("gnu_dev_major")]]
[[requires_include("<asm/os/mkdev.h>")]]
[[requires(defined(__MKDEV_CURRENT_VERSION))]]
major_t major(dev_t dev) {
	return (major_t)(dev >> __MKDEV_MAJOR_SHFT(__MKDEV_CURRENT_VERSION)) &
	       (major_t)(((major_t)1 << __MKDEV_MAJOR_BITS(__MKDEV_CURRENT_VERSION)) - 1);
}

[[const, wunused, nothrow, decl_include("<bits/types.h>")]]
[[export_alias("gnu_dev_minor")]]
[[requires_include("<asm/os/mkdev.h>")]]
[[requires(defined(__MKDEV_CURRENT_VERSION))]]
minor_t minor(dev_t dev) {
	return (minor_t)(dev >> __MKDEV_MINOR_SHFT(__MKDEV_CURRENT_VERSION)) &
	       (minor_t)(((minor_t)1 << __MKDEV_MINOR_BITS(__MKDEV_CURRENT_VERSION)) - 1);
}



[[const, wunused, nothrow, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/mkdev.h>")]]
[[requires(defined(__MKDEV_CURRENT_VERSION))]]
dev_t __makedev(int version, major_t maj, minor_t min) {
	(void)version;
	return ((dev_t)maj << __MKDEV_MAJOR_SHFT(version)) |
	       ((dev_t)min << __MKDEV_MINOR_SHFT(version));
}

[[const, wunused, nothrow, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/mkdev.h>")]]
[[requires(defined(__MKDEV_CURRENT_VERSION))]]
major_t __major(int version, dev_t dev) {
	(void)version;
	return (major_t)(dev >> __MKDEV_MAJOR_SHFT(version)) &
	       (major_t)(((major_t)1 << __MKDEV_MAJOR_BITS(version)) - 1);
}

[[const, wunused, nothrow, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/mkdev.h>")]]
[[requires(defined(__MKDEV_CURRENT_VERSION))]]
minor_t __minor(int version, dev_t dev) {
	(void)version;
	return (minor_t)(dev >> __MKDEV_MINOR_SHFT(version)) &
	       (minor_t)(((minor_t)1 << __MKDEV_MINOR_BITS(version)) - 1);
}


%{

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

#define __makedev(version, maj, min)                        \
	((__CCAST(dev_t)(maj) << __MKDEV_MAJOR_SHFT(version)) | \
	 (__CCAST(dev_t)(min) << __MKDEV_MINOR_SHFT(version)))
#define __major(version, dev)                                 \
	(__CCAST(major_t)((dev) >> __MKDEV_MAJOR_SHFT(version)) & \
	 __CCAST(major_t)(((major_t)1 << __MKDEV_MAJOR_BITS(version)) - 1))
#define __minor(version, dev)                                 \
	(__CCAST(minor_t)((dev) >> __MKDEV_MINOR_SHFT(version)) & \
	 __CCAST(minor_t)(((minor_t)1 << __MKDEV_MINOR_BITS(version)) - 1))
#endif /* __MKDEV_CURRENT_VERSION && __KOS__ && __KERNEL__ */


/* Some programs think that unless macros `minor', `major' and `makedev' have  been
 * defined, the `dev_t'-API won't be available. Since on KOS, we also try to define
 * these  functions as... well: functions, we still  have define the macros so that
 * `#ifdef minor'-style checks can be used
 *
 * Example: MC (midnight commander) (/lib/unixcompat.h:26-39)
 */
}
%[insert:pp_if(!defined(@minor@) && $has_function(minor))]
%#define minor(dev) minor(dev)
%[insert:pp_endif]
%[insert:pp_if(!defined(@major@) && $has_function(major))]
%#define major(dev) major(dev)
%[insert:pp_endif]
%[insert:pp_if(!defined(@makedev@) && $has_function(makedev))]
%#define makedev(maj, min) makedev(maj, min)
%[insert:pp_endif]
%{

}
