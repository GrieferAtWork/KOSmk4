/* HASH CRC-32:0x8e9e1b51 */
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
#ifndef __local_fsetpos_unlocked_defined
#define __local_fsetpos_unlocked_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fsetpos from stdio */
#ifndef __local___localdep_fsetpos_defined
#define __local___localdep_fsetpos_defined 1
#if defined(__CRT_HAVE_fsetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fsetpos,(__FILE *__restrict __stream, __FS_TYPE(pos) const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fsetpos,(__FILE *__restrict __stream, __FS_TYPE(pos) const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64) && defined(__USE_FILE_OFFSET64)
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fsetpos,(__FILE *__restrict __stream, __FS_TYPE(pos) const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) && !defined(__USE_FILE_OFFSET64)
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fsetpos,(__FILE *__restrict __stream, __FS_TYPE(pos) const *__restrict __pos),fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos) && !defined(__USE_FILE_OFFSET64)
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fsetpos,(__FILE *__restrict __stream, __FS_TYPE(pos) const *__restrict __pos),_IO_fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_LOCAL_END
#include <local/stdio/fsetpos.h>
__NAMESPACE_LOCAL_BEGIN
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
#define __localdep_fsetpos __LIBC_LOCAL_NAME(fsetpos)
#else /* ... */
#undef __local___localdep_fsetpos_defined
#endif /* !... */
#endif /* !__local___localdep_fsetpos_defined */
__LOCAL_LIBC(fsetpos_unlocked) __ATTR_NONNULL((1, 2)) int
(__LIBCCALL __LIBC_LOCAL_NAME(fsetpos_unlocked))(__FILE *__restrict __stream, __FS_TYPE(pos) const *__restrict __pos) __THROWS(...) {
	return __localdep_fsetpos(__stream, __pos);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fsetpos_unlocked_defined
#define __local___localdep_fsetpos_unlocked_defined 1
#define __localdep_fsetpos_unlocked __LIBC_LOCAL_NAME(fsetpos_unlocked)
#endif /* !__local___localdep_fsetpos_unlocked_defined */
#else /* __CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#undef __local_fsetpos_unlocked_defined
#endif /* !__CRT_HAVE_fseeko64 && !__CRT_HAVE_fseeko64_unlocked && !__CRT_HAVE__fseeki64_nolock && !__CRT_HAVE__fseeki64 && !__CRT_HAVE_fsetpos && !__CRT_HAVE__IO_fsetpos && !__CRT_HAVE_fsetpos_unlocked && !__CRT_HAVE_fsetpos64 && !__CRT_HAVE__IO_fsetpos64 && !__CRT_HAVE_fsetpos64_unlocked && !__CRT_HAVE_fseeko && !__CRT_HAVE_fseeko_unlocked && !__CRT_HAVE_fseek && !__CRT_HAVE_fseek_unlocked && !__CRT_HAVE__fseek_nolock */
#endif /* !__local_fsetpos_unlocked_defined */
