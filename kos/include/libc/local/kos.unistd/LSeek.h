/* HASH CRC-32:0xd4af27cf */
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
#ifndef __local_LSeek_defined
#define __local_LSeek_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_LSeek64) || defined(__CRT_HAVE_LSeek)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_LSeek64_defined
#define __local___localdep_LSeek64_defined
#if defined(__CRT_HAVE_LSeek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(,__pos64_t,__THROWING(...),__localdep_LSeek64,(__fd_t __fd, __off64_t __offset, int __whence),LSeek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_LSeek64)
__CREDIRECT(,__pos64_t,__THROWING(...),__localdep_LSeek64,(__fd_t __fd, __off64_t __offset, int __whence),LSeek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_LSeek)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.unistd/LSeek64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_LSeek64 __LIBC_LOCAL_NAME(LSeek64)
#else /* ... */
#undef __local___localdep_LSeek64_defined
#endif /* !... */
#endif /* !__local___localdep_LSeek64_defined */
#if !defined(__local___localdep_crt_LSeek32_defined) && defined(__CRT_HAVE_LSeek)
#define __local___localdep_crt_LSeek32_defined
__CREDIRECT(,__pos32_t,__THROWING(...),__localdep_crt_LSeek32,(__fd_t __fd, __off32_t __offset, int __whence),LSeek,(__fd,__offset,__whence))
#endif /* !__local___localdep_crt_LSeek32_defined && __CRT_HAVE_LSeek */
__LOCAL_LIBC(LSeek) __pos_t
(__LIBCCALL __LIBC_LOCAL_NAME(LSeek))(__fd_t __fd, __off_t __offset, int __whence) __THROWS(...) {
#ifdef __CRT_HAVE_LSeek
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_LSeek32)(__fd, (__off32_t)__offset, __whence);
#else /* __CRT_HAVE_LSeek */
	return (__NAMESPACE_LOCAL_SYM __localdep_LSeek64)(__fd, (__off64_t)__offset, __whence);
#endif /* !__CRT_HAVE_LSeek */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_LSeek_defined
#define __local___localdep_LSeek_defined
#define __localdep_LSeek __LIBC_LOCAL_NAME(LSeek)
#endif /* !__local___localdep_LSeek_defined */
#else /* __CRT_HAVE_LSeek64 || __CRT_HAVE_LSeek */
#undef __local_LSeek_defined
#endif /* !__CRT_HAVE_LSeek64 && !__CRT_HAVE_LSeek */
#endif /* !__local_LSeek_defined */
