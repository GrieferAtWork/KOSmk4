/* HASH CRC-32:0x8a152385 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBGEN_H
#define _LIBGEN_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_dirname
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
 * Note that for this purpose, `path' may be modified in-place, meaning
 * that you should really always pass an strdup()'d, or writable string. */
__CDECLARE(__ATTR_RETNONNULL,char *,__NOTHROW_NCX,dirname,(char *__path),(__path))
#else /* __CRT_HAVE_dirname */
#include <libc/local/libgen/dirname.h>
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
 * Note that for this purpose, `path' may be modified in-place, meaning
 * that you should really always pass an strdup()'d, or writable string. */
__NAMESPACE_LOCAL_USING_OR_IMPL(dirname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL char *__NOTHROW_NCX(__LIBCCALL dirname)(char *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dirname))(__path); })
#endif /* !__CRT_HAVE_dirname */
#ifdef __CRT_HAVE___xpg_basename
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
__CDECLARE(__ATTR_RETNONNULL,char *,__NOTHROW_NCX,__xpg_basename,(char *__filename),(__filename))
#elif defined(__CRT_HAVE___gnu_basename)
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
__CREDIRECT(__ATTR_RETNONNULL,char *,__NOTHROW_NCX,__xpg_basename,(char *__filename),__gnu_basename,(__filename))
#else /* ... */
#include <libc/local/libgen/__xpg_basename.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(__xpg_basename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL char *__NOTHROW_NCX(__LIBCCALL __xpg_basename)(char *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__xpg_basename))(__filename); })
#endif /* !... */
#define basename(path) __xpg_basename(path)

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LIBGEN_H */
