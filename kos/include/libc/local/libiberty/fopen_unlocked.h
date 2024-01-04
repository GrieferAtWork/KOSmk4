/* HASH CRC-32:0xa40077e8 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fopen_unlocked_defined
#define __local_fopen_unlocked_defined
#include <__crt.h>
#include <features.h>
#include <asm/os/oflags.h>
#if (defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_fopen64)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fopen_defined
#define __local___localdep_fopen_defined
#if defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen,(__filename,__modes))
#elif defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),_IO_fopen,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen64,(__filename,__modes))
#else /* ... */
#undef __local___localdep_fopen_defined
#endif /* !... */
#endif /* !__local___localdep_fopen_defined */
#ifndef __local___localdep_unlock_stream_defined
#define __local___localdep_unlock_stream_defined
#ifdef __CRT_HAVE_unlock_stream
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_unlock_stream,(__FILE *__fp),unlock_stream,(__fp))
#else /* __CRT_HAVE_unlock_stream */
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/unlock_stream.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unlock_stream __LIBC_LOCAL_NAME(unlock_stream)
#endif /* !__CRT_HAVE_unlock_stream */
#endif /* !__local___localdep_unlock_stream_defined */
__LOCAL_LIBC(fopen_unlocked) __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fopen_unlocked))(char const *__filename, char const *__mode) {
	__FILE *__result = (__NAMESPACE_LOCAL_SYM __localdep_fopen)(__filename, __mode);
	if (__result)
		(__NAMESPACE_LOCAL_SYM __localdep_unlock_stream)(__result);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fopen_unlocked_defined
#define __local___localdep_fopen_unlocked_defined
#define __localdep_fopen_unlocked __LIBC_LOCAL_NAME(fopen_unlocked)
#endif /* !__local___localdep_fopen_unlocked_defined */
#else /* (__CRT_HAVE_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE__IO_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_fopen64 */
#undef __local_fopen_unlocked_defined
#endif /* (!__CRT_HAVE_fopen || (__USE_FILE_OFFSET64 && __O_LARGEFILE && __O_LARGEFILE)) && (!__CRT_HAVE__IO_fopen || (__USE_FILE_OFFSET64 && __O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_fopen64 */
#endif /* !__local_fopen_unlocked_defined */
