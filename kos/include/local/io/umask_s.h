/* HASH CRC-32:0x34b40a5b */
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
#ifndef __local_umask_s_defined
#if defined(__CRT_HAVE_umask) || defined(__CRT_HAVE__umask)
#define __local_umask_s_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <parts/errno.h>
/* Dependency: "umask" */
#ifndef ____localdep_umask_defined
#define ____localdep_umask_defined 1
#ifdef __CRT_HAVE_umask
__CREDIRECT(,__mode_t,__NOTHROW_NCX,__localdep_umask,(__mode_t __mode),umask,(__mode))
#elif defined(__CRT_HAVE__umask)
__CREDIRECT(,__mode_t,__NOTHROW_NCX,__localdep_umask,(__mode_t __mode),_umask,(__mode))
#else /* LIBC: umask */
#undef ____localdep_umask_defined
#endif /* umask... */
#endif /* !____localdep_umask_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(umask_s) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(umask_s))(__mode_t __newmode,
                                                     __mode_t *__oldmode) {
#line 305 "kos/src/libc/magic/io.c"
	if (!__oldmode) {
#ifdef __EINVAL
		return __EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	*__oldmode = __localdep_umask(__newmode);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_umask || __CRT_HAVE__umask */
#endif /* !__local_umask_s_defined */
