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
%(c_prefix){
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/libgen.h) */
/* (#) Portability: FreeBSD       (/include/libgen.h) */
/* (#) Portability: GNU C Library (/misc/libgen.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/libgen.h) */
/* (#) Portability: NetBSD        (/include/libgen.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/libgen.h) */
/* (#) Portability: OpenBSD       (/include/libgen.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/libgen.h) */
/* (#) Portability: diet libc     (/include/libgen.h) */
/* (#) Portability: musl libc     (/include/libgen.h) */
/* (#) Portability: uClibc        (/include/libgen.h) */
}

%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

@@Return the directory, that is everything leading up to, but not
@@including the last slash of `path'. If no such path exists, "."
@@is returned instead. Trailing slashes are ignored
@@>> dirname("/usr/include///"); // Returns "/usr"
@@>> dirname("/usr/include/");   // Returns "/usr"
@@>> dirname("/usr/include");    // Returns "/usr"
@@>> dirname("/usr/");           // Returns "/"
@@>> dirname("/usr");            // Returns "/"
@@>> dirname("/");               // Returns "/"
@@>> dirname("///");             // Returns "/"
@@>> dirname("foo/bar/");        // Returns "foo"
@@>> dirname("foo/bar");         // Returns "foo"
@@>> dirname("foo/");            // Returns "."
@@>> dirname("foo");             // Returns "."
@@>> dirname(".");               // Returns "."
@@>> dirname("..");              // Returns "."
@@>> dirname("");                // Returns "."
@@>> dirname(NULL);              // Returns "."
@@Note that for this purpose, `path' may be modified in-place, meaning
@@that you should really always pass an strdup()'d, or writable string.
[[nonnull]] char *dirname([[nullable]] char *path) {
	char *iter;
	/* Handle the empty-path case. */
	if (!path || !*path)
		goto fallback;
	iter = strend(path);
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



@@Return the filename-part, that is everything following
@@the last slash of `filename'. If no such part exists, "."
@@is returned instead. Trailing slashes are ignored
@@>> basename("/usr/include///"); // Returns "include"
@@>> basename("/usr/include/");   // Returns "include"
@@>> basename("/usr/include");    // Returns "include"
@@>> basename("/usr/");           // Returns "usr"
@@>> basename("/usr");            // Returns "usr"
@@>> basename("/");               // Returns "/"
@@>> basename("///");             // Returns "/"
@@>> basename("foo/bar/");        // Returns "bar"
@@>> basename("foo/bar");         // Returns "bar"
@@>> basename("foo/");            // Returns "foo"
@@>> basename("foo");             // Returns "foo"
@@>> basename(".");               // Returns "."
@@>> basename("..");              // Returns ".."
@@>> basename("");                // Returns "."
@@>> basename(NULL);              // Returns "."
@@Note that for this purpose, `filename' may be modified in-place, meaning
@@that you should really always pass an strdup()'d, or writable string.
@@
@@Also note that a different version of this function exists in <string.h>,
@@where if you include both <libgen.h> and <string.h>, you can use the
@@alternate function from <string.h> by `#undef basename', or calling the
@@function as `(basename)(...)' (as opposed to `basename(...)')
[[nonnull, export_alias("__gnu_basename")]]
char *__xpg_basename(char *filename) {
	char *iter;
	/* Handle the empty-path case. */
	if (!filename || !*filename)
		goto fallback;
	iter = strend(filename);
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

%#define basename(path) __xpg_basename(path)


%{

__SYSDECL_END
#endif /* __CC__ */

}
