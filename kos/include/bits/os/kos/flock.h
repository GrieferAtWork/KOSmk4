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
#ifndef _BITS_OS_KOS_FLOCK_H
#define _BITS_OS_KOS_FLOCK_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>


#define __OFFSET_FLOCK_TYPE   0
#define __OFFSET_FLOCK_WHENCE 2
#if __ALIGNOF_OFF_T__ >= 8
#define __OFFSET_FLOCK_START  8
#else /* __ALIGNOF_OFF_T__ >= 8 */
#define __OFFSET_FLOCK_START  4
#endif /* __ALIGNOF_OFF_T__ < 8 */
#define __OFFSET_FLOCK_LEN    (__OFFSET_FLOCK_START + __SIZEOF_OFF_T__)
#define __OFFSET_FLOCK_PID    (__OFFSET_FLOCK_START + __SIZEOF_OFF_T__ * 2)
#if __ALIGNOF_OFF_T__ > __ALIGNOF_PID_T__
#define __SIZEOF_FLOCK        (__OFFSET_FLOCK_START + __SIZEOF_OFF_T__ * 2 + __SIZEOF_PID_T__ + 4)
#else /* __ALIGNOF_OFF_T__ > __ALIGNOF_PID_T__ */
#define __SIZEOF_FLOCK        (__OFFSET_FLOCK_START + __SIZEOF_OFF_T__ * 2 + __SIZEOF_PID_T__)
#endif /* __ALIGNOF_OFF_T__ <= __ALIGNOF_PID_T__ */

#define __OFFSET_FLOCK32_TYPE   0
#define __OFFSET_FLOCK32_WHENCE 2
#if __ALIGNOF_OFF32_T__ >= 8
#define __OFFSET_FLOCK32_START  8
#else /* __ALIGNOF_OFF32_T__ >= 8 */
#define __OFFSET_FLOCK32_START  4
#endif /* __ALIGNOF_OFF32_T__ < 8 */
#define __OFFSET_FLOCK32_LEN    (__OFFSET_FLOCK32_START + __SIZEOF_OFF32_T__)
#define __OFFSET_FLOCK32_PID    (__OFFSET_FLOCK32_START + __SIZEOF_OFF32_T__ * 2)
#if __ALIGNOF_OFF32_T__ > __ALIGNOF_PID_T__
#define __SIZEOF_FLOCK32        (__OFFSET_FLOCK32_START + __SIZEOF_OFF32_T__ * 2 + __SIZEOF_PID_T__ + 4)
#else /* __ALIGNOF_OFF32_T__ > __ALIGNOF_PID_T__ */
#define __SIZEOF_FLOCK32        (__OFFSET_FLOCK32_START + __SIZEOF_OFF32_T__ * 2 + __SIZEOF_PID_T__)
#endif /* __ALIGNOF_OFF32_T__ <= __ALIGNOF_PID_T__ */

#define __OFFSET_FLOCK64_TYPE   0
#define __OFFSET_FLOCK64_WHENCE 2
#if __ALIGNOF_OFF64_T__ >= 8
#define __OFFSET_FLOCK64_START  8
#else /* __ALIGNOF_OFF64_T__ >= 8 */
#define __OFFSET_FLOCK64_START  4
#endif /* __ALIGNOF_OFF64_T__ < 8 */
#define __OFFSET_FLOCK64_LEN    (__OFFSET_FLOCK64_START + __SIZEOF_OFF64_T__)
#define __OFFSET_FLOCK64_PID    (__OFFSET_FLOCK64_START + __SIZEOF_OFF64_T__ * 2)
#if __ALIGNOF_OFF64_T__ >= 8 && __SIZEOF_PID_T__ < 8
#define __SIZEOF_FLOCK64        (__OFFSET_FLOCK64_START + __SIZEOF_OFF64_T__ * 2 + __SIZEOF_PID_T__ + 4)
#else /* __ALIGNOF_OFF64_T__ >= 8 && __SIZEOF_PID_T__ < 8 */
#define __SIZEOF_FLOCK64        (__OFFSET_FLOCK64_START + __SIZEOF_OFF64_T__ * 2 + __SIZEOF_PID_T__)
#endif /* __ALIGNOF_OFF64_T__ < 8 || __SIZEOF_PID_T__ >= 8 */

#ifdef __CC__
__DECL_BEGIN

struct flock /*[PREFIX(l_)]*/ {
	__INT16_TYPE__ l_type;   /* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK. */
	__INT16_TYPE__ l_whence; /* Where `l_start' is relative to (like `lseek'). */
#if __ALIGNOF_OFF_T__ >= 8
	__UINT32_TYPE__ __l_pad; /* ... */
#endif /* __ALIGNOF_OFF_T__ >= 8 */
#ifdef __USE_KOS_ALTERATIONS
	__pos_t        l_start;  /* Offset where the lock begins. */
	__pos_t        l_len;    /* Size of the locked area; zero means until EOF. */
#else /* __USE_KOS_ALTERATIONS */
	__off_t        l_start;  /* Offset where the lock begins. */
	__off_t        l_len;    /* Size of the locked area; zero means until EOF. */
#endif /* !__USE_KOS_ALTERATIONS */
	__pid_t        l_pid;    /* Process holding the lock. */
#if __ALIGNOF_OFF_T__ > __ALIGNOF_PID_T__
	__UINT32_TYPE__ __l_pad2; /* ... */
#endif /* __ALIGNOF_OFF_T__ > __ALIGNOF_PID_T__ */
};

#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
#define _FLOCK_MATCHES_FLOCK64 1
#endif /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */

#ifdef __USE_LARGEFILE64
#if (defined(__USE_FILE_OFFSET64) || defined(_FLOCK_MATCHES_FLOCK64)) && defined(__USE_STRUCT64_MACRO)
#define flock64 flock
#else /* (__USE_FILE_OFFSET64 || _FLOCK_MATCHES_FLOCK64) && __USE_STRUCT64_MACRO */
#define __flock64 flock64
#endif /* (!__USE_FILE_OFFSET64 && !_FLOCK_MATCHES_FLOCK64) || !__USE_STRUCT64_MACRO */
#endif /* __USE_LARGEFILE64 */

#if (defined(__USE_FILE_OFFSET64) || defined(_FLOCK_MATCHES_FLOCK64)) && defined(__USE_STRUCT64_MACRO)
#define __flock64 flock
#else /* (__USE_FILE_OFFSET64 || _FLOCK_MATCHES_FLOCK64) && __USE_STRUCT64_MACRO */
struct __flock64 /*[NAME(flock64)][PREFIX(l_)]*/ {
	__INT16_TYPE__ l_type;   /* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK. */
	__INT16_TYPE__ l_whence; /* Where `l_start' is relative to (like `lseek'). */
#if __ALIGNOF_OFF64_T__ >= 8
	__UINT32_TYPE__ __l_pad; /* ... */
#endif /* __ALIGNOF_OFF64_T__ >= 8 */
#ifdef __USE_KOS_ALTERATIONS
	__pos64_t      l_start;  /* Offset where the lock begins. */
	__pos64_t      l_len;    /* Size of the locked area; zero means until EOF. */
#else /* __USE_KOS_ALTERATIONS */
	__off64_t      l_start;  /* Offset where the lock begins. */
	__off64_t      l_len;    /* Size of the locked area; zero means until EOF. */
#endif /* !__USE_KOS_ALTERATIONS */
	__pid_t        l_pid;    /* Process holding the lock. */
#if __ALIGNOF_OFF64_T__ >= 8 && __SIZEOF_PID_T__ < 8
	__UINT32_TYPE__ __l_pad2; /* ... */
#endif /* __ALIGNOF_OFF64_T__ >= 8 && __SIZEOF_PID_T__ < 8 */
};
#endif /* (!__USE_FILE_OFFSET64 && !_FLOCK_MATCHES_FLOCK64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#if !defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
#define flock32 flock
#else /* !__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
#define __flock32 flock32
#endif /* __USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */
#endif /* __USE_KOS */

#if !defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
#define __flock32 flock
#else /* !__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
struct __flock32 /*[NAME(flock32)][PREFIX(l_)]*/ {
	__INT16_TYPE__ l_type;   /* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK. */
	__INT16_TYPE__ l_whence; /* Where `l_start' is relative to (like `lseek'). */
#if __ALIGNOF_OFF32_T__ >= 8
	__UINT32_TYPE__ __l_pad; /* ... */
#endif /* __ALIGNOF_OFF32_T__ >= 8 */
#ifdef __USE_KOS_ALTERATIONS
	__pos32_t      l_start;  /* Offset where the lock begins. */
	__pos32_t      l_len;    /* Size of the locked area; zero means until EOF. */
#else /* __USE_KOS_ALTERATIONS */
	__off32_t      l_start;  /* Offset where the lock begins. */
	__off32_t      l_len;    /* Size of the locked area; zero means until EOF. */
#endif /* !__USE_KOS_ALTERATIONS */
	__pid_t        l_pid;    /* Process holding the lock. */
#if __ALIGNOF_OFF32_T__ > __ALIGNOF_PID_T__
	__UINT32_TYPE__ __l_pad2; /* ... */
#endif /* __ALIGNOF_OFF32_T__ > __ALIGNOF_PID_T__ */
};
#endif /* __USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_FLOCK_H */
