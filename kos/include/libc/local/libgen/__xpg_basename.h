/* HASH CRC-32:0x4b24a301 */
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
#ifndef __local___xpg_basename_defined
#define __local___xpg_basename_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strend from string */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined 1
#ifdef __CRT_HAVE_strend
/* Same as `str + strlen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `str + strlen(str)' */
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
/* Return the filename-part, that is everything following
 * the last slash of `filename'. If no such part exists, "."
 * is returned instead. Trailing slashes are ignored
 * >> basename("/usr/include///"); // Returns "include"
 * >> basename("/usr/include/");   // Returns "include"
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns "usr"
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns "/"
 * >> basename("///");             // Returns "/"
 * >> basename("foo/bar/");        // Returns "bar"
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns "foo"
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns "."
 * >> basename(NULL);              // Returns "."
 * Note that for this purpose, `filename' may be modified in-place, meaning
 * that you should really always pass an strdup()'d, or writable string.
 *
 * Also note that a different version of this function exists in <string.h>,
 * where if you include both <libgen.h> and <string.h>, you can use the
 * alternate function from <string.h> by `#undef basename', or calling the
 * function as `(basename)(...)' (as opposed to `basename(...)') */
__LOCAL_LIBC(__xpg_basename) __ATTR_RETNONNULL char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__xpg_basename))(char *__filename) {
	char *__iter;
	/* Handle the empty-path case. */
	if (!__filename || !*__filename)
		goto __fallback;
	__iter = __localdep_strend(__filename);
	for (;;) {
		--__iter;
		if (*__iter != '/')
			break;
		if (__iter <= __filename) {
			/* String consists only of '/'-characters */
			return __filename;
		}
		/* Trim trailing slashes */
		*__iter = '\0';
	}
	/* HINT: iter == strend(path) - 1; */
	for (;;) {
		if (__iter < __filename)
			break;
		if (*__iter == '/')
			break;
		--__iter;
	}
	return __iter + 1;
__fallback:
	return (char *)".";
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___xpg_basename_defined
#define __local___localdep___xpg_basename_defined 1
#define __localdep___xpg_basename __LIBC_LOCAL_NAME(__xpg_basename)
#endif /* !__local___localdep___xpg_basename_defined */
#endif /* !__local___xpg_basename_defined */
