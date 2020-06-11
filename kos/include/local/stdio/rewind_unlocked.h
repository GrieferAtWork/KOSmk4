/* HASH CRC-32:0x372aaf99 */
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
#ifndef __local_rewind_unlocked_defined
#define __local_rewind_unlocked_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_rewind) || defined(__CRT_HAVE_rewind_unlocked)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: rewind from stdio */
#ifndef __local___localdep_rewind_defined
#define __local___localdep_rewind_defined 1
#if defined(__CRT_HAVE_rewind_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Rewind the current in-file position of `STREAM' to its starting position */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,__localdep_rewind,(__FILE *__restrict __stream),rewind_unlocked,(__stream))
#elif defined(__CRT_HAVE_rewind)
/* Rewind the current in-file position of `STREAM' to its starting position */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,__localdep_rewind,(__FILE *__restrict __stream),rewind,(__stream))
#elif defined(__CRT_HAVE_rewind_unlocked)
/* Rewind the current in-file position of `STREAM' to its starting position */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,__localdep_rewind,(__FILE *__restrict __stream),rewind_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_rewind_defined
#endif /* !... */
#endif /* !__local___localdep_rewind_defined */
__LOCAL_LIBC(rewind_unlocked) __ATTR_NONNULL((1)) void
(__LIBCCALL __LIBC_LOCAL_NAME(rewind_unlocked))(__FILE *__restrict __stream) __THROWS(...) {
	__localdep_rewind(__stream);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rewind_unlocked_defined
#define __local___localdep_rewind_unlocked_defined 1
#define __localdep_rewind_unlocked __LIBC_LOCAL_NAME(rewind_unlocked)
#endif /* !__local___localdep_rewind_unlocked_defined */
#else /* __CRT_HAVE_rewind || __CRT_HAVE_rewind_unlocked */
#undef __local_rewind_unlocked_defined
#endif /* !__CRT_HAVE_rewind && !__CRT_HAVE_rewind_unlocked */
#endif /* !__local_rewind_unlocked_defined */
