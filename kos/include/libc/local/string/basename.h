/* HASH CRC-32:0x9d780709 */
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
#ifndef __local_basename_defined
#define __local_basename_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific basename() function (you can explicitly make use of this GNU
 * version by doing `#undef basename', or writing `(basename)(filename)', as
 * opposed to `basename(filename)', when both version have been defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__LOCAL_LIBC(basename) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(basename))(char const *__filename) {
	/* char  *slash   =   strrchr(filename,   '/');
	 * return slash ? slash + 1 : (char *)filename; */
	char *__result = (char *)__filename;
	char *__iter   = (char *)__filename;
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
#define __local___localdep_basename_defined 1
#define __localdep_basename __LIBC_LOCAL_NAME(basename)
#endif /* !__local___localdep_basename_defined */
#endif /* !__local_basename_defined */
