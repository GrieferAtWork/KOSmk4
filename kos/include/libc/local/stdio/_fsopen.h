/* HASH CRC-32:0x4fadc76f */
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
#ifndef __local__fsopen_defined
#define __local__fsopen_defined
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
__LOCAL_LIBC(_fsopen) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __FILE *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_fsopen))(char const *__filename, char const *__modes, __STDC_INT_AS_UINT_T __sflag) {
	(void)__sflag;
	return (__NAMESPACE_LOCAL_SYM __localdep_fopen)(__filename, __modes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__fsopen_defined
#define __local___localdep__fsopen_defined
#define __localdep__fsopen __LIBC_LOCAL_NAME(_fsopen)
#endif /* !__local___localdep__fsopen_defined */
#else /* (__CRT_HAVE_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE__IO_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_fopen64 */
#undef __local__fsopen_defined
#endif /* (!__CRT_HAVE_fopen || (__USE_FILE_OFFSET64 && __O_LARGEFILE && __O_LARGEFILE)) && (!__CRT_HAVE__IO_fopen || (__USE_FILE_OFFSET64 && __O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_fopen64 */
#endif /* !__local__fsopen_defined */
