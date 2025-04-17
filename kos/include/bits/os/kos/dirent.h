/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!replace_with_include <bits/os/dirent.h>*/
#ifndef _BITS_OS_KOS_DIRENT_H
#define _BITS_OS_KOS_DIRENT_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

#undef _DIRENT_HAVE_D_RECLEN
#define _DIRENT_HAVE_D_NAMLEN
#define _DIRENT_HAVE_D_TYPE      1
#define _DIRENT_HAVE_D_FILENO    1 /* Backwards compatibility. */
#define _DIRENT_MATCHES_DIRENT64 1

#define __DIRENT32_MATCHES_DIRENT64 1

#define __OFFSET_DIRENT_INO      0
#define __OFFSET_DIRENT_NAMLEN   __SIZEOF_INO64_T__
#define __OFFSET_DIRENT_TYPE     (__SIZEOF_INO64_T__ + 2)
#define __OFFSET_DIRENT_NAME     (__SIZEOF_INO64_T__ + 3)
#define __OFFSET_DIRENT64_INO    0
#define __OFFSET_DIRENT64_NAMLEN __SIZEOF_INO64_T__
#define __OFFSET_DIRENT64_TYPE   (__SIZEOF_INO64_T__ + 2)
#define __OFFSET_DIRENT64_NAME   (__SIZEOF_INO64_T__ + 3)
#ifdef __CC__
__DECL_BEGIN

#ifdef _DIRENT_HAVE_D_FILENO
#undef d_fileno
#endif /* _DIRENT_HAVE_D_FILENO */
struct dirent {
#ifdef __USE_KOS
#undef d_ino
#undef d_ino32
#undef d_ino64
	union {
#ifdef _DIRENT_HAVE_D_FILENO
		__ino_t        d_fileno;
#endif /* _DIRENT_HAVE_D_FILENO */
		__ino_t        d_ino;
		__ino32_t      d_ino32;
		__ino64_t      d_ino64;
	}
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	;
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	__u_d_ino;
#define __DIRENT_HAVE_U_D_INO 1
#ifdef _DIRENT_HAVE_D_FILENO
#define d_fileno     __u_d_ino.d_fileno
#endif /* _DIRENT_HAVE_D_FILENO */
#define d_ino        __u_d_ino.d_ino
#define d_ino32      __u_d_ino.d_ino32
#define d_ino64      __u_d_ino.d_ino64
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#else /* __USE_KOS */
#ifdef _DIRENT_HAVE_D_FILENO
#undef d_ino
#undef d_fileno
	union {
		__ino_t        d_ino;
		__ino_t        d_fileno;
	}
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	;
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	__u_d_ino;
#define __DIRENT_HAVE_U_D_INO 1
#define d_fileno     __u_d_ino.d_fileno
#define d_ino        __u_d_ino.d_ino
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#else /* _DIRENT_HAVE_D_FILENO */
	__ino_t     d_ino;
#endif /* !_DIRENT_HAVE_D_FILENO */
#ifndef __USE_FILE_OFFSET64
#if __SIZEOF_INO32_T__ < __SIZEOF_INO64_T__
	__byte_t         __padding0[__SIZEOF_INO64_T__ - __SIZEOF_INO32_T__];
#endif /* __SIZEOF_INO32_T__ < __SIZEOF_INO64_T__ */
#endif /* !__USE_FILE_OFFSET64 */
#endif /* !__USE_KOS */
	__UINT16_TYPE__    d_namlen; /* == strlen(d_name) */
	__UINT8_TYPE__     d_type;
#if defined(__DIRENT_TEXTSIZE)
	char               d_name[__DIRENT_TEXTSIZE];
#elif (defined(__COMPILER_HAVE_VARIABLE_LENGTH_ARRAYS) && \
       (defined(__USE_KOS) || defined(__USE_KOS_KERNEL) || \
        defined(__USE_KOS_ALTERATIONS)))
	__COMPILER_FLEXIBLE_ARRAY(char, d_name); /* Allocated as required. */
#else /* ... */
	char               d_name[256];
#endif /* !... */
};

#ifdef __USE_LARGEFILE64
#define __dirent64 dirent64
#ifdef __USE_STRUCT64_MACRO
#define dirent64 dirent
#else /* __USE_STRUCT64_MACRO */
#ifndef _DIRENT_HAVE_D_FILENO
#undef d_fileno
#endif /* !_DIRENT_HAVE_D_FILENO */
struct dirent64 {
#ifdef __USE_KOS
#undef d_ino
#undef d_ino32
#undef d_ino64
	union {
#ifndef _DIRENT_HAVE_D_FILENO
		__ino64_t      d_fileno;
#endif /* !_DIRENT_HAVE_D_FILENO */
		__ino64_t      d_ino;
		__ino32_t      d_ino32;
		__ino64_t      d_ino64;
	}
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	;
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	__u_d_ino;
#ifndef _DIRENT_HAVE_D_FILENO
#define d_fileno   __u_d_ino.d_fileno
#endif /* !_DIRENT_HAVE_D_FILENO */
#define d_ino      __u_d_ino.d_ino
#define d_ino32    __u_d_ino.d_ino32
#define d_ino64    __u_d_ino.d_ino64
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#else /* __USE_KOS */
#ifdef _DIRENT_HAVE_D_FILENO
#undef d_ino
#undef d_fileno
	union {
		__ino64_t      d_ino;
		__ino64_t      d_fileno;
	}
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	;
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	__u_d_ino;
#define d_fileno     __u_d_ino.d_fileno
#define d_ino        __u_d_ino.d_ino
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#else /* _DIRENT_HAVE_D_FILENO */
	__ino64_t          d_ino;
#endif /* !_DIRENT_HAVE_D_FILENO */
#endif /* !__USE_KOS */
	__UINT16_TYPE__    d_namlen; /* == strlen(d_name) */
	__UINT8_TYPE__     d_type;
#if defined(__DIRENT_TEXTSIZE)
	char               d_name[__DIRENT_TEXTSIZE];
#elif defined(__USE_KOS_KERNEL)
	__COMPILER_FLEXIBLE_ARRAY(char, d_name); /* Allocated as required. */
#else /* ... */
	char               d_name[256];
#endif /* !... */
};
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_LARGEFILE64 */
#define __dirent64 dirent
#endif /* !__USE_LARGEFILE64 */

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_KOS_DIRENT_H */
