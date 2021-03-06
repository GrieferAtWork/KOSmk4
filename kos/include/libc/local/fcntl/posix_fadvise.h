/* HASH CRC-32:0x5eab0f76 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_posix_fadvise_defined
#define __local_posix_fadvise_defined 1
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(__pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(__off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
/* Dependency: posix_fadvise32 from fcntl */
#if !defined(__local___localdep_posix_fadvise32_defined) && defined(__CRT_HAVE_posix_fadvise)
#define __local___localdep_posix_fadvise32_defined 1
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_posix_fadvise32,(__fd_t __fd, __off32_t __offset, __off32_t __length, __STDC_INT_AS_UINT_T __advise),posix_fadvise,(__fd,__offset,__length,__advise))
#endif /* !__local___localdep_posix_fadvise32_defined && __CRT_HAVE_posix_fadvise */
/* Dependency: posix_fadvise64 from fcntl */
#ifndef __local___localdep_posix_fadvise64_defined
#define __local___localdep_posix_fadvise64_defined 1
#ifdef __CRT_HAVE_posix_fadvise64
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_posix_fadvise64,(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length, __STDC_INT_AS_UINT_T __advise),posix_fadvise64,(__fd,__offset,__length,__advise))
#elif defined(__CRT_HAVE_posix_fadvise) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_posix_fadvise64,(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length, __STDC_INT_AS_UINT_T __advise),posix_fadvise,(__fd,__offset,__length,__advise))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/posix_fadvise64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_posix_fadvise64 __LIBC_LOCAL_NAME(posix_fadvise64)
#endif /* !... */
#endif /* !__local___localdep_posix_fadvise64_defined */
__LOCAL_LIBC(posix_fadvise) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_fadvise))(__fd_t __fd, __PIO_OFFSET __offset, __PIO_OFFSET __length, __STDC_INT_AS_UINT_T __advise) {

	return __localdep_posix_fadvise64(__fd, (__PIO_OFFSET64)__offset, (__PIO_OFFSET64)__length, __advise);









}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_fadvise_defined
#define __local___localdep_posix_fadvise_defined 1
#define __localdep_posix_fadvise __LIBC_LOCAL_NAME(posix_fadvise)
#endif /* !__local___localdep_posix_fadvise_defined */
#endif /* !__local_posix_fadvise_defined */
