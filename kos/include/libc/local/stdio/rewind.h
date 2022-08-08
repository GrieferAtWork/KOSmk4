/* HASH CRC-32:0x65332955 */
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
#ifndef __local_rewind_defined
#define __local_rewind_defined
#include <__crt.h>
#include <asm/os/stdio.h>
#include <features.h>
#include <bits/types.h>
#if defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fseeko_defined
#define __local___localdep_fseeko_defined
#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && __SIZEOF_OFF_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fseeko,(__FILE *__restrict __stream, __off_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fseeko.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fseeko __LIBC_LOCAL_NAME(fseeko)
#endif /* !... */
#endif /* !__local___localdep_fseeko_defined */
__LOCAL_LIBC(rewind) __ATTR_INOUT(1) void
(__LIBCCALL __LIBC_LOCAL_NAME(rewind))(__FILE *__restrict __stream) __THROWS(...) {
	(__NAMESPACE_LOCAL_SYM __localdep_fseeko)(__stream, 0, __SEEK_SET);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rewind_defined
#define __local___localdep_rewind_defined
#define __localdep_rewind __LIBC_LOCAL_NAME(rewind)
#endif /* !__local___localdep_rewind_defined */
#else /* __SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock) */
#undef __local_rewind_defined
#endif /* !__SEEK_SET || (!__CRT_HAVE_fseeko64 && !__CRT_HAVE_fseek64 && !__CRT_HAVE__fseeki64 && !__CRT_HAVE_fseeko64_unlocked && !__CRT_HAVE_fseek64_unlocked && !__CRT_HAVE__fseeki64_nolock && !__CRT_HAVE_fseeko && !__CRT_HAVE_fseeko_unlocked && !__CRT_HAVE_fseek && !__CRT_HAVE_fseek_unlocked && !__CRT_HAVE__fseek_nolock) */
#endif /* !__local_rewind_defined */
