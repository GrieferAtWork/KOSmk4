/* HASH CRC-32:0xb5fc299c */
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
#ifndef __local_ftello_unlocked_defined
#define __local_ftello_unlocked_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_ftello64) && defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: ftello from stdio */
#ifndef __local___localdep_ftello_defined
#define __local___localdep_ftello_defined 1
#if defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,__localdep_ftello,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,__localdep_ftello,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,__localdep_ftello,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && ((defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,__localdep_ftello,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && ((defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,__localdep_ftello,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello64) && defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,__localdep_ftello,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,__localdep_ftello,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftello) && !defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,__localdep_ftello,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftell) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,__localdep_ftello,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,__localdep_ftello,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
__NAMESPACE_LOCAL_END
#include <local/stdio/ftello.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the current in-file position of `STREAM' */
#define __localdep_ftello __LIBC_LOCAL_NAME(ftello)
#else /* ... */
#undef __local___localdep_ftello_defined
#endif /* !... */
#endif /* !__local___localdep_ftello_defined */
__LOCAL_LIBC(ftello_unlocked) __ATTR_NONNULL((1)) __FS_TYPE(off)
(__LIBCCALL __LIBC_LOCAL_NAME(ftello_unlocked))(__FILE *__restrict __stream) __THROWS(...) {
	return __localdep_ftello(__stream);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ftello_unlocked_defined
#define __local___localdep_ftello_unlocked_defined 1
#define __localdep_ftello_unlocked __LIBC_LOCAL_NAME(ftello_unlocked)
#endif /* !__local___localdep_ftello_unlocked_defined */
#else /* (__CRT_HAVE_ftello64 && __USE_FILE_OFFSET64) || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock || __CRT_HAVE__IO_ftell */
#undef __local_ftello_unlocked_defined
#endif /* (!__CRT_HAVE_ftello64 || !__USE_FILE_OFFSET64) && !__CRT_HAVE_fgetpos64 && !__CRT_HAVE__IO_fgetpos64 && !__CRT_HAVE_fgetpos64_unlocked && !__CRT_HAVE_fgetpos && !__CRT_HAVE__IO_fgetpos && !__CRT_HAVE_fgetpos_unlocked && !__CRT_HAVE_ftello && !__CRT_HAVE_ftello64_unlocked && !__CRT_HAVE__ftelli64_nolock && !__CRT_HAVE__ftelli64 && !__CRT_HAVE_ftello_unlocked && !__CRT_HAVE_ftell && !__CRT_HAVE_ftell_unlocked && !__CRT_HAVE__ftell_nolock && !__CRT_HAVE__IO_ftell */
#endif /* !__local_ftello_unlocked_defined */
