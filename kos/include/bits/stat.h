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
#ifndef _BITS_STAT_H
#define _BITS_STAT_H 1

#include <__stdinc.h>
#include <features.h>

#include <asm/stat.h>

#ifdef __USE_ATFILE
#define UTIME_NOW  __UTIME_NOW
#define UTIME_OMIT __UTIME_OMIT
#endif /* __USE_ATFILE */


/* When running as `__CRT_DOS_PRIMARY':
 *   `struct stat' is:
 *       [                                       ] = struct __dos_stat32
 *       [__USE_TIME_BITS64                      ] = struct __dos_stat64i32 == struct __dos_stat64
 *       [__USE_FILE_OFFSET64                    ] = struct __dos_stat32i64
 *       [__USE_TIME_BITS64 + __USE_FILE_OFFSET64] = struct __dos_stat64
 *   `struct stat64' is:
 *       [                 ]                       = struct __dos_stat32i64
 *       [__USE_TIME_BITS64]                       = struct __dos_stat64
 * When running as `__CRT_KOS_PRIMARY':
 *   `struct stat' is:                             = struct __kos_stat
 *   `struct stat64' is:                           = struct __kos_stat
 * When running as `__CRT_GLC_PRIMARY':
 *   `struct stat' is:
 *       [                   ]                     = struct __cyg_stat
 *       [__USE_FILE_OFFSET64]                     = struct __glc_stat64
 *   `struct stat64' is:                           = struct __glc_stat64
 * When running as `__CRT_CYG_PRIMARY':
 *   `struct stat' is:                             = struct __cyg_stat
 *   `struct stat64' is:                           = struct __cyg_stat
 * Otherwise, `struct stat' uses a totally generic layout.
 */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("stat")
#ifdef __USE_LARGEFILE64
#pragma push_macro("stat64")
#endif /* __USE_LARGEFILE64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef stat
#ifdef __USE_LARGEFILE64
#undef stat64
#endif /* __USE_LARGEFILE64 */

#ifdef __CRT_DOS_PRIMARY
#include <bits/stat-dos.h>
#elif defined(__CRT_KOS_PRIMARY) || defined(__KOS__)
#include <bits/stat-kos.h>
#elif defined(__CRT_GLC_PRIMARY)
#include <bits/stat-glc.h>
#elif defined(__CRT_CYG_PRIMARY)
#include <bits/stat-cyg.h>
#elif defined(__CRT_GENERIC)
#include <bits/stat-gen.h>
#else
#include <__crt.h>
#ifdef __CRT_HAVE_stat
#ifndef __NO_WARNINGS
#warning "No stat() support for CRT"
#endif /* !__NO_WARNINGS */
#ifdef __CC__
__DECL_BEGIN
struct stat { int __placeholder; };
#ifdef __USE_LARGEFILE64
struct stat64 { int __placeholder; };
#endif /* __USE_LARGEFILE64 */
__DECL_END
#endif /* __CC__ */
#endif /* __CRT_HAVE_stat */
#endif

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __USE_LARGEFILE64
#pragma pop_macro("stat64")
#endif /* __USE_LARGEFILE64 */
#pragma pop_macro("stat")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_BITS_STAT_H */
