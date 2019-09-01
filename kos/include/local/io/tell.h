/* HASH 0x1675d1db */
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
#ifndef __local_tell_defined
#if (defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64))
#define __local_tell_defined 1
#include <bits/types.h>
#include <bits/types.h>
/* Dependency: "_lseek" from "io" */
#ifndef ____localdep__lseek_defined
#define ____localdep__lseek_defined 1
#if defined(__CRT_HAVE__lseek)
__CREDIRECT(,__LONG32_TYPE__,__NOTHROW_NCX,__localdep__lseek,(__fd_t __fd, __LONG32_TYPE__ __offset, int __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek)
__CREDIRECT(,__LONG32_TYPE__,__NOTHROW_NCX,__localdep__lseek,(__fd_t __fd, __LONG32_TYPE__ __offset, int __whence),lseek,(__fd,__offset,__whence))
#elif (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64))
#include <local/io/_lseek.h>
#define __localdep__lseek (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lseek))
#else /* CUSTOM: _lseek */
#undef ____localdep__lseek_defined
#endif /* _lseek... */
#endif /* !____localdep__lseek_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tell) __ATTR_WUNUSED __LONG32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tell))(__fd_t __fd) {
#line 352 "kos/src/libc/magic/io.c"
	return __localdep__lseek(__fd, 0, 1);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)) */
#endif /* !__local_tell_defined */
