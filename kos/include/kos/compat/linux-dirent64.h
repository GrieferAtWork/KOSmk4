/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_COMPAT_LINUX_DIRENT64_H
#define _KOS_COMPAT_LINUX_DIRENT64_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/dirent.h> /* __DIRENT_HAVE_U_D_INO */

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

struct linux_dirent64 {
#ifndef __DIRENT_HAVE_U_D_INO
	__ULONG64_TYPE__                d_ino;    /* File INode number */
#else /* !__DIRENT_HAVE_U_D_INO */
	union {
		__ULONG64_TYPE__            d_ino;    /* File INode number */
	} __u_d_ino;
#define d_ino __u_d_ino.d_ino
#endif /* __DIRENT_HAVE_U_D_INO */
#ifdef __USE_KOS_ALTERATIONS
	__ULONG64_TYPE__                d_off;    /* Offset of next directory entry in containing directory. */
#else /* __USE_KOS_ALTERATIONS */
	__LONG64_TYPE__                 d_off;    /* Offset of next directory entry in containing directory. */
#endif /* !__USE_KOS_ALTERATIONS */
	__UINT16_TYPE__                 d_reclen; /* Record length (`== CEIL_ALIGN(offsetof(struct linux_dirent64, d_name) +
	                                           *                               strlen(d_name), sizeof(void *))') */
	__UINT8_TYPE__                  d_type;   /* File type (One of `DT_*') */
	__COMPILER_FLEXIBLE_ARRAY(char, d_name);  /* Entry file name. */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("d_name")
#pragma pop_macro("d_namlen")
#pragma pop_macro("d_offset")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_COMPAT_LINUX_DIRENT64_H */
