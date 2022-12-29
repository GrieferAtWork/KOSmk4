/* HASH CRC-32:0x108ab3c3 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/fts.h) */
/* (#) Portability: DragonFly BSD (/include/fts.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/fts.h) */
/* (#) Portability: FreeBSD       (/include/fts.h) */
/* (#) Portability: GNU C Library (/io/fts.h) */
/* (#) Portability: GNU Hurd      (/usr/include/fts.h) */
/* (#) Portability: NetBSD        (/include/fts.h) */
/* (#) Portability: OpenBSD       (/include/fts.h) */
/* (#) Portability: libc6         (/include/fts.h) */
/* (#) Portability: uClibc        (/include/fts.h) */
#ifndef _FTS_H
#define _FTS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/crt/fts.h>
#include <bits/types.h>

#include <sys/types.h>


#if !defined(FTS_ROOTPARENTLEVEL) && defined(__FTS_ROOTPARENTLEVEL)
#define FTS_ROOTPARENTLEVEL __FTS_ROOTPARENTLEVEL /* ??? */
#endif /* !FTS_ROOTPARENTLEVEL && __FTS_ROOTPARENTLEVEL */
#if !defined(FTS_ROOTLEVEL) && defined(__FTS_ROOTLEVEL)
#define FTS_ROOTLEVEL       __FTS_ROOTLEVEL       /* ??? */
#endif /* !FTS_ROOTLEVEL && __FTS_ROOTLEVEL */

#if !defined(FTS_D) && defined(__FTS_D)
#define FTS_D       __FTS_D       /* ??? */
#endif /* !FTS_D && __FTS_D */
#if !defined(FTS_DC) && defined(__FTS_DC)
#define FTS_DC      __FTS_DC      /* ??? */
#endif /* !FTS_DC && __FTS_DC */
#if !defined(FTS_DEFAULT) && defined(__FTS_DEFAULT)
#define FTS_DEFAULT __FTS_DEFAULT /* ??? */
#endif /* !FTS_DEFAULT && __FTS_DEFAULT */
#if !defined(FTS_DNR) && defined(__FTS_DNR)
#define FTS_DNR     __FTS_DNR     /* ??? */
#endif /* !FTS_DNR && __FTS_DNR */
#if !defined(FTS_DOT) && defined(__FTS_DOT)
#define FTS_DOT     __FTS_DOT     /* ??? */
#endif /* !FTS_DOT && __FTS_DOT */
#if !defined(FTS_DP) && defined(__FTS_DP)
#define FTS_DP      __FTS_DP      /* ??? */
#endif /* !FTS_DP && __FTS_DP */
#if !defined(FTS_ERR) && defined(__FTS_ERR)
#define FTS_ERR     __FTS_ERR     /* ??? */
#endif /* !FTS_ERR && __FTS_ERR */
#if !defined(FTS_F) && defined(__FTS_F)
#define FTS_F       __FTS_F       /* ??? */
#endif /* !FTS_F && __FTS_F */
#if !defined(FTS_INIT) && defined(__FTS_INIT)
#define FTS_INIT    __FTS_INIT    /* ??? */
#endif /* !FTS_INIT && __FTS_INIT */
#if !defined(FTS_NS) && defined(__FTS_NS)
#define FTS_NS      __FTS_NS      /* ??? */
#endif /* !FTS_NS && __FTS_NS */
#if !defined(FTS_NSOK) && defined(__FTS_NSOK)
#define FTS_NSOK    __FTS_NSOK    /* ??? */
#endif /* !FTS_NSOK && __FTS_NSOK */
#if !defined(FTS_SL) && defined(__FTS_SL)
#define FTS_SL      __FTS_SL      /* ??? */
#endif /* !FTS_SL && __FTS_SL */
#if !defined(FTS_SLNONE) && defined(__FTS_SLNONE)
#define FTS_SLNONE  __FTS_SLNONE  /* ??? */
#endif /* !FTS_SLNONE && __FTS_SLNONE */
#if !defined(FTS_W) && defined(__FTS_W)
#define FTS_W       __FTS_W       /* ??? */
#endif /* !FTS_W && __FTS_W */

#if !defined(FTS_DONTCHDIR) && defined(__FTS_DONTCHDIR)
#define FTS_DONTCHDIR __FTS_DONTCHDIR /* ??? */
#endif /* !FTS_DONTCHDIR && __FTS_DONTCHDIR */
#if !defined(FTS_SYMFOLLOW) && defined(__FTS_SYMFOLLOW)
#define FTS_SYMFOLLOW __FTS_SYMFOLLOW /* ??? */
#endif /* !FTS_SYMFOLLOW && __FTS_SYMFOLLOW */

/* FTS instruction codes. */
#if !defined(FTS_AGAIN) && defined(__FTS_AGAIN)
#define FTS_AGAIN   __FTS_AGAIN   /* ??? */
#endif /* !FTS_AGAIN && __FTS_AGAIN */
#if !defined(FTS_FOLLOW) && defined(__FTS_FOLLOW)
#define FTS_FOLLOW  __FTS_FOLLOW  /* ??? */
#endif /* !FTS_FOLLOW && __FTS_FOLLOW */
#if !defined(FTS_NOINSTR) && defined(__FTS_NOINSTR)
#define FTS_NOINSTR __FTS_NOINSTR /* ??? */
#endif /* !FTS_NOINSTR && __FTS_NOINSTR */
#if !defined(FTS_SKIP) && defined(__FTS_SKIP)
#define FTS_SKIP    __FTS_SKIP    /* ??? */
#endif /* !FTS_SKIP && __FTS_SKIP */

/* FTS open options. */
#if !defined(FTS_COMFOLLOW) && defined(__FTS_COMFOLLOW)
#define FTS_COMFOLLOW  __FTS_COMFOLLOW  /* ??? */
#endif /* !FTS_COMFOLLOW && __FTS_COMFOLLOW */
#if !defined(FTS_LOGICAL) && defined(__FTS_LOGICAL)
#define FTS_LOGICAL    __FTS_LOGICAL    /* ??? */
#endif /* !FTS_LOGICAL && __FTS_LOGICAL */
#if !defined(FTS_NOCHDIR) && defined(__FTS_NOCHDIR)
#define FTS_NOCHDIR    __FTS_NOCHDIR    /* ??? */
#endif /* !FTS_NOCHDIR && __FTS_NOCHDIR */
#if !defined(FTS_NOSTAT) && defined(__FTS_NOSTAT)
#define FTS_NOSTAT     __FTS_NOSTAT     /* ??? */
#endif /* !FTS_NOSTAT && __FTS_NOSTAT */
#if !defined(FTS_PHYSICAL) && defined(__FTS_PHYSICAL)
#define FTS_PHYSICAL   __FTS_PHYSICAL   /* ??? */
#endif /* !FTS_PHYSICAL && __FTS_PHYSICAL */
#if !defined(FTS_SEEDOT) && defined(__FTS_SEEDOT)
#define FTS_SEEDOT     __FTS_SEEDOT     /* ??? */
#endif /* !FTS_SEEDOT && __FTS_SEEDOT */
#if !defined(FTS_XDEV) && defined(__FTS_XDEV)
#define FTS_XDEV       __FTS_XDEV       /* ??? */
#endif /* !FTS_XDEV && __FTS_XDEV */
#if !defined(FTS_WHITEOUT) && defined(__FTS_WHITEOUT)
#define FTS_WHITEOUT   __FTS_WHITEOUT   /* ??? */
#endif /* !FTS_WHITEOUT && __FTS_WHITEOUT */
#if !defined(FTS_OPTIONMASK) && defined(__FTS_OPTIONMASK)
#define FTS_OPTIONMASK __FTS_OPTIONMASK /* ??? */
#endif /* !FTS_OPTIONMASK && __FTS_OPTIONMASK */
#if !defined(FTS_NAMEONLY) && defined(__FTS_NAMEONLY)
#define FTS_NAMEONLY   __FTS_NAMEONLY   /* ??? */
#endif /* !FTS_NAMEONLY && __FTS_NAMEONLY */
#if !defined(FTS_STOP) && defined(__FTS_STOP)
#define FTS_STOP       __FTS_STOP       /* ??? */
#endif /* !FTS_STOP && __FTS_STOP */


#ifdef __CC__
__SYSDECL_BEGIN

typedef struct __fts FTS;
typedef struct _ftsent FTSENT;
#ifdef __USE_LARGEFILE64
typedef struct _ftsent64 FTSENT64;
typedef struct __fts64 FTS64;
#endif /* __USE_LARGEFILE64 */

#if defined(__CRT_HAVE_fts_children) && (!defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64))
/* >> fts_children(3), fts_children64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1),FTSENT *,__NOTHROW_RPC,fts_children,(FTS *__ftsp, __STDC_INT_AS_UINT_T __instr),(__ftsp,__instr))
#elif defined(__CRT_HAVE_fts64_children) && (defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64))
/* >> fts_children(3), fts_children64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),FTSENT *,__NOTHROW_RPC,fts_children,(FTS *__ftsp, __STDC_INT_AS_UINT_T __instr),fts64_children,(__ftsp,__instr))
#endif /* ... */
#if defined(__CRT_HAVE_fts_children) && (!defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64))
/* >> fts_close(3), fts_close64(3) */
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,fts_close,(FTS *__ftsp),fts_children,(__ftsp))
#elif defined(__CRT_HAVE_fts64_close) && (defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64))
/* >> fts_close(3), fts_close64(3) */
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,fts_close,(FTS *__ftsp),fts64_close,(__ftsp))
#endif /* ... */
#if defined(__CRT_HAVE_fts_open) && (!defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64))
/* >> fts_open(3), fts_open64(3)
 * @param: options: Set of `FTS_COMFOLLOW | FTS_LOGICAL | ... | FTS_STOP' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),FTS *,__NOTHROW_RPC,fts_open,(char *const *__path_argv, __STDC_INT_AS_UINT_T __options, int (__LIBKCALL *__compar)(FTSENT const **__lhs, FTSENT const **__rhs)),(__path_argv,__options,__compar))
#elif defined(__CRT_HAVE_fts64_open) && (defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64))
/* >> fts_open(3), fts_open64(3)
 * @param: options: Set of `FTS_COMFOLLOW | FTS_LOGICAL | ... | FTS_STOP' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),FTS *,__NOTHROW_RPC,fts_open,(char *const *__path_argv, __STDC_INT_AS_UINT_T __options, int (__LIBKCALL *__compar)(FTSENT const **__lhs, FTSENT const **__rhs)),fts64_open,(__path_argv,__options,__compar))
#endif /* ... */
#if defined(__CRT_HAVE_fts_read) && (!defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64))
/* >> fts_read(3), fts_read64(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1),FTSENT *,__NOTHROW_RPC,fts_read,(FTS *__ftsp),(__ftsp))
#elif defined(__CRT_HAVE_fts64_read) && (defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64))
/* >> fts_read(3), fts_read64(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),FTSENT *,__NOTHROW_RPC,fts_read,(FTS *__ftsp),fts64_read,(__ftsp))
#endif /* ... */
#if defined(__CRT_HAVE_fts_set) && (!defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64))
/* >> fts_set(3), fts_set64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
__CDECLARE(__ATTR_INOUT(1) __ATTR_INOUT(2),int,__NOTHROW_NCX,fts_set,(FTS *__ftsp, FTSENT *__f, __STDC_INT_AS_UINT_T __instr),(__ftsp,__f,__instr))
#elif defined(__CRT_HAVE_fts64_set) && (defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64))
/* >> fts_set(3), fts_set64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_INOUT(2),int,__NOTHROW_NCX,fts_set,(FTS *__ftsp, FTSENT *__f, __STDC_INT_AS_UINT_T __instr),fts64_set,(__ftsp,__f,__instr))
#endif /* ... */


#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_fts_children) && defined(__FTS32_MATCHES_FTS64)
/* >> fts_children(3), fts_children64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),FTSENT64 *,__NOTHROW_RPC,fts64_children,(FTS64 *__ftsp, __STDC_INT_AS_UINT_T __instr),fts_children,(__ftsp,__instr))
#elif defined(__CRT_HAVE_fts64_children)
/* >> fts_children(3), fts_children64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1),FTSENT64 *,__NOTHROW_RPC,fts64_children,(FTS64 *__ftsp, __STDC_INT_AS_UINT_T __instr),(__ftsp,__instr))
#endif /* ... */
#if defined(__CRT_HAVE_fts_close) && defined(__FTS32_MATCHES_FTS64)
/* >> fts_close(3), fts_close64(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),int,__NOTHROW_RPC,fts64_close,(FTS64 *__ftsp),fts_close,(__ftsp))
#elif defined(__CRT_HAVE_fts64_close)
/* >> fts_close(3), fts_close64(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1),int,__NOTHROW_RPC,fts64_close,(FTS64 *__ftsp),(__ftsp))
#endif /* ... */
#if defined(__CRT_HAVE_fts_open) && defined(__FTS32_MATCHES_FTS64)
/* >> fts_open(3), fts_open64(3)
 * @param: options: Set of `FTS_COMFOLLOW | FTS_LOGICAL | ... | FTS_STOP' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),FTS64 *,__NOTHROW_RPC,fts64_open,(char *const *__path_argv, __STDC_INT_AS_UINT_T __options, int (__LIBKCALL *__compar)(FTSENT64 const **__lhs, FTSENT64 const **__rhs)),fts_open,(__path_argv,__options,__compar))
#elif defined(__CRT_HAVE_fts64_open)
/* >> fts_open(3), fts_open64(3)
 * @param: options: Set of `FTS_COMFOLLOW | FTS_LOGICAL | ... | FTS_STOP' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),FTS64 *,__NOTHROW_RPC,fts64_open,(char *const *__path_argv, __STDC_INT_AS_UINT_T __options, int (__LIBKCALL *__compar)(FTSENT64 const **__lhs, FTSENT64 const **__rhs)),(__path_argv,__options,__compar))
#endif /* ... */
#if defined(__CRT_HAVE_fts_read) && defined(__FTS32_MATCHES_FTS64)
/* >> fts_read(3), fts_read64(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),FTSENT64 *,__NOTHROW_RPC,fts64_read,(FTS64 *__ftsp),fts_read,(__ftsp))
#elif defined(__CRT_HAVE_fts64_read)
/* >> fts_read(3), fts_read64(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1),FTSENT64 *,__NOTHROW_RPC,fts64_read,(FTS64 *__ftsp),(__ftsp))
#endif /* ... */
#if defined(__CRT_HAVE_fts_set) && defined(__FTS32_MATCHES_FTS64)
/* >> fts_set(3), fts_set64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_INOUT(2),int,__NOTHROW_NCX,fts64_set,(FTS64 *__ftsp, FTSENT64 *__f, __STDC_INT_AS_UINT_T __instr),fts_set,(__ftsp,__f,__instr))
#elif defined(__CRT_HAVE_fts64_set)
/* >> fts_set(3), fts_set64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
__CDECLARE(__ATTR_INOUT(1) __ATTR_INOUT(2),int,__NOTHROW_NCX,fts64_set,(FTS64 *__ftsp, FTSENT64 *__f, __STDC_INT_AS_UINT_T __instr),(__ftsp,__f,__instr))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_FTS_H */
