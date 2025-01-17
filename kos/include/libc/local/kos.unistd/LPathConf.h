/* HASH CRC-32:0x71f100a1 */
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
#ifndef __local_LPathConf_defined
#define __local_LPathConf_defined
#include <__crt.h>
#include <asm/os/oflags.h>
#include <features.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_FPathConf) && (defined(__CRT_HAVE_Open64) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)) && defined(__O_RDONLY) && defined(__O_PATH) && defined(__O_NOFOLLOW)
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_FPathConf_defined
#define __local___localdep_FPathConf_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1),__LONGPTR_TYPE__,__THROWING(...),__localdep_FPathConf,(__fd_t __fd, __STDC_INT_AS_UINT_T __name),FPathConf,(__fd,__name))
#endif /* !__local___localdep_FPathConf_defined */
#ifndef __local___localdep_Open_defined
#define __local___localdep_Open_defined
#if defined(__CRT_HAVE_Open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__THROWING(...),__localdep_Open,(char const *__filename, __oflag_t __oflags),Open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_Open64) && (defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__THROWING(...),__localdep_Open,(char const *__filename, __oflag_t __oflags),Open64,(__filename,__oflags),__oflags,1,(__mode_t))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.fcntl/Open.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_Open __LIBC_LOCAL_NAME(Open)
#endif /* !... */
#endif /* !__local___localdep_Open_defined */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
__NAMESPACE_LOCAL_END
#include <kos/bits/except-compiler.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(LPathConf) __ATTR_IN(1) __LONGPTR_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(LPathConf))(char const *__path, __STDC_INT_AS_UINT_T __name) __THROWS(...) {
	__fd_t __fd;
	__LONGPTR_TYPE__ __result;
	__fd = (__NAMESPACE_LOCAL_SYM __localdep_Open)(__path, __O_RDONLY | __O_PATH | __O_NOFOLLOW | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
#if defined(__RAII_FINALLY) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close))
	__RAII_FINALLY { (void)(__NAMESPACE_LOCAL_SYM __localdep_close)(__fd); }
#endif /* __RAII_FINALLY && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_FPathConf)(__fd, __name);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_LPathConf_defined
#define __local___localdep_LPathConf_defined
#define __localdep_LPathConf __LIBC_LOCAL_NAME(LPathConf)
#endif /* !__local___localdep_LPathConf_defined */
#else /* __CRT_HAVE_FPathConf && (__CRT_HAVE_Open64 || (__AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt)) || __CRT_HAVE_Open) && __O_RDONLY && __O_PATH && __O_NOFOLLOW */
#undef __local_LPathConf_defined
#endif /* !__CRT_HAVE_FPathConf || (!__CRT_HAVE_Open64 && (!__AT_FDCWD || (!__CRT_HAVE_OpenAt64 && !__CRT_HAVE_OpenAt)) && !__CRT_HAVE_Open) || !__O_RDONLY || !__O_PATH || !__O_NOFOLLOW */
#endif /* !__local_LPathConf_defined */
