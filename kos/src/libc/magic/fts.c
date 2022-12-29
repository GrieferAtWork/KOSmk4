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
%(c_prefix){
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
}

%[default:section(".text.crt{|.dos}.fs.fts")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/crt/fts.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

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

}
%[define_replacement(FTS      = "struct __fts")]
%[define_replacement(FTSENT   = "struct _ftsent")]
%[define_replacement(FTS64    = "struct __fts64")]
%[define_replacement(FTSENT64 = "struct __ftsent64")]



@@>> fts_children(3), fts_children64(3)
@@@param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP'
[[cp, wunused, decl_include("<features.h>", "<bits/crt/fts.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/fts.h>")!defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64)), alias("fts_children")]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/fts.h>") defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64)), alias("fts64_children")]]
FTSENT *fts_children([[inout]] FTS *ftsp, __STDC_INT_AS_UINT_T instr);

@@>> fts_close(3), fts_close64(3)
[[decl_include("<bits/crt/fts.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/fts.h>")!defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64)), alias("fts_children")]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/fts.h>") defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64)), alias("fts64_close")]]
int fts_close([[inout]] FTS *ftsp);


@@>> fts_open(3), fts_open64(3)
@@@param: options: Set of `FTS_COMFOLLOW | FTS_LOGICAL | ... | FTS_STOP'
[[cp, nodos /*TODO*/, wunused, decl_include("<features.h>", "<bits/crt/fts.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/fts.h>")!defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64)), alias("fts_open")]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/fts.h>") defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64)), alias("fts64_open")]]
FTS *fts_open([[in]] char *const *path_argv, __STDC_INT_AS_UINT_T options,
              int (LIBKCALL *compar)(FTSENT const **lhs, FTSENT const **rhs));

@@>> fts_read(3), fts_read64(3)
[[cp, wunused, decl_include("<bits/crt/fts.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/fts.h>")!defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64)), alias("fts_read")]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/fts.h>") defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64)), alias("fts64_read")]]
FTSENT *fts_read([[inout]] FTS *ftsp);

@@>> fts_set(3), fts_set64(3)
@@@param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP'
[[decl_include("<features.h>", "<bits/crt/fts.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/fts.h>")!defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64)), alias("fts_set")]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/fts.h>") defined(__USE_FILE_OFFSET64) || defined(__FTS32_MATCHES_FTS64)), alias("fts64_set")]]
int fts_set([[inout]] FTS *ftsp,
            [[inout]] FTSENT *f,
            __STDC_INT_AS_UINT_T instr);


%
%
%#ifdef __USE_LARGEFILE64
[[cp, wunused, decl_include("<features.h>", "<bits/crt/fts.h>")]]
[[doc_alias("fts_children"), preferred_fts64_variant_of(fts_children)]]
FTSENT64 *fts64_children([[inout]] FTS64 *ftsp, __STDC_INT_AS_UINT_T instr);

[[cp, wunused, decl_include("<bits/crt/fts.h>")]]
[[doc_alias("fts_close"), preferred_fts64_variant_of(fts_close)]]
int fts64_close([[inout]] FTS64 *ftsp);

[[cp, nodos /*TODO*/, wunused, decl_include("<features.h>", "<bits/crt/fts.h>")]]
[[doc_alias("fts_open"), preferred_fts64_variant_of(fts_open)]]
FTS64 *fts64_open([[in]] char *const *path_argv,
                  __STDC_INT_AS_UINT_T options,
                  int (LIBKCALL *compar)(FTSENT64 const **lhs, FTSENT64 const **rhs));

[[cp, wunused, decl_include("<bits/crt/fts.h>")]]
[[doc_alias("fts_read"), preferred_fts64_variant_of(fts_read)]]
FTSENT64 *fts64_read([[inout]] FTS64 *ftsp);

[[decl_include("<features.h>", "<bits/crt/fts.h>")]]
[[doc_alias("fts_set"), preferred_fts64_variant_of(fts_set)]]
int fts64_set([[inout]] FTS64 *ftsp,
              [[inout]] FTSENT64 *f,
              __STDC_INT_AS_UINT_T instr);

%#endif /* __USE_LARGEFILE64 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
