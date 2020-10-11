/* HASH CRC-32:0xbb4aef0 */
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
#ifndef GUARD_LIBC_AUTO_LIBGEN_H
#define GUARD_LIBC_AUTO_LIBGEN_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <libgen.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_RETNONNULL char *NOTHROW_NCX(LIBDCALL libd_dirname)(char *path);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
 * Note that for this purpose, `path' may be modified in-place, meaning
 * that you should really always pass an strdup()'d, or writable string. */
INTDEF ATTR_RETNONNULL char *NOTHROW_NCX(LIBCCALL libc_dirname)(char *path);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_RETNONNULL char *NOTHROW_NCX(LIBDCALL libd___xpg_basename)(char *filename);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_RETNONNULL char *NOTHROW_NCX(LIBCCALL libc___xpg_basename)(char *filename);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_LIBGEN_H */
