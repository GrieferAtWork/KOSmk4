/* HASH CRC-32:0xad19ad9f */
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
#ifndef __local_dirname_defined
#define __local_dirname_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__LOCAL_LIBC(dirname) __ATTR_RETNONNULL __ATTR_ACCESS_RO_OPT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dirname))(char *__path) {
	char *__iter;
	/* Handle the empty-path case. */
	if (!__path || !*__path)
		goto __fallback;
	__iter = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__path);
	for (;;) {
		--__iter;
		if (*__iter != '/')
			break;
		if (__iter <= __path) {
			/* String consists only of '/'-characters */
			return __path;
		}
		/* Trim trailing slashes */
		*__iter = '\0';
	}
	/* HINT: iter == strend(path) - 1; */
	for (;;) {
		if (__iter < __path)
			goto __fallback;
		if (*__iter == '/')
			break;
		--__iter;
	}
	if (__iter == __path) {
		/* First character is the slash (e.g. "/foo/")
		 * Return "/" in this case! */
		++__iter;
	}
	/* Delete the  slash character  (or  the one  after  the
	 * slash, if the only character left is a leading slash) */
	__iter[0] = '\0';
	return __path;
__fallback:
	return (char *)".";
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dirname_defined
#define __local___localdep_dirname_defined
#define __localdep_dirname __LIBC_LOCAL_NAME(dirname)
#endif /* !__local___localdep_dirname_defined */
#endif /* !__local_dirname_defined */
