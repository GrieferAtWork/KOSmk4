/* HASH CRC-32:0x3113975a */
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
#ifndef __local_fgetpos_unlocked_defined
#define __local_fgetpos_unlocked_defined 1
#include <__crt.h>
#include <bits/crt/stdio.h>
#include <features.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fgetpos from stdio */
#ifndef __local___localdep_fgetpos_defined
#define __local___localdep_fgetpos_defined 1
#if defined(__CRT_HAVE_fgetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fgetpos,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fgetpos,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fgetpos,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fgetpos,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),_IO_fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fgetpos,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fgetpos,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fgetpos,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_fgetpos,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fgetpos.h>
__NAMESPACE_LOCAL_BEGIN
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
#define __localdep_fgetpos __LIBC_LOCAL_NAME(fgetpos)
#endif /* !... */
#endif /* !__local___localdep_fgetpos_defined */
__LOCAL_LIBC(fgetpos_unlocked) __ATTR_NONNULL((1, 2)) int
(__LIBCCALL __LIBC_LOCAL_NAME(fgetpos_unlocked))(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos) __THROWS(...) {
	return __localdep_fgetpos(__stream, __pos);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fgetpos_unlocked_defined
#define __local___localdep_fgetpos_unlocked_defined 1
#define __localdep_fgetpos_unlocked __LIBC_LOCAL_NAME(fgetpos_unlocked)
#endif /* !__local___localdep_fgetpos_unlocked_defined */
#else /* __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock */
#undef __local_fgetpos_unlocked_defined
#endif /* !__CRT_HAVE_fgetpos && !__CRT_HAVE__IO_fgetpos && !__CRT_HAVE_fgetpos_unlocked && !__CRT_HAVE_fgetpos64 && !__CRT_HAVE__IO_fgetpos64 && !__CRT_HAVE_fgetpos64_unlocked && !__CRT_HAVE_ftello64 && !__CRT_HAVE_ftell64 && !__CRT_HAVE__ftelli64 && !__CRT_HAVE_ftello64_unlocked && !__CRT_HAVE_ftell64_unlocked && !__CRT_HAVE__ftelli64_nolock && !__CRT_HAVE_ftello && !__CRT_HAVE_ftello_unlocked && !__CRT_HAVE_ftell && !__CRT_HAVE__IO_ftell && !__CRT_HAVE_ftell_unlocked && !__CRT_HAVE__ftell_nolock */
#endif /* !__local_fgetpos_unlocked_defined */
