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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_DIRENT_H
#define _BITS_DIRENT_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__
struct dirent {
#ifdef __USE_KOS
#undef d_ino
#undef d_ino32
#undef d_ino64
	union {
		__FS_TYPE(ino)     d_ino;
		__ino32_t          d_ino32;
		__ino64_t          d_ino64;
	}
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	;
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	__u_d_ino;
#define d_ino        __u_d_ino.d_ino
#define d_ino32      __u_d_ino.d_ino32
#define d_ino64      __u_d_ino.d_ino64
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#else /* __USE_KOS */
#ifdef __USE_FILE_OFFSET64
	__ino64_t          d_ino;
#else /* __USE_FILE_OFFSET64 */
	__ino32_t          d_ino;
	__ino32_t        __padding0;
#endif /* !__USE_FILE_OFFSET64 */
#endif /* !__USE_KOS */
	__UINT8_TYPE__     d_type;
	__UINT8_TYPE__   __d_pad;
	__UINT16_TYPE__    d_namlen; /* == strlen(d_name) */
#if defined(__DIRENT_TEXTSIZE)
	char               d_name[__DIRENT_TEXTSIZE];
#elif defined(__USE_KOS_KERNEL)
	__COMPILER_FLEXIBLE_ARRAY(char, d_name); /* Allocated as required. */
#else
	char               d_name[256];
#endif
};

#ifdef __USE_LARGEFILE64
#ifdef __USE_STRUCT64_MACRO
#define dirent64 dirent
#else /* __USE_STRUCT64_MACRO */
struct dirent64 {
#ifdef __USE_KOS
#undef d_ino
#undef d_ino32
#undef d_ino64
	union {
		__ino64_t          d_ino;
		__ino32_t          d_ino32;
		__ino64_t          d_ino64;
	}
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	;
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	__u_d_ino;
#define d_ino      __u_d_ino.d_ino
#define d_ino32    __u_d_ino.d_ino32
#define d_ino64    __u_d_ino.d_ino64
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#else /* __USE_KOS */
	__ino64_t          d_ino;
#endif /* !__USE_KOS */
	__UINT8_TYPE__     d_type;
	__UINT8_TYPE__   __d_pad;
	__UINT16_TYPE__    d_namlen; /* == strlen(d_name) */
#if defined(__DIRENT_TEXTSIZE)
	char               d_name[__DIRENT_TEXTSIZE];
#elif defined(__USE_KOS_KERNEL)
	__COMPILER_FLEXIBLE_ARRAY(char, d_name); /* Allocated as required. */
#else
	char               d_name[256];
#endif
};
#endif /* !__USE_STRUCT64_MACRO */
#endif /* __USE_LARGEFILE64 */

#undef d_fileno
#define d_fileno d_ino /* Backwards compatibility. */

#endif /* __CC__ */


#undef  _DIRENT_HAVE_D_RECLEN
#define _DIRENT_HAVE_D_NAMLEN
#define _DIRENT_HAVE_D_TYPE 1
#define _DIRENT_MATCHES_DIRENT64 1

__SYSDECL_END

#endif /* !_BITS_DIRENT_H */
