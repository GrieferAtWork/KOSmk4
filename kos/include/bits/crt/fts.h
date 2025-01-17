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
#ifndef _BITS_CRT_FTS_H
#define _BITS_CRT_FTS_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/stat.h> /* __STAT32_MATCHES_STAT64 */
#include <bits/types.h>

#define __FTS_ROOTPARENTLEVEL (-1) /* ??? */
#define __FTS_ROOTLEVEL       0    /* ??? */

#define __FTS_D       1  /* ??? */
#define __FTS_DC      2  /* ??? */
#define __FTS_DEFAULT 3  /* ??? */
#define __FTS_DNR     4  /* ??? */
#define __FTS_DOT     5  /* ??? */
#define __FTS_DP      6  /* ??? */
#define __FTS_ERR     7  /* ??? */
#define __FTS_F       8  /* ??? */
#define __FTS_INIT    9  /* ??? */
#define __FTS_NS      10 /* ??? */
#define __FTS_NSOK    11 /* ??? */
#define __FTS_SL      12 /* ??? */
#define __FTS_SLNONE  13 /* ??? */
#define __FTS_W       14 /* ??? */

#define __FTS_DONTCHDIR 0x01 /* ??? */
#define __FTS_SYMFOLLOW 0x02 /* ??? */

/* FTS instruction codes. */
#define __FTS_AGAIN   1 /* ??? */
#define __FTS_FOLLOW  2 /* ??? */
#define __FTS_NOINSTR 3 /* ??? */
#define __FTS_SKIP    4 /* ??? */

/* FTS open options. */
#define __FTS_COMFOLLOW  0x0001 /* ??? */
#define __FTS_LOGICAL    0x0002 /* ??? */
#define __FTS_NOCHDIR    0x0004 /* ??? */
#define __FTS_NOSTAT     0x0008 /* ??? */
#define __FTS_PHYSICAL   0x0010 /* ??? */
#define __FTS_SEEDOT     0x0020 /* ??? */
#define __FTS_XDEV       0x0040 /* ??? */
#define __FTS_WHITEOUT   0x0080 /* ??? */
#define __FTS_OPTIONMASK 0x00ff /* ??? */
#define __FTS_NAMEONLY   0x0100 /* ??? */
#define __FTS_STOP       0x0200 /* ??? */


#if (__SIZEOF_INO32_T__ == __SIZEOF_INO64_T__ && \
     defined(__STAT32_MATCHES_STAT64))
#define __FTS32_MATCHES_FTS64
#endif /* ... */

#ifdef __CC__
__DECL_BEGIN

struct stat;
struct stat64;

#ifdef __USE_FILE_OFFSET64
struct __ftsent32
#else /* __USE_FILE_OFFSET64 */
#define __ftsent32 _ftsent
struct _ftsent
#endif /* !__USE_FILE_OFFSET64 */
{
	struct __ftsent32              *fts_cycle;   /* ??? */
	struct __ftsent32              *fts_parent;  /* ??? */
	struct __ftsent32              *fts_link;    /* ??? */
	__LONGPTR_TYPE__                fts_number;  /* ??? */
	void                           *fts_pointer; /* ??? */
	char                           *fts_accpath; /* ??? */
	char                           *fts_path;    /* ??? */
	__errno_t                       fts_errno;   /* ??? */
	__fd_t                          fts_symfd;   /* ??? */
	unsigned short                  fts_pathlen; /* ??? */
	unsigned short                  fts_namelen; /* ??? */
	__ino32_t                       fts_ino;     /* ??? */
	__dev_t                         fts_dev;     /* ??? */
	__nlink_t                       fts_nlink;   /* ??? */
	short                           fts_level;   /* One of `FTS_ROOTPARENTLEVEL', `FTS_ROOTLEVEL' */
	unsigned short                  fts_info;    /* One of `FTS_D', `FTS_DC', ..., `FTS_W' */
	unsigned short                  fts_flags;   /* Set of `FTS_DONTCHDIR | FTS_SYMFOLLOW' */
	unsigned short                  fts_instr;   /* One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
	struct stat                    *fts_statp;   /* ??? */
	__COMPILER_FLEXIBLE_ARRAY(char, fts_name);   /* ??? */
};

#ifdef __USE_LARGEFILE64
struct _ftsent64
#define __ftsent64 _ftsent64
#else /* __USE_LARGEFILE64 */
struct __ftsent64
#endif /* !__USE_LARGEFILE64 */
{
	struct __ftsent64              *fts_cycle;   /* ??? */
	struct __ftsent64              *fts_parent;  /* ??? */
	struct __ftsent64              *fts_link;    /* ??? */
	__LONGPTR_TYPE__                fts_number;  /* ??? */
	void                           *fts_pointer; /* ??? */
	char                           *fts_accpath; /* ??? */
	char                           *fts_path;    /* ??? */
	__errno_t                       fts_errno;   /* ??? */
	__fd_t                          fts_symfd;   /* ??? */
	unsigned short                  fts_pathlen; /* ??? */
	unsigned short                  fts_namelen; /* ??? */
	__ino64_t                       fts_ino;     /* ??? */
	__dev_t                         fts_dev;     /* ??? */
	__nlink_t                       fts_nlink;   /* ??? */
	short                           fts_level;   /* One of `FTS_ROOTPARENTLEVEL', `FTS_ROOTLEVEL' */
	unsigned short                  fts_info;    /* One of `FTS_D', `FTS_DC', ..., `FTS_W' */
	unsigned short                  fts_flags;   /* Set of `FTS_DONTCHDIR | FTS_SYMFOLLOW' */
	unsigned short                  fts_instr;   /* One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
	struct stat64                  *fts_statp;   /* ??? */
	__COMPILER_FLEXIBLE_ARRAY(char, fts_name);   /* ??? */
};


#ifdef __USE_FILE_OFFSET64
struct __fts32
#else /* __USE_FILE_OFFSET64 */
#define __fts32 __fts
struct __fts
#endif /* !__USE_FILE_OFFSET64 */
{
	struct __ftsent32   *fts_cur;                                 /* ??? */
	struct __ftsent32   *fts_child;                               /* ??? */
	struct __ftsent32  **fts_array;                               /* ??? */
	__dev_t              fts_dev;                                 /* ??? */
	char                *fts_path;                                /* ??? */
	__fd_t               fts_rfd;                                 /* ??? */
	__STDC_INT_AS_UINT_T fts_pathlen;                             /* ??? */
	__STDC_INT_AS_UINT_T fts_nitems;                              /* ??? */
	int (__LIBKCALL     *fts_compar)(void const *, void const *); /* ??? */
	__STDC_INT_AS_UINT_T fts_options;                             /* Set of `FTS_COMFOLLOW | FTS_LOGICAL | ... | FTS_STOP' */
};

#ifdef __USE_FILE_OFFSET64
#define __fts64 __fts
struct __fts
#else /* __USE_FILE_OFFSET64 */
struct __fts64
#endif /* !__USE_FILE_OFFSET64 */
{
	struct __ftsent64   *fts_cur;                                 /* ??? */
	struct __ftsent64   *fts_child;                               /* ??? */
	struct __ftsent64  **fts_array;                               /* ??? */
	__dev_t              fts_dev;                                 /* ??? */
	char                *fts_path;                                /* ??? */
	__fd_t               fts_rfd;                                 /* ??? */
	__STDC_INT_AS_UINT_T fts_pathlen;                             /* ??? */
	__STDC_INT_AS_UINT_T fts_nitems;                              /* ??? */
	int (__LIBKCALL     *fts_compar)(void const *, void const *); /* ??? */
	__STDC_INT_AS_UINT_T fts_options;                             /* Set of `FTS_COMFOLLOW | FTS_LOGICAL | ... | FTS_STOP' */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_FTS_H */
