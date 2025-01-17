/* HASH CRC-32:0x1a95dc00 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_freopen64_unlocked_defined
#define __local_freopen64_unlocked_defined
#include <__crt.h>
#include <features.h>
#include <asm/os/oflags.h>
#if (defined(__CRT_HAVE_freopen) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_freopen64) || (defined(__CRT_HAVE_freopen_unlocked) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_freopen64_unlocked)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_freopen64_defined
#define __local___localdep_freopen64_defined
#if defined(__CRT_HAVE_freopen_unlocked) && defined(__USE_STDIO_UNLOCKED) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_INOUT(3),__FILE *,__NOTHROW_RPC,__localdep_freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_INOUT(3),__FILE *,__NOTHROW_RPC,__localdep_freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_INOUT(3),__FILE *,__NOTHROW_RPC,__localdep_freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_INOUT(3),__FILE *,__NOTHROW_RPC,__localdep_freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen_unlocked) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_INOUT(3),__FILE *,__NOTHROW_RPC,__localdep_freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_INOUT(3),__FILE *,__NOTHROW_RPC,__localdep_freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#else /* ... */
#undef __local___localdep_freopen64_defined
#endif /* !... */
#endif /* !__local___localdep_freopen64_defined */
__LOCAL_LIBC(freopen64_unlocked) __ATTR_IN(1) __ATTR_IN(2) __ATTR_INOUT(3) __FILE *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(freopen64_unlocked))(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream) {
	return (__NAMESPACE_LOCAL_SYM __localdep_freopen64)(__filename, __modes, __stream);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_freopen64_unlocked_defined
#define __local___localdep_freopen64_unlocked_defined
#define __localdep_freopen64_unlocked __LIBC_LOCAL_NAME(freopen64_unlocked)
#endif /* !__local___localdep_freopen64_unlocked_defined */
#else /* (__CRT_HAVE_freopen && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_freopen64 || (__CRT_HAVE_freopen_unlocked && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_freopen64_unlocked */
#undef __local_freopen64_unlocked_defined
#endif /* (!__CRT_HAVE_freopen || (__O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_freopen64 && (!__CRT_HAVE_freopen_unlocked || (__O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_freopen64_unlocked */
#endif /* !__local_freopen64_unlocked_defined */
