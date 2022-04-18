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
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/sysmacros.h) */
/* (#) Portability: DJGPP         (/include/sys/sysmacros.h) */
/* (#) Portability: GNU C Library (/misc/sys/sysmacros.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sysmacros.h) */
/* (#) Portability: diet libc     (/include/sys/sysmacros.h) */
/* (#) Portability: libc4/5       (/include/sys/sysmacros.h) */
/* (#) Portability: mintlib       (/include/sys/sysmacros.h) */
/* (#) Portability: musl libc     (/include/sys/sysmacros.h) */
/* (#) Portability: uClibc        (/include/sys/sysmacros.h) */
}

%[define_replacement(major_t = __major_t)]
%[define_replacement(minor_t = __minor_t)]
%[define_replacement(dev_t = __dev_t)]
%[default:section(".text.crt{|.dos}.system.utility")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

[[const, wunused, nothrow, decl_include("<bits/types.h>")]]
$major_t gnu_dev_major($dev_t dev) {
	return (major_t)((uintptr_t)dev >> 20);
}

[[const, wunused, nothrow, decl_include("<bits/types.h>")]]
$minor_t gnu_dev_minor($dev_t dev) {
	return (minor_t)((uintptr_t)dev & ((1 << 20) - 1));
}

[[const, wunused, nothrow, decl_include("<bits/types.h>")]]
$dev_t gnu_dev_makedev($major_t major, $minor_t minor) {
	return (dev_t)major << 20 | (dev_t)minor;
}

%{

/* Access the functions with their traditional names.  */
#define major(dev)        gnu_dev_major(dev)
#define minor(dev)        gnu_dev_minor(dev)
#define makedev(maj, min) gnu_dev_makedev(maj, min)

__SYSDECL_END
#endif /* __CC__ */

}
