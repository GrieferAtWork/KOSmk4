/* HASH CRC-32:0xfe2084a6 */
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
#ifndef GUARD_LIBC_AUTO_LIBGEN_C
#define GUARD_LIBC_AUTO_LIBGEN_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "libgen.h"
#include "../user/string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Return the directory, that is everything leading up to, but not
 * including the last slash of `path'. If no such path exists, "."
 * is returned instead. Trailing slashes are ignored
 * >> dirname("/usr/include///"); // Returns "/usr"
 * >> dirname("/usr/include/");   // Returns "/usr"
 * >> dirname("/usr/include");    // Returns "/usr"
 * >> dirname("/usr/");           // Returns "/"
 * >> dirname("/usr");            // Returns "/"
 * >> dirname("/");               // Returns "/"
 * >> dirname("///");             // Returns "/"
 * >> dirname("foo/bar/");        // Returns "foo"
 * >> dirname("foo/bar");         // Returns "foo"
 * >> dirname("foo/");            // Returns "."
 * >> dirname("foo");             // Returns "."
 * >> dirname(".");               // Returns "."
 * >> dirname("..");              // Returns "."
 * >> dirname("");                // Returns "."
 * >> dirname(NULL);              // Returns "."
 * Note  that for this purpose, `path' may be modified in-place, meaning
 * that you should really always pass an strdup()'d, or writable string. */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_RETNONNULL char *
NOTHROW_NCX(LIBCCALL libc_dirname)(char *path) {
	char *iter;
	/* Handle the empty-path case. */
	if (!path || !*path)
		goto fallback;
	iter = libc_strend(path);
	for (;;) {
		--iter;
		if (*iter != '/')
			break;
		if (iter <= path) {
			/* String consists only of '/'-characters */
			return path;
		}
		/* Trim trailing slashes */
		*iter = '\0';
	}
	/* HINT: iter == strend(path) - 1; */
	for (;;) {
		if (iter < path)
			goto fallback;
		if (*iter == '/')
			break;
		--iter;
	}
	if (iter == path) {
		/* First character is the slash (e.g. "/foo/")
		 * Return "/" in this case! */
		++iter;
	}
	/* Delete the  slash character  (or  the one  after  the
	 * slash, if the only character left is a leading slash) */
	iter[0] = '\0';
	return path;
fallback:
	return (char *)".";
}
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
 * that  you should really  always pass an  strdup()'d, or writable string.
 *
 * Also note that a different version of this function exists in <string.h>,
 * where if you  include both  <libgen.h> and  <string.h>, you  can use  the
 * alternate function from <string.h>  by `#undef basename', or calling  the
 * function as `(basename)(...)' (as opposed to `basename(...)') */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_RETNONNULL char *
NOTHROW_NCX(LIBCCALL libc___xpg_basename)(char *filename) {
	char *iter;
	/* Handle the empty-path case. */
	if (!filename || !*filename)
		goto fallback;
	iter = libc_strend(filename);
	for (;;) {
		--iter;
		if (*iter != '/')
			break;
		if (iter <= filename) {
			/* String consists only of '/'-characters */
			return filename;
		}
		/* Trim trailing slashes */
		*iter = '\0';
	}
	/* HINT: iter == strend(path) - 1; */
	for (;;) {
		if (iter < filename)
			break;
		if (*iter == '/')
			break;
		--iter;
	}
	return iter + 1;
fallback:
	return (char *)".";
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(dirname, libc_dirname);
DEFINE_PUBLIC_ALIAS(__gnu_basename, libc___xpg_basename);
DEFINE_PUBLIC_ALIAS(__xpg_basename, libc___xpg_basename);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_LIBGEN_C */
