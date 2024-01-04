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
#ifndef _BITS_CRT_GLOB_H
#define _BITS_CRT_GLOB_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/dirent.h>
#include <bits/os/stat.h>
#include <bits/types.h>

#if defined(__DIRENT32_MATCHES_DIRENT64) && defined(__STAT32_MATCHES_STAT64)
#define __GLOB32_MATCHES_GLOB64 1
#endif /* __DIRENT32_MATCHES_DIRENT64 && __STAT32_MATCHES_STAT64 */

#ifdef __CC__
__DECL_BEGIN

struct __glob_struct {
	__size_t gl_pathc; /* ??? */
	char   **gl_pathv; /* ??? */
	__size_t gl_offs;  /* ??? */
	int      gl_flags; /* ??? */
	void (__LIBKCALL *gl_closedir)(void *);
#ifdef __USE_GNU
	struct dirent *(__LIBKCALL *gl_readdir)(void *);
#else /* __USE_GNU */
	void *(__LIBKCALL *gl_readdir)(void *);
#endif /* !__USE_GNU */
	void *(__LIBKCALL *gl_opendir)(char const *);
#ifdef __USE_GNU
	int (__LIBKCALL *gl_lstat)(char const *__restrict, struct stat *__restrict);
	int (__LIBKCALL *gl_stat)(char const *__restrict, struct stat *__restrict);
#else /* __USE_GNU */
	int (__LIBKCALL *gl_lstat)(char const *__restrict, void *__restrict);
	int (__LIBKCALL *gl_stat)(char const *__restrict, void *__restrict);
#endif /* !__USE_GNU */
};

#ifdef __USE_LARGEFILE64
struct __glob64_struct {
	__size_t gl_pathc; /* ??? */
	char   **gl_pathv; /* ??? */
	__size_t gl_offs;  /* ??? */
	int      gl_flags; /* ??? */
	void (__LIBKCALL *gl_closedir)(void *);
#ifdef __USE_GNU
	struct dirent64 *(__LIBKCALL *gl_readdir)(void *);
#else /* __USE_GNU */
	void *(__LIBKCALL *gl_readdir)(void *);
#endif /* !__USE_GNU */
	void *(__LIBKCALL *gl_opendir)(char const *);
#ifdef __USE_GNU
	int (__LIBKCALL *gl_lstat)(char const *__restrict, struct stat64 *__restrict);
	int (__LIBKCALL *gl_stat)(char const *__restrict, struct stat64 *__restrict);
#else /* __USE_GNU */
	int (__LIBKCALL *gl_lstat)(char const *__restrict, void *__restrict);
	int (__LIBKCALL *gl_stat)(char const *__restrict, void *__restrict);
#endif /* !__USE_GNU */
};
#endif /* __USE_LARGEFILE64 */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_GLOB_H */
