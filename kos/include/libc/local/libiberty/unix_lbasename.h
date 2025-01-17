/* HASH CRC-32:0xdb9e34f */
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
#ifndef __local_unix_lbasename_defined
#define __local_unix_lbasename_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_basename_defined
#define __local___localdep_basename_defined
#ifdef __CRT_HAVE_basename
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_basename,(char const *__filename),basename,(__filename))
#elif defined(__CRT_HAVE___basename)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_basename,(char const *__filename),__basename,(__filename))
#elif defined(__CRT_HAVE_lbasename)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_basename,(char const *__filename),lbasename,(__filename))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/basename.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_basename __LIBC_LOCAL_NAME(basename)
#endif /* !... */
#endif /* !__local___localdep_basename_defined */
__LOCAL_LIBC(unix_lbasename) __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unix_lbasename))(char const *__filename) {
#ifndef _WIN32
	return (__NAMESPACE_LOCAL_SYM __localdep_basename)(__filename);
#else /* !_WIN32 */
	/* >> char *slash = strrchr(filename, '/');
	 * >> return slash ? slash + 1 : (char *)filename; */
	char *__result, *__iter = (char *)__filename;
	__result = __iter;
	for (;;) {
		char __ch = *__iter++;
		if (__ch == '/')
			__result = __iter;
		if (!__ch)
			break;
	}
	return __result;
#endif /* _WIN32 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unix_lbasename_defined
#define __local___localdep_unix_lbasename_defined
#define __localdep_unix_lbasename __LIBC_LOCAL_NAME(unix_lbasename)
#endif /* !__local___localdep_unix_lbasename_defined */
#endif /* !__local_unix_lbasename_defined */
