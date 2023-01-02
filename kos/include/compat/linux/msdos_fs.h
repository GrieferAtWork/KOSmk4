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
/* (#) Portability: Linux (/include/linux/msdos_fs.h) */
#ifndef _COMPAT_LINUX_MSDOS_FS_H
#define _COMPAT_LINUX_MSDOS_FS_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <compat/config.h>
#include <linux/msdos_fs.h>

#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER == __SIZEOF_POINTER__
#define __COMPAT_FAT_DIRENT_MATCHES_FAT_DIRENT
#define __compat_fat_dirent __fat_dirent
#else /* __ARCH_COMPAT_SIZEOF_POINTER == __SIZEOF_POINTER__ */

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("d_off")
#pragma push_macro("d_reclen")
#pragma push_macro("d_name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef d_ino
#undef d_off
#undef d_reclen
#undef d_name
struct __compat_fat_dirent {
#ifdef __USE_KOS_ALTERATIONS
#ifndef __DIRENT_HAVE_U_D_INO
	__ARCH_COMPAT_ULONGPTR_TYPE     d_ino;
#else /* !__DIRENT_HAVE_U_D_INO */
	union {
		__ARCH_COMPAT_ULONGPTR_TYPE d_ino;
	} __u_d_ino;
#define d_ino __u_d_ino.d_ino
#endif /* __DIRENT_HAVE_U_D_INO */
	__ARCH_COMPAT_ULONGPTR_TYPE     d_off;
#else /* __USE_KOS_ALTERATIONS */
#ifndef __DIRENT_HAVE_U_D_INO
	__ARCH_COMPAT_LONGPTR_TYPE      d_ino;
#else /* !__DIRENT_HAVE_U_D_INO */
	union {
		__ARCH_COMPAT_LONGPTR_TYPE  d_ino;
	} __u_d_ino;
#define d_ino __u_d_ino.d_ino
#endif /* __DIRENT_HAVE_U_D_INO */
	__ARCH_COMPAT_LONGPTR_TYPE      d_off;
#endif /* !__USE_KOS_ALTERATIONS */
	__UINT16_TYPE__                 d_reclen;
	char                            d_name[256];
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("d_name")
#pragma pop_macro("d_reclen")
#pragma pop_macro("d_off")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != __SIZEOF_POINTER__ */
#endif /* __ARCH_HAVE_COMPAT */

#endif /* _COMPAT_LINUX_MSDOS_FS_H */
