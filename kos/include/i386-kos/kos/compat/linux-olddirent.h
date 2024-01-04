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
#ifndef _I386_KOS_KOS_COMPAT_LINUX_OLDDIRENT_H
#define _I386_KOS_KOS_COMPAT_LINUX_OLDDIRENT_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/os/dirent.h> /* __DIRENT_HAVE_U_D_INO */

#ifdef __x86_64__
#define old_linux_direntx64 old_linux_dirent
#elif defined(__i386__)
#define old_linux_direntx32 old_linux_dirent
#endif /* ... */

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("d_offset")
#pragma push_macro("d_namlen")
#pragma push_macro("d_name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef d_ino
#undef d_offset
#undef d_namlen
#undef d_name

struct old_linux_direntx32 {
#ifndef __DIRENT_HAVE_U_D_INO
	__ULONG32_TYPE__                d_ino;    /* File INode number */
#else /* !__DIRENT_HAVE_U_D_INO */
	union {
		__ULONG32_TYPE__            d_ino;    /* File INode number */
	} __u_d_ino;
#endif /* __DIRENT_HAVE_U_D_INO */
	__ULONG32_TYPE__                d_offset; /* Offset of next directory entry in containing directory. */
	__UINT16_TYPE__                 d_namlen; /* == strlen(d_name) */
	__COMPILER_FLEXIBLE_ARRAY(char, d_name);  /* Entry file name. */
};

struct old_linux_direntx64 {
#ifndef __DIRENT_HAVE_U_D_INO
	__ULONG64_TYPE__                d_ino;    /* File INode number */
#else /* !__DIRENT_HAVE_U_D_INO */
	union {
		__ULONG64_TYPE__            d_ino;    /* File INode number */
	} __u_d_ino;
#define d_ino __u_d_ino.d_ino
#endif /* __DIRENT_HAVE_U_D_INO */
	__ULONG64_TYPE__                d_offset; /* Offset of next directory entry in containing directory. */
	__UINT16_TYPE__                 d_namlen; /* == strlen(d_name) */
	__COMPILER_FLEXIBLE_ARRAY(char, d_name);  /* Entry file name. */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("d_name")
#pragma pop_macro("d_namlen")
#pragma pop_macro("d_offset")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_COMPAT_LINUX_OLDDIRENT_H */
