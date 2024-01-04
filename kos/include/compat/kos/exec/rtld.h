/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _COMPAT_KOS_EXEC_RTLD_H
#define _COMPAT_KOS_EXEC_RTLD_H 1

#include <__stdinc.h>

#include <compat/kos/exec/asm/rtld.h>

/* Absolute path of the libdl driver itself. */
#ifndef COMPAT_RTLD_LIBDL
#ifdef COMPAT_RTLD_LIB
#error "Arch defined `COMPAT_RTLD_LIB', but not `COMPAT_RTLD_LIBDL'"
#endif /* COMPAT_RTLD_LIB */
#ifdef _COMPAT_RTLD_LIBDL_HASH
#error "Arch defined `_COMPAT_RTLD_LIBDL_HASH', but not `COMPAT_RTLD_LIBDL'"
#endif /* _COMPAT_RTLD_LIBDL_HASH */
#define COMPAT_RTLD_LIB   "lib"
#define COMPAT_RTLD_LIBDL "/lib/libdl.so"
#define _COMPAT_RTLD_LIBDL_HASH /*[[[fdirent_hash("/lib/libdl.so")]]]*/FDIRENT_HASH_INIT(0x6e321ca9, 0x75b4ce19e8e33a0b, 0x94d3128e, 0xaacfb4e31dfe20d6)/*[[[end]]]*/
#elif !defined(_COMPAT_RTLD_LIBDL_HASH)
#error "Arch defined `COMPAT_RTLD_LIBDL', but not `_COMPAT_RTLD_LIBDL_HASH'"
#endif /* !COMPAT_RTLD_LIBDL */

/* Default for `LD_LIBRARY_PATH' */
#ifndef COMPAT_RTLD_LIBRARY_PATH
#define COMPAT_RTLD_LIBRARY_PATH "/usr/" COMPAT_RTLD_LIB ":/" COMPAT_RTLD_LIB
#endif /* !COMPAT_RTLD_LIBRARY_PATH */

/* The string to which `$LIB' in library paths is expanded */
#ifndef COMPAT_RTLD_LIB
#define COMPAT_RTLD_LIB "lib"
#endif /* !COMPAT_RTLD_LIB */

/* The string to which `$PLATFORM' in library paths is expanded */
#ifndef COMPAT_RTLD_PLATFORM
#define COMPAT_RTLD_PLATFORM "?"
#endif /* !COMPAT_RTLD_PLATFORM */

#endif /* !_COMPAT_KOS_EXEC_RTLD_H */
