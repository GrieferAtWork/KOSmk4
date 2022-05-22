/* HASH CRC-32:0x4e857232 */
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
#ifndef __local__fullpath_dbg_defined
#define __local__fullpath_dbg_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE__fullpath) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__fullpath_defined
#define __local___localdep__fullpath_defined
#ifdef __CRT_HAVE__fullpath
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(1, 3),char *,__NOTHROW_RPC,__localdep__fullpath,(char *__buf, char const *__path, __SIZE_TYPE__ __buflen),_fullpath,(__buf,__path,__buflen))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_fullpath.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__fullpath __LIBC_LOCAL_NAME(_fullpath)
#else /* ... */
#undef __local___localdep__fullpath_defined
#endif /* !... */
#endif /* !__local___localdep__fullpath_defined */
__LOCAL_LIBC(_fullpath_dbg) __ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(1, 3) char *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_fullpath_dbg))(char *__full_path, char const *__path, __SIZE_TYPE__ __bufsize, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__NAMESPACE_LOCAL_SYM __localdep__fullpath)(__full_path, __path, __bufsize);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__fullpath_dbg_defined
#define __local___localdep__fullpath_dbg_defined
#define __localdep__fullpath_dbg __LIBC_LOCAL_NAME(_fullpath_dbg)
#endif /* !__local___localdep__fullpath_dbg_defined */
#else /* __CRT_HAVE__fullpath || (__AT_FDCWD && __CRT_HAVE_frealpathat) */
#undef __local__fullpath_dbg_defined
#endif /* !__CRT_HAVE__fullpath && (!__AT_FDCWD || !__CRT_HAVE_frealpathat) */
#endif /* !__local__fullpath_dbg_defined */
