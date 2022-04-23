/* HASH CRC-32:0x1f26aec */
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
#ifndef __local_basename_defined
#define __local_basename_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(basename) __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(basename))(char const *__filename) {
	/* >> char *slash = strrchr(filename, '/');
	 * >> return slash ? slash + 1 : (char *)filename; */
	char *__result, *__iter = (char *)__filename;
#ifdef _WIN32
	/* Skip drive letter. */
	if (((__iter[0] >= 'A' && __iter[0] <= 'Z') ||
	     (__iter[0] >= 'a' && __iter[0] <= 'z')) &&
	    __iter[1] == ':')
		__iter += 2;
#endif /* _WIN32 */
	__result = __iter;
	for (;;) {
		char __ch = *__iter++;
#ifdef _WIN32
		if (__ch == '/' || __ch == '\\')
#else /* _WIN32 */
		if (__ch == '/')
#endif /* !_WIN32 */
		{
			__result = __iter;
		}
		if (!__ch)
			break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_basename_defined
#define __local___localdep_basename_defined
#define __localdep_basename __LIBC_LOCAL_NAME(basename)
#endif /* !__local___localdep_basename_defined */
#endif /* !__local_basename_defined */
