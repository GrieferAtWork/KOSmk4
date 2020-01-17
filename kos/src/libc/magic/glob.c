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

%[default_impl_section(.text.crt.utility.glob)]


%{
#include <features.h>
#include <bits/types.h>

/* Documentation taken from Glibc /usr/include/glob.h */
/* Copyright (C) 1996-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */


/* Bits set in the FLAGS argument to `glob'.  */
#define GLOB_ERR      (1 << 0) /* Return on read errors.  */
#define GLOB_MARK     (1 << 1) /* Append a slash to each name.  */
#define GLOB_NOSORT   (1 << 2) /* Don't sort the names.  */
#define GLOB_DOOFFS   (1 << 3) /* Insert PGLOB->gl_offs NULLs.  */
#define GLOB_NOCHECK  (1 << 4) /* If nothing matches, return the pattern.  */
#define GLOB_APPEND   (1 << 5) /* Append to results of a previous call.  */
#define GLOB_NOESCAPE (1 << 6) /* Backslashes don't quote metacharacters.  */
#define GLOB_PERIOD   (1 << 7) /* Leading `.' can be matched by metachars.  */

#if !defined __USE_POSIX2 || defined __USE_MISC
#define GLOB_MAGCHAR      (1 << 8)  /* Set in gl_flags if any metachars seen.  */
#define GLOB_ALTDIRFUNC   (1 << 9)  /* Use gl_opendir et al functions.  */
#define GLOB_BRACE        (1 << 10) /* Expand "{a,b}" to "a" "b".  */
#define GLOB_NOMAGIC      (1 << 11) /* If no magic chars, return the pattern.  */
#define GLOB_TILDE        (1 << 12) /* Expand ~user and ~ to home directories. */
#define GLOB_ONLYDIR      (1 << 13) /* Match only directories.  */
#define GLOB_TILDE_CHECK  (1 << 14) /* Like GLOB_TILDE but return an error if the user name is not available.  */
#define __GLOB_FLAGS                                    \
	(GLOB_ERR | GLOB_MARK | GLOB_NOSORT | GLOB_DOOFFS | \
	 GLOB_NOESCAPE | GLOB_NOCHECK | GLOB_APPEND |       \
	 GLOB_PERIOD | GLOB_ALTDIRFUNC | GLOB_BRACE |       \
	 GLOB_NOMAGIC | GLOB_TILDE | GLOB_ONLYDIR | GLOB_TILDE_CHECK)
#else
#define __GLOB_FLAGS                                    \
	(GLOB_ERR | GLOB_MARK | GLOB_NOSORT | GLOB_DOOFFS | \
	 GLOB_NOESCAPE | GLOB_NOCHECK | GLOB_APPEND |       \
	 GLOB_PERIOD)
#endif

/* Error returns from `glob'. */
#define GLOB_NOSPACE 1 /* Ran out of memory.  */
#define GLOB_ABORTED 2 /* Read error.  */
#define GLOB_NOMATCH 3 /* No matches found.  */
#define GLOB_NOSYS   4 /* Not implemented.  */
#ifdef __USE_GNU
/* Previous versions of this file defined GLOB_ABEND instead
 * of GLOB_ABORTED. Provide a compatibility definition here. */
#define GLOB_ABEND GLOB_ABORTED
#endif /* __USE_GNU */

/* Structure describing a globbing run. */
#ifdef __USE_GNU
struct dirent;
struct stat;
#endif /* __USE_GNU */
typedef struct __glob_struct {
	__size_t gl_pathc; /* Count of paths matched by the pattern.  */
	char   **gl_pathv; /* List of matched pathnames.  */
	__size_t gl_offs;  /* Slots to reserve in `gl_pathv'.  */
	int      gl_flags; /* Set to FLAGS, maybe | GLOB_MAGCHAR.  */
	/* If the GLOB_ALTDIRFUNC flag is set, the following functions
	 * are used instead of the normal file access functions. */
	void (__LIBCCALL *gl_closedir)(void *);
#ifdef __USE_GNU
	struct dirent *(__LIBCCALL *gl_readdir)(void *);
#else /* __USE_GNU */
	void *(__LIBCCALL *gl_readdir)(void *);
#endif /* !__USE_GNU */
	void *(__LIBCCALL *gl_opendir)(char const *);
#ifdef __USE_GNU
	int (__LIBCCALL *gl_lstat)(char const *__restrict, struct stat *__restrict);
	int (__LIBCCALL *gl_stat)(char const *__restrict, struct stat *__restrict);
#else /* __USE_GNU */
	int (__LIBCCALL *gl_lstat)(char const *__restrict, void *__restrict);
	int (__LIBCCALL *gl_stat)(char const *__restrict, void *__restrict);
#endif /* !__USE_GNU */
} glob_t;

#ifdef __USE_LARGEFILE64
#ifdef __USE_GNU
struct dirent64;
struct stat64;
#endif /* __USE_GNU */
typedef struct __glob64_struct {
	__size_t gl_pathc;
	char   **gl_pathv;
	__size_t gl_offs;
	int      gl_flags;
	/* If the GLOB_ALTDIRFUNC flag is set, the following functions
	 * are used instead of the normal file access functions.  */
	void (__LIBCCALL *gl_closedir)(void *);
#ifdef __USE_GNU
	struct dirent64 *(__LIBCCALL *gl_readdir)(void *);
#else /* __USE_GNU */
	void *(__LIBCCALL *gl_readdir)(void *);
#endif /* !__USE_GNU */
	void *(__LIBCCALL *gl_opendir)(char const *);
#ifdef __USE_GNU
	int (__LIBCCALL *gl_lstat)(char const *__restrict, struct stat64 *__restrict);
	int (__LIBCCALL *gl_stat)(char const *__restrict, struct stat64 *__restrict);
#else /* __USE_GNU */
	int (__LIBCCALL *gl_lstat)(char const *__restrict, void *__restrict);
	int (__LIBCCALL *gl_stat)(char const *__restrict, void *__restrict);
#endif /* !__USE_GNU */
} glob64_t;
#endif /* __USE_LARGEFILE64 */


typedef int (__LIBCCALL *__glob_errfunc_t)(char const *__path, int __flags);

}

[doc_alias(glob)][ignore] glob32:([nonnull] char const *__restrict pattern, int flags, __glob_errfunc_t errfunc, [nonnull] void *__restrict pglob) -> int = glob?;
[doc_alias(globfree)][ignore] globfree32:(void *pglob) = globfree?;


@@Do glob searching for PATTERN, placing results in PGLOB.
@@The bits defined above may be set in FLAGS.
@@If a directory cannot be opened or read and ERRFUNC is not nil,
@@it is called with the pathname that caused the error, and the
@@`errno' value from the failing call; if it returns non-zero
@@`glob' returns GLOB_ABEND; if it returns zero, the error is ignored.
@@If memory cannot be allocated for PGLOB, GLOB_NOSPACE is returned.
@@Otherwise, `glob' returns zero
[if(defined(__USE_FILE_OFFSET64)),preferred_alias(glob64)]
[if(!defined(__USE_FILE_OFFSET64)),preferred_alias(glob)][noexport][user]
glob:([nonnull] char const *__restrict pattern, int flags,
      [nullable] __glob_errfunc_t errfunc,
      [nonnull] glob_t *__restrict pglob) -> int {
#if defined(__CRT_HAVE_glob)
	return glob32(pattern, flags, errfunc, pglob);
#elif defined(__CRT_HAVE_glob64)
	return glob64(pattern, flags, errfunc, (struct __glob64_struct *)pglob);
#else
	(void)pattern;
	(void)flags;
	(void)errfunc;
	(void)pglob;
	COMPILER_IMPURE();
	return @GLOB_NOSYS@;
#endif
}




@@Free storage allocated in PGLOB by a previous `glob' call
[if(defined(__USE_FILE_OFFSET64)),preferred_alias(globfree64)]
[if(!defined(__USE_FILE_OFFSET64)),preferred_alias(globfree)][noexport][user]
globfree:([nonnull] glob_t *pglob) {
#if defined(__CRT_HAVE_globfree)
	globfree32(pglob);
#elif defined(__CRT_HAVE_globfree64)
	globfree64((struct __glob64_struct *)pglob);
#else
	COMPILER_IMPURE();
	(void)pglob;
#endif
}

%
%#ifdef __USE_LARGEFILE64
[doc_alias(glob)][decl_prefix(struct __glob64_struct;)][noexport][user]
glob64:([nonnull] const char *__restrict pattern, int flags,
        [nullable] __glob_errfunc_t errfunc,
        [nonnull] struct __glob64_struct *__restrict pglob) -> int {
#if defined(__CRT_HAVE_glob)
	return glob32(pattern, flags, errfunc, pglob);
#else
	(void)pattern;
	(void)flags;
	(void)errfunc;
	(void)pglob;
	COMPILER_IMPURE();
	return @GLOB_NOSYS@;
#endif
}

[doc_alias(globfree)][decl_prefix(struct __glob64_struct;)][noexport][user]
globfree64:([nonnull] struct __glob64_struct *pglob) {
#if defined(__CRT_HAVE_globfree)
	globfree32(pglob);
#else
	COMPILER_IMPURE();
	(void)pglob;
#endif
}
%#endif /* __USE_LARGEFILE64 */


%{
#endif /* __CC__ */

__SYSDECL_END

}