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
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/regex.h) */
/* (#) Portability: DJGPP         (/include/regex.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/regex.h) */
/* (#) Portability: FreeBSD       (/include/regex.h) */
/* (#) Portability: GNU C Library (/posix/regex.h) */
/* (#) Portability: NetBSD        (/include/regex.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/regex.h) */
/* (#) Portability: OpenBSD       (/include/regex.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/regex.h) */
/* (#) Portability: diet libc     (/include/regex.h) */
/* (#) Portability: libc4/5       (/include/regex.h) */
/* (#) Portability: libc6         (/include/regex.h) */
/* (#) Portability: mintlib       (/include/regex.h) */
/* (#) Portability: musl libc     (/include/regex.h) */
/* (#) Portability: uClibc        (/include/regex.h) */
}

%[define_replacement(s_reg_t = __LONGPTR_TYPE__)]
%[define_replacement(active_reg_t = __ULONGPTR_TYPE__)]
%[define_replacement(reg_syntax_t = __reg_syntax_t)]
%[define_replacement(regex_t = "struct re_pattern_buffer")]
%[define_replacement(regoff_t = __regoff_t)]
%[define_replacement(regmatch_t = "struct __regmatch")]
%[define_replacement(re_syntax_options = __LOCAL_re_syntax_options)]
%[define_type_class(__reg_syntax_t = "TIn(__SIZEOF_REG_SYNTAX_T__)")]
%[define_type_class(__regoff_t = "TIn(__SIZEOF_REGOFF_T__)")]

%[default:section(".text.crt{|.dos}.utility.regex")]

%[assume_defined_in_kos_userspace(REG_ENOSYS, __REG_ENOSYS)]
%[assume_defined_in_kos_userspace(REG_NOERROR, __REG_NOERROR)]
%[assume_defined_in_kos_userspace(REG_NOMATCH, __REG_NOMATCH)]
%[assume_defined_in_kos_userspace(REG_BADPAT, __REG_BADPAT)]
%[assume_defined_in_kos_userspace(REG_ECOLLATE, __REG_ECOLLATE)]
%[assume_defined_in_kos_userspace(REG_ECTYPE, __REG_ECTYPE)]
%[assume_defined_in_kos_userspace(REG_EESCAPE, __REG_EESCAPE)]
%[assume_defined_in_kos_userspace(REG_ESUBREG, __REG_ESUBREG)]
%[assume_defined_in_kos_userspace(REG_EBRACK, __REG_EBRACK)]
%[assume_defined_in_kos_userspace(REG_EPAREN, __REG_EPAREN)]
%[assume_defined_in_kos_userspace(REG_EBRACE, __REG_EBRACE)]
%[assume_defined_in_kos_userspace(REG_BADBR, __REG_BADBR)]
%[assume_defined_in_kos_userspace(REG_ERANGE, __REG_ERANGE)]
%[assume_defined_in_kos_userspace(REG_ESPACE, __REG_ESPACE)]
%[assume_defined_in_kos_userspace(REG_BADRPT, __REG_BADRPT)]
%[assume_defined_in_kos_userspace(REG_EEND, __REG_EEND)]
%[assume_defined_in_kos_userspace(REG_ESIZE, __REG_ESIZE)]
%[assume_defined_in_kos_userspace(REG_ERPAREN, __REG_ERPAREN)]
%[assume_defined_in_kos_userspace(REG_EILLSEQ, __REG_EILLSEQ)]
%[assume_defined_in_kos_userspace(REG_EILLSET, __REG_EILLSET)]
%[assume_defined_in_kos_userspace(RE_BACKSLASH_ESCAPE_IN_LISTS, __RE_BACKSLASH_ESCAPE_IN_LISTS)]
%[assume_defined_in_kos_userspace(RE_BK_PLUS_QM, __RE_BK_PLUS_QM)]
%[assume_defined_in_kos_userspace(RE_CHAR_CLASSES, __RE_CHAR_CLASSES)]
%[assume_defined_in_kos_userspace(RE_CONTEXT_INDEP_ANCHORS, __RE_CONTEXT_INDEP_ANCHORS)]
%[assume_defined_in_kos_userspace(RE_CONTEXT_INDEP_OPS, __RE_CONTEXT_INDEP_OPS)]
%[assume_defined_in_kos_userspace(RE_CONTEXT_INVALID_OPS, __RE_CONTEXT_INVALID_OPS)]
%[assume_defined_in_kos_userspace(RE_DOT_NEWLINE, __RE_DOT_NEWLINE)]
%[assume_defined_in_kos_userspace(RE_DOT_NOT_NULL, __RE_DOT_NOT_NULL)]
%[assume_defined_in_kos_userspace(RE_HAT_LISTS_NOT_NEWLINE, __RE_HAT_LISTS_NOT_NEWLINE)]
%[assume_defined_in_kos_userspace(RE_INTERVALS, __RE_INTERVALS)]
%[assume_defined_in_kos_userspace(RE_LIMITED_OPS, __RE_LIMITED_OPS)]
%[assume_defined_in_kos_userspace(RE_NEWLINE_ALT, __RE_NEWLINE_ALT)]
%[assume_defined_in_kos_userspace(RE_NO_BK_BRACES, __RE_NO_BK_BRACES)]
%[assume_defined_in_kos_userspace(RE_NO_BK_PARENS, __RE_NO_BK_PARENS)]
%[assume_defined_in_kos_userspace(RE_NO_BK_REFS, __RE_NO_BK_REFS)]
%[assume_defined_in_kos_userspace(RE_NO_BK_VBAR, __RE_NO_BK_VBAR)]
%[assume_defined_in_kos_userspace(RE_NO_EMPTY_RANGES, __RE_NO_EMPTY_RANGES)]
%[assume_defined_in_kos_userspace(RE_UNMATCHED_RIGHT_PAREN_ORD, __RE_UNMATCHED_RIGHT_PAREN_ORD)]
%[assume_defined_in_kos_userspace(RE_NO_POSIX_BACKTRACKING, __RE_NO_POSIX_BACKTRACKING)]
%[assume_defined_in_kos_userspace(RE_NO_GNU_OPS, __RE_NO_GNU_OPS)]
%[assume_defined_in_kos_userspace(RE_DEBUG, __RE_DEBUG)]
%[assume_defined_in_kos_userspace(RE_INVALID_INTERVAL_ORD, __RE_INVALID_INTERVAL_ORD)]
%[assume_defined_in_kos_userspace(RE_ICASE, __RE_ICASE)]
%[assume_defined_in_kos_userspace(RE_CARET_ANCHORS_HERE, __RE_CARET_ANCHORS_HERE)]
%[assume_defined_in_kos_userspace(RE_CONTEXT_INVALID_DUP, __RE_CONTEXT_INVALID_DUP)]
%[assume_defined_in_kos_userspace(RE_NO_SUB, __RE_NO_SUB)]
%[assume_defined_in_kos_userspace(RE_ANCHORS_IGNORE_EFLAGS, __RE_ANCHORS_IGNORE_EFLAGS)]
%[assume_defined_in_kos_userspace(RE_NO_UTF8, __RE_NO_UTF8)]
%[assume_defined_in_kos_userspace(RE_NO_KOS_OPS, __RE_NO_KOS_OPS)]
%[assume_defined_in_kos_userspace(REG_EXTENDED, __REG_EXTENDED)]
%[assume_defined_in_kos_userspace(REG_ICASE, __REG_ICASE)]
%[assume_defined_in_kos_userspace(REG_NEWLINE, __REG_NEWLINE)]
%[assume_defined_in_kos_userspace(REG_NOSUB, __REG_NOSUB)]
%[assume_defined_in_kos_userspace(REG_NOTBOL, __REG_NOTBOL)]
%[assume_defined_in_kos_userspace(REG_NOTEOL, __REG_NOTEOL)]
%[assume_defined_in_kos_userspace(REG_STARTEND, __REG_STARTEND)]

%(auto_source){
#include "../libc/globals.h"
}

%(auto_header){
#include <bits/crt/format-printer.h>
}

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#include <asm/crt/limits.h> /* __RE_DUP_MAX */
#include <asm/crt/regex.h>
}%[insert:prefix(
#include <bits/crt/regex.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __USE_KOS
#include <bits/crt/format-printer.h>
#include <bits/os/iovec.h>
#endif /* __USE_KOS */

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

/* NOTE: On KOS, regex is implemented by a dedicated library that gets loaded by libc
 *       once  the demand to do so comes up,  in order to emulate POSIX and GNU regex
 *       functionality. If you intend on making use of this library, its main  header
 *       can be included as `<libregex/regcomp.h>' and `<libregex/regexec.h>' */

__SYSDECL_BEGIN

/* Regex error codes, as returned by `regcomp(3)', `regexec(3)', and other functions. */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum {
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifdef __REG_ENOSYS
	REG_ENOSYS   = __REG_ENOSYS, /* Returned when libc.so fails to load `libregex.so' for some reason */
#endif /* __REG_ENOSYS */
#endif /* __USE_XOPEN || __USE_XOPEN2K */
#ifdef __REG_NOERROR
	REG_NOERROR  = __REG_NOERROR, /* Success. */
#endif /* __REG_NOERROR */
#ifdef __REG_NOMATCH
	REG_NOMATCH  = __REG_NOMATCH, /* Didn't find a match (for `regexec(3)'). */
#endif /* __REG_NOMATCH */
#ifdef __REG_BADPAT
	REG_BADPAT   = __REG_BADPAT, /* General pattern syntax error. */
#endif /* __REG_BADPAT */
#ifdef __REG_ECOLLATE
	REG_ECOLLATE = __REG_ECOLLATE, /* ??? */
#endif /* __REG_ECOLLATE */
#ifdef __REG_ECTYPE
	REG_ECTYPE   = __REG_ECTYPE, /* Invalid/unknown character class name. */
#endif /* __REG_ECTYPE */
#ifdef __REG_EESCAPE
	REG_EESCAPE  = __REG_EESCAPE, /* Trailing '\'. */
#endif /* __REG_EESCAPE */
#ifdef __REG_ESUBREG
	REG_ESUBREG  = __REG_ESUBREG, /* Back reference to group that was never initialized. */
#endif /* __REG_ESUBREG */
#ifdef __REG_EBRACK
	REG_EBRACK   = __REG_EBRACK, /* Unmatched '['. */
#endif /* __REG_EBRACK */
#ifdef __REG_EPAREN
	REG_EPAREN   = __REG_EPAREN, /* Unmatched '('. */
#endif /* __REG_EPAREN */
#ifdef __REG_EBRACE
	REG_EBRACE   = __REG_EBRACE, /* Unmatched '{'. */
#endif /* __REG_EBRACE */
#ifdef __REG_BADBR
	REG_BADBR    = __REG_BADBR, /* Invalid contents of '{...}'. */
#endif /* __REG_BADBR */
#ifdef __REG_ERANGE
	REG_ERANGE   = __REG_ERANGE, /* Invalid range end (e.g. '[z-a]'). */
#endif /* __REG_ERANGE */
#ifdef __REG_ESPACE
	REG_ESPACE   = __REG_ESPACE, /* Out of memory. */
#endif /* __REG_ESPACE */
#ifdef __REG_BADRPT
	REG_BADRPT   = __REG_BADRPT, /* Nothing is preceding '+', '*', '?' or '{'. */
#endif /* __REG_BADRPT */
#ifdef __REG_EEND
	REG_EEND     = __REG_EEND, /* Unexpected end of pattern. */
#endif /* __REG_EEND */
#ifdef __REG_ESIZE
	REG_ESIZE    = __REG_ESIZE, /* Too large (pattern violates some hard limit that isn't the currently available ram) */
#endif /* __REG_ESIZE */
#ifdef __REG_ERPAREN
	REG_ERPAREN  = __REG_ERPAREN, /* Unmatched ')' (only when `RE_UNMATCHED_RIGHT_PAREN_ORD' was set) */
#endif /* __REG_ERPAREN */
#ifdef __REG_EMPTY
	REG_EMPTY    = __REG_EMPTY, /* ??? */
#endif /* __REG_EMPTY */
#ifdef __REG_ASSERT
	REG_ASSERT   = __REG_ASSERT, /* ??? */
#endif /* __REG_ASSERT */
#ifdef __REG_INVARG
	REG_INVARG   = __REG_INVARG, /* ??? */
#endif /* __REG_INVARG */
#ifdef __REG_ATOI
	REG_ATOI     = __REG_ATOI, /* ??? */
#endif /* __REG_ATOI */
#ifdef __REG_ITOA
	REG_ITOA     = __REG_ITOA, /* ??? */
#endif /* __REG_ITOA */
#ifdef __REG_EILLSEQ
	REG_EILLSEQ  = __REG_EILLSEQ, /* Illegal unicode character (when `RE_NO_UTF8' wasn't set) */
#endif /* __REG_EILLSEQ */
#ifdef __REG_EILLSET
	REG_EILLSET  = __REG_EILLSET, /* Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]") */
#endif /* __REG_EILLSET */
} reg_errcode_t;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifdef __REG_ENOSYS
#define REG_ENOSYS   REG_ENOSYS   /* Returned when libc.so fails to load `libregex.so' for some reason */
#endif /* __REG_ENOSYS */
#endif /* __USE_XOPEN || __USE_XOPEN2K */
#ifdef __REG_NOERROR
#define REG_NOERROR  REG_NOERROR  /* Success. */
#endif /* __REG_NOERROR */
#ifdef __REG_NOMATCH
#define REG_NOMATCH  REG_NOMATCH  /* Didn't find a match (for `regexec(3)'). */
#endif /* __REG_NOMATCH */
#ifdef __REG_BADPAT
#define REG_BADPAT   REG_BADPAT   /* General pattern syntax error. */
#endif /* __REG_BADPAT */
#ifdef __REG_ECOLLATE
#define REG_ECOLLATE REG_ECOLLATE /* ??? */
#endif /* __REG_ECOLLATE */
#ifdef __REG_ECTYPE
#define REG_ECTYPE   REG_ECTYPE   /* Invalid/unknown character class name. */
#endif /* __REG_ECTYPE */
#ifdef __REG_EESCAPE
#define REG_EESCAPE  REG_EESCAPE  /* Trailing '\'. */
#endif /* __REG_EESCAPE */
#ifdef __REG_ESUBREG
#define REG_ESUBREG  REG_ESUBREG  /* Back reference to group that was never initialized. */
#endif /* __REG_ESUBREG */
#ifdef __REG_EBRACK
#define REG_EBRACK   REG_EBRACK   /* Unmatched '['. */
#endif /* __REG_EBRACK */
#ifdef __REG_EPAREN
#define REG_EPAREN   REG_EPAREN   /* Unmatched '('. */
#endif /* __REG_EPAREN */
#ifdef __REG_EBRACE
#define REG_EBRACE   REG_EBRACE   /* Unmatched '{'. */
#endif /* __REG_EBRACE */
#ifdef __REG_BADBR
#define REG_BADBR    REG_BADBR    /* Invalid contents of '{...}'. */
#endif /* __REG_BADBR */
#ifdef __REG_ERANGE
#define REG_ERANGE   REG_ERANGE   /* Invalid range end (e.g. '[z-a]'). */
#endif /* __REG_ERANGE */
#ifdef __REG_ESPACE
#define REG_ESPACE   REG_ESPACE   /* Out of memory. */
#endif /* __REG_ESPACE */
#ifdef __REG_BADRPT
#define REG_BADRPT   REG_BADRPT   /* Nothing is preceding '+', '*', '?' or '{'. */
#endif /* __REG_BADRPT */
#ifdef __REG_EEND
#define REG_EEND     REG_EEND     /* Unexpected end of pattern. */
#endif /* __REG_EEND */
#ifdef __REG_ESIZE
#define REG_ESIZE    REG_ESIZE    /* Too large (pattern violates some hard limit that isn't the currently available ram) */
#endif /* __REG_ESIZE */
#ifdef __REG_ERPAREN
#define REG_ERPAREN  REG_ERPAREN  /* Unmatched ')' (only when `RE_UNMATCHED_RIGHT_PAREN_ORD' was set) */
#endif /* __REG_ERPAREN */
#ifdef __REG_EMPTY
#define REG_EMPTY    REG_EMPTY    /* ??? */
#endif /* __REG_EMPTY */
#ifdef __REG_ASSERT
#define REG_ASSERT   REG_ASSERT   /* ??? */
#endif /* __REG_ASSERT */
#ifdef __REG_INVARG
#define REG_INVARG   REG_INVARG   /* ??? */
#endif /* __REG_INVARG */
#ifdef __REG_ATOI
#define REG_ATOI     REG_ATOI     /* ??? */
#endif /* __REG_ATOI */
#ifdef __REG_ITOA
#define REG_ITOA     REG_ITOA     /* ??? */
#endif /* __REG_ITOA */
#ifdef __REG_EILLSEQ
#define REG_EILLSEQ  REG_EILLSEQ  /* Illegal unicode character (when `RE_NO_UTF8' wasn't set) */
#endif /* __REG_EILLSEQ */
#ifdef __REG_EILLSET
#define REG_EILLSET  REG_EILLSET  /* Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]") */
#endif /* __REG_EILLSET */
#else /* __COMPILER_PREFERR_ENUMS */
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifdef __REG_ENOSYS
#define REG_ENOSYS   __REG_ENOSYS   /* Returned when libc.so fails to load `libregex.so' for some reason */
#endif /* __REG_ENOSYS */
#endif /* __USE_XOPEN || __USE_XOPEN2K */
#ifdef __REG_NOERROR
#define REG_NOERROR  __REG_NOERROR  /* Success. */
#endif /* __REG_NOERROR */
#ifdef __REG_NOMATCH
#define REG_NOMATCH  __REG_NOMATCH  /* Didn't find a match (for `regexec(3)'). */
#endif /* __REG_NOMATCH */
#ifdef __REG_BADPAT
#define REG_BADPAT   __REG_BADPAT   /* General pattern syntax error. */
#endif /* __REG_BADPAT */
#ifdef __REG_ECOLLATE
#define REG_ECOLLATE __REG_ECOLLATE /* ??? */
#endif /* __REG_ECOLLATE */
#ifdef __REG_ECTYPE
#define REG_ECTYPE   __REG_ECTYPE   /* Invalid/unknown character class name. */
#endif /* __REG_ECTYPE */
#ifdef __REG_EESCAPE
#define REG_EESCAPE  __REG_EESCAPE  /* Trailing '\'. */
#endif /* __REG_EESCAPE */
#ifdef __REG_ESUBREG
#define REG_ESUBREG  __REG_ESUBREG  /* Back reference to group that was never initialized. */
#endif /* __REG_ESUBREG */
#ifdef __REG_EBRACK
#define REG_EBRACK   __REG_EBRACK   /* Unmatched '['. */
#endif /* __REG_EBRACK */
#ifdef __REG_EPAREN
#define REG_EPAREN   __REG_EPAREN   /* Unmatched '('. */
#endif /* __REG_EPAREN */
#ifdef __REG_EBRACE
#define REG_EBRACE   __REG_EBRACE   /* Unmatched '{'. */
#endif /* __REG_EBRACE */
#ifdef __REG_BADBR
#define REG_BADBR    __REG_BADBR    /* Invalid contents of '{...}'. */
#endif /* __REG_BADBR */
#ifdef __REG_ERANGE
#define REG_ERANGE   __REG_ERANGE   /* Invalid range end (e.g. '[z-a]'). */
#endif /* __REG_ERANGE */
#ifdef __REG_ESPACE
#define REG_ESPACE   __REG_ESPACE   /* Out of memory. */
#endif /* __REG_ESPACE */
#ifdef __REG_BADRPT
#define REG_BADRPT   __REG_BADRPT   /* Nothing is preceding '+', '*', '?' or '{'. */
#endif /* __REG_BADRPT */
#ifdef __REG_EEND
#define REG_EEND     __REG_EEND     /* Unexpected end of pattern. */
#endif /* __REG_EEND */
#ifdef __REG_ESIZE
#define REG_ESIZE    __REG_ESIZE    /* Too large (pattern violates some hard limit that isn't the currently available ram) */
#endif /* __REG_ESIZE */
#ifdef __REG_ERPAREN
#define REG_ERPAREN  __REG_ERPAREN  /* Unmatched ')' (only when `RE_UNMATCHED_RIGHT_PAREN_ORD' was set) */
#endif /* __REG_ERPAREN */
#ifdef __REG_EMPTY
#define REG_EMPTY    __REG_EMPTY    /* ??? */
#endif /* __REG_EMPTY */
#ifdef __REG_ASSERT
#define REG_ASSERT   __REG_ASSERT   /* ??? */
#endif /* __REG_ASSERT */
#ifdef __REG_INVARG
#define REG_INVARG   __REG_INVARG   /* ??? */
#endif /* __REG_INVARG */
#ifdef __REG_ATOI
#define REG_ATOI     __REG_ATOI     /* ??? */
#endif /* __REG_ATOI */
#ifdef __REG_ITOA
#define REG_ITOA     __REG_ITOA     /* ??? */
#endif /* __REG_ITOA */
#ifdef __REG_EILLSEQ
#define REG_EILLSEQ  __REG_EILLSEQ  /* Illegal unicode character (when `RE_NO_UTF8' wasn't set) */
#endif /* __REG_EILLSEQ */
#ifdef __REG_EILLSET
#define REG_EILLSET  __REG_EILLSET  /* Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]") */
#endif /* __REG_EILLSET */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#if defined(__USE_GNU) || defined(__USE_KOS)
#ifdef __CC__
typedef __reg_syntax_t reg_syntax_t; /* Set of `RE_*' (see below) */
#endif /* __CC__ */

/* Glibc-compatible regex syntax flags */
/* '\' can be used to escape characters in sets: '[a\[\]\-]' */
#if !defined(RE_BACKSLASH_ESCAPE_IN_LISTS) && defined(__RE_BACKSLASH_ESCAPE_IN_LISTS)
#define RE_BACKSLASH_ESCAPE_IN_LISTS __RE_BACKSLASH_ESCAPE_IN_LISTS
#endif /* !RE_BACKSLASH_ESCAPE_IN_LISTS && __RE_BACKSLASH_ESCAPE_IN_LISTS */
/* If clear: '+' and '?' are operators and '\+' and '\?' are literals; if set: the opposite is the case. */
#if !defined(RE_BK_PLUS_QM) && defined(__RE_BK_PLUS_QM)
#define RE_BK_PLUS_QM __RE_BK_PLUS_QM
#endif /* !RE_BK_PLUS_QM && __RE_BK_PLUS_QM */
/* Support for char-classes (e.g. `[[:alpha:]]') */
#if !defined(RE_CHAR_CLASSES) && defined(__RE_CHAR_CLASSES)
#define RE_CHAR_CLASSES __RE_CHAR_CLASSES
#endif /* !RE_CHAR_CLASSES && __RE_CHAR_CLASSES */
/* '^' and '$' are always anchors (as opposed to only at the start/end or after/before a '(' and ')') */
#if !defined(RE_CONTEXT_INDEP_ANCHORS) && defined(__RE_CONTEXT_INDEP_ANCHORS)
#define RE_CONTEXT_INDEP_ANCHORS __RE_CONTEXT_INDEP_ANCHORS
#endif /* !RE_CONTEXT_INDEP_ANCHORS && __RE_CONTEXT_INDEP_ANCHORS */
/* Ignored... */
#if !defined(RE_CONTEXT_INDEP_OPS) && defined(__RE_CONTEXT_INDEP_OPS)
#define RE_CONTEXT_INDEP_OPS __RE_CONTEXT_INDEP_OPS
#endif /* !RE_CONTEXT_INDEP_OPS && __RE_CONTEXT_INDEP_OPS */
/* '*', '+', '{' and '?' appearing at the start or after '(' or '|' results in `RE_BADRPT'; If not set, they are treated as literals. */
#if !defined(RE_CONTEXT_INVALID_OPS) && defined(__RE_CONTEXT_INVALID_OPS)
#define RE_CONTEXT_INVALID_OPS __RE_CONTEXT_INVALID_OPS
#endif /* !RE_CONTEXT_INVALID_OPS && __RE_CONTEXT_INVALID_OPS */
/* '.' matches line-feeds (if not set, then it doesn't) */
#if !defined(RE_DOT_NEWLINE) && defined(__RE_DOT_NEWLINE)
#define RE_DOT_NEWLINE __RE_DOT_NEWLINE
#endif /* !RE_DOT_NEWLINE && __RE_DOT_NEWLINE */
/* '.' doesn't match '\0' (if not set, then it does) */
#if !defined(RE_DOT_NOT_NULL) && defined(__RE_DOT_NOT_NULL)
#define RE_DOT_NOT_NULL __RE_DOT_NOT_NULL
#endif /* !RE_DOT_NOT_NULL && __RE_DOT_NOT_NULL */
/* '[^abc]' will not match line-feeds (as though line-feeds were part of the set of characters never matched). If not set, [^]-sets will match them (unless explicitly added to the set of unmatched characters) */
#if !defined(RE_HAT_LISTS_NOT_NEWLINE) && defined(__RE_HAT_LISTS_NOT_NEWLINE)
#define RE_HAT_LISTS_NOT_NEWLINE __RE_HAT_LISTS_NOT_NEWLINE
#endif /* !RE_HAT_LISTS_NOT_NEWLINE && __RE_HAT_LISTS_NOT_NEWLINE */
/* Enable support for intervals: 'x{1,2}' (if not set, '{' and '}' are literals, though escaping is governed by `RE_NO_BK_BRACES') */
#if !defined(RE_INTERVALS) && defined(__RE_INTERVALS)
#define RE_INTERVALS __RE_INTERVALS
#endif /* !RE_INTERVALS && __RE_INTERVALS */
/* If set, support for '+', '?' and '|' is disabled (if not set, support is enabled, though escaping is governed by `RE_BK_PLUS_QM' and `RE_NO_BK_VBAR') */
#if !defined(RE_LIMITED_OPS) && defined(__RE_LIMITED_OPS)
#define RE_LIMITED_OPS __RE_LIMITED_OPS
#endif /* !RE_LIMITED_OPS && __RE_LIMITED_OPS */
/* '\n' (embedded ASCII 10h) is treated like as an alias for the '|'-operator (if not set, '\n' is a literal; but note the kos-exception "\" "n", which matches that 2-character sequence against arbitrary line-feeds) */
#if !defined(RE_NEWLINE_ALT) && defined(__RE_NEWLINE_ALT)
#define RE_NEWLINE_ALT __RE_NEWLINE_ALT
#endif /* !RE_NEWLINE_ALT && __RE_NEWLINE_ALT */
/* If set, '{...}' are intervals, and '\{' and '\}' are literals; if clear, the opposite is the case (iow: '\{...\}' is an interval) */
#if !defined(RE_NO_BK_BRACES) && defined(__RE_NO_BK_BRACES)
#define RE_NO_BK_BRACES __RE_NO_BK_BRACES
#endif /* !RE_NO_BK_BRACES && __RE_NO_BK_BRACES */
/* If set, '(...)' are groups, and '\(' and '\)' are literals; if clear, the opposite is the case (iow: '\(...\)' is a group) */
#if !defined(RE_NO_BK_PARENS) && defined(__RE_NO_BK_PARENS)
#define RE_NO_BK_PARENS __RE_NO_BK_PARENS
#endif /* !RE_NO_BK_PARENS && __RE_NO_BK_PARENS */
/* If set, '\<1-9>' matches the literal <1-9>; if clear, '\<1-9>' is a back-reference */
#if !defined(RE_NO_BK_REFS) && defined(__RE_NO_BK_REFS)
#define RE_NO_BK_REFS __RE_NO_BK_REFS
#endif /* !RE_NO_BK_REFS && __RE_NO_BK_REFS */
/* If set, '|' is the alternation operation: '(a|b)' (and '\|' is a literal); if clear, the opposite is the case (iow: '(a\|b)' matches '[ab]') */
#if !defined(RE_NO_BK_VBAR) && defined(__RE_NO_BK_VBAR)
#define RE_NO_BK_VBAR __RE_NO_BK_VBAR
#endif /* !RE_NO_BK_VBAR && __RE_NO_BK_VBAR */
/* If set, a []-set like '[z-a]' results in `RE_ERANGE'; if clear, it is equal to '[]' (iow: bad ranges are simply ignored) */
#if !defined(RE_NO_EMPTY_RANGES) && defined(__RE_NO_EMPTY_RANGES)
#define RE_NO_EMPTY_RANGES __RE_NO_EMPTY_RANGES
#endif /* !RE_NO_EMPTY_RANGES && __RE_NO_EMPTY_RANGES */
/* If set, unmatched ')' are treated as literals; if clear, unmatched an ')' results in `RE_ERPAREN' */
#if !defined(RE_UNMATCHED_RIGHT_PAREN_ORD) && defined(__RE_UNMATCHED_RIGHT_PAREN_ORD)
#define RE_UNMATCHED_RIGHT_PAREN_ORD __RE_UNMATCHED_RIGHT_PAREN_ORD
#endif /* !RE_UNMATCHED_RIGHT_PAREN_ORD && __RE_UNMATCHED_RIGHT_PAREN_ORD */
/* If set, return the first match, rather than the perfect one (s.a. `REOP_MATCHED' and `REOP_MATCHED_PERFECT') */
#if !defined(RE_NO_POSIX_BACKTRACKING) && defined(__RE_NO_POSIX_BACKTRACKING)
#define RE_NO_POSIX_BACKTRACKING __RE_NO_POSIX_BACKTRACKING
#endif /* !RE_NO_POSIX_BACKTRACKING && __RE_NO_POSIX_BACKTRACKING */
/* If set, disable support for '\<', '\>', '\b', '\B', '\w', '\W', '\s', '\S', '\`' and "\'" */
#if !defined(RE_NO_GNU_OPS) && defined(__RE_NO_GNU_OPS)
#define RE_NO_GNU_OPS __RE_NO_GNU_OPS
#endif /* !RE_NO_GNU_OPS && __RE_NO_GNU_OPS */
/* Ignored... */
#if !defined(RE_DEBUG) && defined(__RE_DEBUG)
#define RE_DEBUG __RE_DEBUG
#endif /* !RE_DEBUG && __RE_DEBUG */
/* Invalid intervals like "a{b" are treated as literals (i.e. like "a\{b") */
#if !defined(RE_INVALID_INTERVAL_ORD) && defined(__RE_INVALID_INTERVAL_ORD)
#define RE_INVALID_INTERVAL_ORD __RE_INVALID_INTERVAL_ORD
#endif /* !RE_INVALID_INTERVAL_ORD && __RE_INVALID_INTERVAL_ORD */
/* Casing is ignored by literal-matches, and '[[:lower:]]', '[[:upper:]]', '[[:title:]]' are aliases for '[[:alpha:]]' */
#if !defined(RE_ICASE) && defined(__RE_ICASE)
#define RE_ICASE __RE_ICASE
#endif /* !RE_ICASE && __RE_ICASE */
/* Alias for `RE_CONTEXT_INDEP_ANCHORS', but only for '^', and used internally */
#if !defined(RE_CARET_ANCHORS_HERE) && defined(__RE_CARET_ANCHORS_HERE)
#define RE_CARET_ANCHORS_HERE __RE_CARET_ANCHORS_HERE
#endif /* !RE_CARET_ANCHORS_HERE && __RE_CARET_ANCHORS_HERE */
/* If set, '{' appearing at the start, or after '(', '|' or '}' results in `RE_BADRPT'; else, behavior is governed by `RE_CONTEXT_INVALID_OPS' */
#if !defined(RE_CONTEXT_INVALID_DUP) && defined(__RE_CONTEXT_INVALID_DUP)
#define RE_CONTEXT_INVALID_DUP __RE_CONTEXT_INVALID_DUP
#endif /* !RE_CONTEXT_INVALID_DUP && __RE_CONTEXT_INVALID_DUP */
/* Used to implement `RE_NOSUB' */
#if !defined(RE_NO_SUB) && defined(__RE_NO_SUB)
#define RE_NO_SUB __RE_NO_SUB
#endif /* !RE_NO_SUB && __RE_NO_SUB */
#ifdef __USE_KOS
/* '^' and '$' operators will ignore `RE_EXEC_NOTBOL' and `RE_EXEC_NOTEOL' */
#if !defined(RE_ANCHORS_IGNORE_EFLAGS) && defined(__RE_ANCHORS_IGNORE_EFLAGS)
#define RE_ANCHORS_IGNORE_EFLAGS __RE_ANCHORS_IGNORE_EFLAGS
#endif /* !RE_ANCHORS_IGNORE_EFLAGS && __RE_ANCHORS_IGNORE_EFLAGS */
/* If set, pattern is byte-based (rather than a utf-8 string; e.g. '[ä]' is like '[\xC3\xA4]'). Also disables support for '\uABCD', '\UABCDABCD' */
#if !defined(RE_NO_UTF8) && defined(__RE_NO_UTF8)
#define RE_NO_UTF8 __RE_NO_UTF8
#endif /* !RE_NO_UTF8 && __RE_NO_UTF8 */
/* If set, disable support for python- and kos-extensions: '\n', "[^:<foo>:]", '\d', '\D', '\0123', '\xAB', '\uABCD', '\UABCDABCD', '\A', '\Z' */
#if !defined(RE_NO_KOS_OPS) && defined(__RE_NO_KOS_OPS)
#define RE_NO_KOS_OPS __RE_NO_KOS_OPS
#endif /* !RE_NO_KOS_OPS && __RE_NO_KOS_OPS */
#endif /* __USE_KOS */
#endif /* __USE_GNU || __USE_KOS */

#ifdef __USE_GNU
#ifdef __CC__
typedef __LONGPTR_TYPE__ s_reg_t;       /* ??? */
typedef __ULONGPTR_TYPE__ active_reg_t; /* ??? */
#endif /* __CC__ */

/* Regex syntax sets */
#define RE_SYNTAX_EMACS                  0
#define RE_SYNTAX_AWK                    (RE_BACKSLASH_ESCAPE_IN_LISTS | RE_DOT_NOT_NULL | RE_NO_BK_PARENS | RE_NO_BK_REFS | RE_NO_BK_VBAR | RE_NO_EMPTY_RANGES | RE_DOT_NEWLINE | RE_CONTEXT_INDEP_ANCHORS | RE_CHAR_CLASSES | RE_UNMATCHED_RIGHT_PAREN_ORD | RE_NO_GNU_OPS)
#define RE_SYNTAX_GNU_AWK                ((RE_SYNTAX_POSIX_EXTENDED | RE_BACKSLASH_ESCAPE_IN_LISTS | RE_INVALID_INTERVAL_ORD) & ~(RE_DOT_NOT_NULL | RE_CONTEXT_INDEP_OPS | RE_CONTEXT_INVALID_OPS))
#define RE_SYNTAX_POSIX_AWK              (RE_SYNTAX_POSIX_EXTENDED | RE_BACKSLASH_ESCAPE_IN_LISTS | RE_INTERVALS | RE_NO_GNU_OPS | RE_INVALID_INTERVAL_ORD)
#define RE_SYNTAX_GREP                   (RE_BK_PLUS_QM | RE_CHAR_CLASSES | RE_HAT_LISTS_NOT_NEWLINE | RE_INTERVALS | RE_NEWLINE_ALT)
#define RE_SYNTAX_EGREP                  (RE_CHAR_CLASSES | RE_CONTEXT_INDEP_ANCHORS | RE_CONTEXT_INDEP_OPS | RE_HAT_LISTS_NOT_NEWLINE | RE_NEWLINE_ALT | RE_NO_BK_PARENS | RE_NO_BK_VBAR)
#define RE_SYNTAX_POSIX_EGREP            (RE_SYNTAX_EGREP | RE_INTERVALS | RE_NO_BK_BRACES | RE_INVALID_INTERVAL_ORD)
#define RE_SYNTAX_ED                     RE_SYNTAX_POSIX_BASIC
#define RE_SYNTAX_SED                    RE_SYNTAX_POSIX_BASIC
#define _RE_SYNTAX_POSIX_COMMON          (RE_CHAR_CLASSES | RE_DOT_NEWLINE | RE_DOT_NOT_NULL | RE_INTERVALS | RE_NO_EMPTY_RANGES)
#define RE_SYNTAX_POSIX_BASIC            (_RE_SYNTAX_POSIX_COMMON | RE_BK_PLUS_QM | RE_CONTEXT_INVALID_DUP)
#define RE_SYNTAX_POSIX_MINIMAL_BASIC    (_RE_SYNTAX_POSIX_COMMON | RE_LIMITED_OPS)
#define RE_SYNTAX_POSIX_EXTENDED         (_RE_SYNTAX_POSIX_COMMON | RE_CONTEXT_INDEP_ANCHORS | RE_CONTEXT_INDEP_OPS | RE_NO_BK_BRACES | RE_NO_BK_PARENS | RE_NO_BK_VBAR | RE_CONTEXT_INVALID_OPS | RE_UNMATCHED_RIGHT_PAREN_ORD)
#define RE_SYNTAX_POSIX_MINIMAL_EXTENDED (_RE_SYNTAX_POSIX_COMMON | RE_CONTEXT_INDEP_ANCHORS | RE_CONTEXT_INVALID_OPS | RE_NO_BK_BRACES | RE_NO_BK_PARENS | RE_NO_BK_REFS | RE_NO_BK_VBAR | RE_UNMATCHED_RIGHT_PAREN_ORD)

#ifndef RE_DUP_MAX
#ifndef __RE_DUP_MAX
#define __RE_DUP_MAX 255 /* _POSIX_RE_DUP_MAX */
#endif /* !__RE_DUP_MAX */
#if __RE_DUP_MAX != -1
#define RE_DUP_MAX __RE_DUP_MAX
#else /* __RE_DUP_MAX != -1 */
#define RE_DUP_MAX 255 /* _POSIX_RE_DUP_MAX */
#endif /* __RE_DUP_MAX == -1 */
#endif /* !RE_DUP_MAX */

/* Possible values for `struct re_pattern_buffer::regs_allocated' */
#if !defined(REGS_UNALLOCATED) && defined(__REGS_UNALLOCATED)
#define REGS_UNALLOCATED __REGS_UNALLOCATED /* ??? */
#endif /* !REGS_UNALLOCATED && __REGS_UNALLOCATED */
#if !defined(REGS_REALLOCATE) && defined(__REGS_REALLOCATE)
#define REGS_REALLOCATE __REGS_REALLOCATE /* ??? */
#endif /* !REGS_REALLOCATE && __REGS_REALLOCATE */
#if !defined(REGS_FIXED) && defined(__REGS_FIXED)
#define REGS_FIXED __REGS_FIXED /* ??? */
#endif /* !REGS_FIXED && __REGS_FIXED */

#ifndef RE_TRANSLATE_TYPE
#define RE_TRANSLATE_TYPE __RE_TRANSLATE_TYPE /* ??? */
#endif /* !RE_TRANSLATE_TYPE */
#if !defined(RE_NREGS) && defined(__RE_NREGS)
#define RE_NREGS __RE_NREGS /* ??? */
#endif /* !RE_NREGS && __RE_NREGS */
#endif /* __USE_GNU */

/* Flags for `regcomp(3)'s `cflags' argument. */
#ifndef REG_BASIC
#define REG_BASIC 0 /* Use `RE_POSIX_BASIC' */
#endif /* !REG_BASIC */
#if !defined(REG_EXTENDED) && defined(__REG_EXTENDED)
#define REG_EXTENDED __REG_EXTENDED /* Use `RE_POSIX_MINIMAL_BASIC' instead of `RE_POSIX_BASIC' */
#endif /* !REG_EXTENDED && __REG_EXTENDED */
#if !defined(REG_ICASE) && defined(__REG_ICASE)
#define REG_ICASE    __REG_ICASE    /* Ignore casing during matching (s.a. `RE_ICASE') */
#endif /* !REG_ICASE && __REG_ICASE */
#if !defined(REG_NEWLINE) && defined(__REG_NEWLINE)
#define REG_NEWLINE  __REG_NEWLINE  /* Clears `RE_DOT_NEWLINE'; sets `RE_HAT_LISTS_NOT_NEWLINE | RE_ANCHORS_IGNORE_EFLAGS' */
#endif /* !REG_NEWLINE && __REG_NEWLINE */
#if !defined(REG_NOSUB) && defined(__REG_NOSUB)
#define REG_NOSUB    __REG_NOSUB    /* `regexec(3)' will ignore the `nmatch' and `pmatch' arguments (s.a. `RE_NO_SUB'). */
#endif /* !REG_NOSUB && __REG_NOSUB */
#if !defined(REG_NOSPEC) && defined(__REG_NOSPEC)
#define REG_NOSPEC   __REG_NOSPEC   /* ??? */
#endif /* !REG_NOSPEC && __REG_NOSPEC */
#if !defined(REG_PEND) && defined(__REG_PEND)
#define REG_PEND     __REG_PEND     /* ??? */
#endif /* !REG_PEND && __REG_PEND */
#if !defined(REG_DUMP) && defined(__REG_DUMP)
#define REG_DUMP     __REG_DUMP     /* ??? */
#endif /* !REG_DUMP && __REG_DUMP */
#if !defined(REG_GNU) && defined(__REG_GNU)
#define REG_GNU      __REG_GNU      /* ??? */
#endif /* !REG_GNU && __REG_GNU */


/* Flags for `regexec(3)'s `eflags' argument. */
#if !defined(REG_NOTBOL) && defined(__REG_NOTBOL)
#define REG_NOTBOL   __REG_NOTBOL   /* '^' doesn't match the start of input data (but only at an actual begin-of-line) */
#endif /* !REG_NOTBOL && __REG_NOTBOL */
#if !defined(REG_NOTEOL) && defined(__REG_NOTEOL)
#define REG_NOTEOL   __REG_NOTEOL   /* '$' doesn't match the end of input data (but only before an actual line-feed) */
#endif /* !REG_NOTEOL && __REG_NOTEOL */
#if !defined(REG_STARTEND) && defined(__REG_STARTEND)
#define REG_STARTEND __REG_STARTEND /* Use `pmatch[0]' on input to determine the search start/end-offsets
                                     * in the input buffer (allowing '\0' to be included in input  data). */
#endif /* !REG_STARTEND && __REG_STARTEND */

/* Some hint flags from NetBSD (which we 0 out if not available) */
#ifndef REG_TRACE
#ifdef __REG_TRACE
#define REG_TRACE __REG_TRACE
#else /* __REG_TRACE */
#define REG_TRACE 0
#endif /* !__REG_TRACE */
#endif /* !REG_TRACE */
#ifndef REG_LARGE
#ifdef __REG_LARGE
#define REG_LARGE __REG_LARGE
#else /* __REG_LARGE */
#define REG_LARGE 0
#endif /* !__REG_LARGE */
#endif /* !REG_LARGE */
#ifndef REG_BACKR
#ifdef __REG_BACKR
#define REG_BACKR __REG_BACKR
#else /* __REG_BACKR */
#define REG_BACKR 0
#endif /* !__REG_BACKR */
#endif /* !REG_BACKR */


#ifdef __CC__
typedef struct re_pattern_buffer regex_t;
typedef __regoff_t regoff_t;
typedef struct __regmatch regmatch_t;

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

}

%#ifdef __USE_GNU

%{

/* Regex syntax used by `re_compile_pattern(3)'.
 * By default, this is set to `RE_SYNTAX_EMACS'. */
#ifndef re_syntax_options
#ifdef __LOCAL_re_syntax_options
#define re_syntax_options __LOCAL_re_syntax_options
#elif defined(__CRT_HAVE_re_syntax_options)
__CSDECLARE(,reg_syntax_t,re_syntax_options)
#define re_syntax_options re_syntax_options
#endif /* ... */
#endif /* !re_syntax_options */

}

@@>> re_set_syntax(3)
@@Set  the  regex  syntax used  by  `re_compile_pattern(3)', and
@@return the old default syntax (same as `re_syntax_options(3)')
[[decl_include("<bits/crt/regex.h>")]]
[[requires_include("<libc/template/re_syntax_options.h>")]]
[[requires(defined(__LOCAL_re_syntax_options))]]
[[impl_include("<libc/template/re_syntax_options.h>")]]
reg_syntax_t re_set_syntax(reg_syntax_t syntax) {
	reg_syntax_t result = re_syntax_options;
	re_syntax_options   = syntax;
	return result;
}


@@>> re_compile_pattern(3)
@@Compile a regular expression pattern (s.a. re_compiler_compile(3R)')
@@@param: pattern: Regex pattern string
@@@param: length:  Length of regex pattern string (in bytes)
@@@param: self:    The `regex_t' object to initialize.
@@@return: NULL:   Success
@@@return: * :     An error message, as would be produced by `regerror(3)'
[[decl_include("<hybrid/typecore.h>", "<bits/crt/regex.h>")]]
char const *re_compile_pattern([[in(length)]] char const *pattern, size_t length,
                               [[out]] regex_t *self);

@@>> re_compile_fastmap(3)
@@Compile the fast-map of `self'. No-op on KOS, where the fastmap is always compiled immediatly.
@@@return: 0 : Always returns `0'
[[decl_include("<bits/crt/regex.h>")]]
int re_compile_fastmap([[inout]] regex_t *self) {
	(void)self;
	COMPILER_IMPURE();
	return 0;
}

%[define_c_language_keyword(__KOS_FIXED_CONST)]

@@>> re_search(3)
@@Perform a regex search for the first matching byte-offset in `[start,start+range)'.
@@The  accessed area of  the input buffer  is restricted to `[string,string+length)'.
@@@param: self:   The compiled regex pattern to use. NOTE: regex `eflags' are set as:
@@                 - `REG_NOTBOL = self->__not_bol'
@@                 - `REG_NOTEOL = self->__not_eol'
@@                Sadly, this make this interface really badly designed, as this choice
@@                (which was made by Glibc  btw), prevents multiple threads from  using
@@                the same `regex_t' buffer simultaneously. Though note that this  same
@@                restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
@@                if  you completely by-pass  the `<regex.h>' API  and directly talk to
@@                the public API of `libregex.so' from `<libregex/regexec.h>'.
@@@param: string: Base pointer for input data.
@@@param: length: Length of input data (in bytes)
@@@param: start:  Starting offset where to begin searching
@@@param: range:  The max # of searches to attempt at successive byte-offsets starting at `start'
@@@param: regs:   Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
@@@return: >= 0:  Was able to discover a match at this offset. (always `< range')
@@@return: -1:    No match was found
@@@return: -2:    Internal error (probably meaning out-of-memory)
[[userimpl, requires_function(re_search_2)]]
[[decl_include("<features.h>", "<bits/crt/regex.h>")]]
__STDC_INT_AS_SSIZE_T re_search([[in]] regex_t __KOS_FIXED_CONST *self,
                                [[in(length)]] char const *string, __STDC_INT_AS_SIZE_T length,
                                __STDC_INT_AS_SIZE_T start, __STDC_INT_AS_SIZE_T range,
                                [[out_opt]] struct __re_registers *regs) {
	return re_search_2(self, string, length, NULL, 0, start, range, regs, length);
}

@@>> re_search_2(3)
@@Same as `re_search(3)',  but use the  virtual concatenation of  `string1...+=length1'
@@and  `string2...+=length2' as input  buffer. Also: use `stop'  as the end-offset into
@@this  virtual buffer of where to stop  doing non-extra accessing accesses (extra data
@@accesses are positional assertion checks at the end of the regex pattern, such as '$'
@@checking  if it is followed by a line-feed being allowed to read until the actual end
@@of the virtual buffer,  whilst actual byte-matching is  only allowed to happen  until
@@an offset of `stop' bytes has been reached)
@@
@@Note that on KOS, the underlying API used is `re_exec_search(3R)' from `libregex.so'
@@and exposed in `<libregex/regexec.h>', which allows for the virtual concatenation of
@@not just 2, but an arbitrary number of buffers which are then used as input.
@@
@@@param: self:    The compiled regex pattern to use. NOTE: regex `eflags' are set as:
@@                  - `REG_NOTBOL = self->__not_bol'
@@                  - `REG_NOTEOL = self->__not_eol'
@@                 Sadly, this make this interface really badly designed, as this choice
@@                 (which was made by Glibc  btw), prevents multiple threads from  using
@@                 the same `regex_t' buffer simultaneously. Though note that this  same
@@                 restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
@@                 if  you completely by-pass  the `<regex.h>' API  and directly talk to
@@                 the public API of `libregex.so' from `<libregex/regexec.h>'.
@@@param: string1: First base pointer for input data.
@@@param: length1: Length of first input data (in bytes)
@@@param: string2: Second base pointer for input data.
@@@param: length2: Length of second input data (in bytes)
@@@param: start:   Starting offset where to begin searching
@@@param: range:   The max # of searches to attempt at successive byte-offsets starting at `start'
@@@param: regs:    Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
@@@param: stop:    Offset into the virtual input buffer that marks its end (must be `<= length1+length2')
@@@return: >= 0:   Was able to discover a match at this offset. (always `< range')
@@@return: -1:     No match was found
@@@return: -2:     Internal error (probably meaning out-of-memory)
[[decl_include("<features.h>", "<bits/crt/regex.h>")]]
__STDC_INT_AS_SSIZE_T re_search_2([[in]] regex_t __KOS_FIXED_CONST *self,
                                  [[in(length1)]] char const *string1, __STDC_INT_AS_SIZE_T length1,
                                  [[in(length2)]] char const *string2, __STDC_INT_AS_SIZE_T length2,
                                  __STDC_INT_AS_SIZE_T start, __STDC_INT_AS_SIZE_T range,
                                  [[out_opt]] struct __re_registers *regs, __STDC_INT_AS_SIZE_T stop);

@@>> re_match(3)
@@Match input data `[string+start,string+length)' against the regex pattern `self'
@@The accessed area of the input buffer is restricted to `[string,string+length)'.
@@@param: self:   The compiled regex pattern to use. NOTE: regex `eflags' are set as:
@@                 - `REG_NOTBOL = self->__not_bol'
@@                 - `REG_NOTEOL = self->__not_eol'
@@                Sadly, this make this interface really badly designed, as this choice
@@                (which was made by Glibc  btw), prevents multiple threads from  using
@@                the same `regex_t' buffer simultaneously. Though note that this  same
@@                restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
@@                if  you completely by-pass  the `<regex.h>' API  and directly talk to
@@                the public API of `libregex.so' from `<libregex/regexec.h>'.
@@@param: string: Base pointer for input data.
@@@param: length: Length of input data (in bytes)
@@@param: start:  Starting offset where to begin searching
@@@param: regs:   Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
@@@return: >= 0:  The number of bytes starting at `start' that were matched against `self'
@@@return: -1:    No match was found
@@@return: -2:    Internal error (probably meaning out-of-memory)
[[userimpl, requires_function(re_match_2)]]
[[decl_include("<features.h>", "<bits/crt/regex.h>")]]
__STDC_INT_AS_SSIZE_T re_match([[in]] regex_t __KOS_FIXED_CONST *self,
                               [[in(length)]] char const *string, __STDC_INT_AS_SIZE_T length,
                               __STDC_INT_AS_SIZE_T start, [[out_opt]] struct __re_registers *regs) {
	return re_match_2(self, string, length, NULL, 0, start, regs, length);
}

@@>> re_match_2(3)
@@Same  as `re_match(3)',  but use  the virtual  concatenation of `string1...+=length1'
@@and  `string2...+=length2' as input  buffer. Also: use `stop'  as the end-offset into
@@this  virtual buffer of where to stop  doing non-extra accessing accesses (extra data
@@accesses are positional assertion checks at the end of the regex pattern, such as '$'
@@checking  if it is followed by a line-feed being allowed to read until the actual end
@@of the virtual buffer,  whilst actual byte-matching is  only allowed to happen  until
@@an offset of `stop' bytes has been reached)
@@
@@Note that on KOS, the underlying API used is `re_exec_match(3R)' from  `libregex.so'
@@and exposed in `<libregex/regexec.h>', which allows for the virtual concatenation of
@@not just 2, but an arbitrary number of buffers which are then used as input.
@@
@@@param: self:    The compiled regex pattern to use. NOTE: regex `eflags' are set as:
@@                  - `REG_NOTBOL = self->__not_bol'
@@                  - `REG_NOTEOL = self->__not_eol'
@@                 Sadly, this make this interface really badly designed, as this choice
@@                 (which was made by Glibc  btw), prevents multiple threads from  using
@@                 the same `regex_t' buffer simultaneously. Though note that this  same
@@                 restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
@@                 if  you completely by-pass  the `<regex.h>' API  and directly talk to
@@                 the public API of `libregex.so' from `<libregex/regexec.h>'.
@@@param: string1: First base pointer for input data.
@@@param: length1: Length of first input data (in bytes)
@@@param: string2: Second base pointer for input data.
@@@param: length2: Length of second input data (in bytes)
@@@param: start:   Starting offset where to begin searching
@@@param: range:   The max # of searches to attempt at successive byte-offsets starting at `start'
@@@param: regs:    Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
@@@param: stop:    Offset into the virtual input buffer that marks its end (must be `<= length1+length2')
@@@return: >= 0:   The number of bytes starting at `start' that were matched against `self'
@@@return: -1:     No match was found
@@@return: -2:     Internal error (probably meaning out-of-memory)
[[decl_include("<features.h>", "<bits/crt/regex.h>")]]
__STDC_INT_AS_SSIZE_T re_match_2([[in]] regex_t __KOS_FIXED_CONST *self,
                                 [[in(length1)]] char const *string1, __STDC_INT_AS_SIZE_T length1,
                                 [[in(length2)]] char const *string2, __STDC_INT_AS_SIZE_T length2,
                                 __STDC_INT_AS_SIZE_T start, [[out_opt]] struct __re_registers *regs,
                                 __STDC_INT_AS_SIZE_T stop);

@@>> re_set_registers(3)
@@Initializes `regs', and sets some weird internal flag in `self' (which it doesn't do on KOS)
[[decl_include("<bits/crt/regex.h>")]]
void re_set_registers([[inout]] regex_t *self, [[out]] struct __re_registers *regs,
                      unsigned int num_regs, regoff_t *starts, regoff_t *ends) {
	(void)self;
	regs->@num_regs@ = num_regs;
	if (num_regs) {
		regs->@start@ = starts;
		regs->@end@   = ends;
	} else {
		regs->@start@ = NULL;
		regs->@end@   = NULL;
	}
}

%#endif /* __USE_GNU */

%{

/************************************************************************/
/* STANDARD POSIX REGEX FUNCTIONS                                       */
/************************************************************************/

}


@@>> regcomp(3)
@@Compile a regular expression `pattern' and initialize `self'
@@@param: self:    Storage for the produced regex pattern.
@@@param: pattern: The pattern to compile.
@@@param: cflags:  Set of `REG_EXTENDED | REG_ICASE | REG_NEWLINE | REG_NOSUB'
@@@return: REG_NOERROR: Success
@@@return: REG_BADPAT:  General pattern syntax error.
@@@return: REG_ECTYPE:  Invalid/unknown character class name.
@@@return: REG_EESCAPE: Trailing backslash.
@@@return: REG_ESUBREG: Invalid back reference.
@@@return: REG_EBRACK:  Unmatched '['.
@@@return: REG_EPAREN:  Unmatched '('.
@@@return: REG_EBRACE:  Unmatched '{'.
@@@return: REG_BADBR:   Invalid contents of '{...}'.
@@@return: REG_ERANGE:  Invalid range end (e.g. '[z-a]').
@@@return: REG_ESPACE:  Out of memory.
@@@return: REG_BADRPT:  Nothing is preceding '+', '*', '?' or '{'.
@@@return: REG_EEND:    Unexpected end of pattern.
@@@return: REG_ESIZE:   Compiled pattern bigger than 2^16 bytes.
@@@return: REG_ERPAREN: Unmatched ')' (only when `RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD' was set)
@@@return: REG_EILLSEQ: Illegal unicode character (when `RE_NO_UTF8' wasn't set)
@@@return: REG_EILLSET: Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]")
@@@return: REG_ENOSYS:  Unable to load `libregex.so' (shouldn't happen)
[[decl_include("<bits/crt/regex.h>")]]
int regcomp([[out]] regex_t *__restrict self, [[in]] char const *__restrict pattern, int cflags);

@@>> regexec(3)
@@Execute a compiled regular expression `pattern' on the priveded string.
@@- This function searches for the FIRST position in `string' at which `self' can be matched.
@@- When `nmatch > 0' (and `REG_NOSUB' wasn't set), the matched address-range is stored in `pmatch[0]'
@@- When `nmatch > 1' (and `REG_NOSUB' wasn't set), the start/end-offsets of "(...)"-groups are stored
@@  here for up to the  first `nmatch - 1' groups. Non-existant groups  are assigned `-1' in  offsets.
@@- When nothing was matched, and `nmatch > 0' (and `REG_NOSUB' wasn't set), the offsets of all elements
@@  of `pmatch' are set to `-1' (thus indicating a lack of any sort of match).
@@@param: self:   The compiled regex pattern.
@@@param: string: Input data that should be matched (must be a NUL-terminated string, unless `REG_STARTEND' is given)
@@@param: nmatch: one plus max # of group start/end-offsets to write to `*pmatch' (ignored if `REG_NOSUB' was set)
@@                When non-zero, `pmatch[0]' will receive the start/end offsets where `self' matched in  `string'.
@@@param: pmatch: Storage for at least `nmatch' group start/end-offsets (ignored if `REG_NOSUB' was set)
@@@param: eflags: Set of `REG_NOTBOL | REG_NOTEOL | REG_STARTEND'
@@@return: 0:           Success
@@@return: REG_NOMATCH: Nothing was matched, or some internal error happened
[[decl_include("<hybrid/typecore.h>", "<bits/crt/regex.h>")]]
int regexec([[in]] regex_t const *__restrict self, [[in]] char const *__restrict string,
            size_t nmatch, regmatch_t pmatch[__restrict_arr], int eflags);


@@>> regerror(3)
@@Produce a human-readable description for a regex error code `errcode' (s.a. `regerrordesc_np(3)')
@@@param: errcode: Regex error code (one of `REG_*'; s.a. `reg_errcode_t')
@@@param: self:    The compiled regex pattern that produced the error (unused in this impl)
@@@return: * :     The required buffer size (including a trailing '\0'-byte)
[[requires_function(regerrordesc_np)]]
[[decl_include("<hybrid/typecore.h>", "<bits/crt/regex.h>")]]
size_t regerror(int errcode, [[in]] regex_t const *__restrict self,
                [[out(? <= errbuf_size)]] char *__restrict errbuf,
                size_t errbuf_size) {
	char const *msg;
	size_t msglen;
	(void)self;
	msg = regerrordesc_np(errcode);
	if unlikely(!msg)
		msg = "?";
	msglen = strlen(msg);
	if (errbuf_size > (msglen + 1))
		errbuf_size = (msglen + 1);
	memcpy(errbuf, msg, errbuf_size);
	return msglen;
}

@@>> regfree(3)
@@Free dynamic memory allocated during a successful call to `regcomp(3)'
@@@param: self: The compiled regex pattern to destroy
[[requires($has_function(free) && defined(__CRT_KOS))]]
[[decl_include("<bits/crt/regex.h>")]]
void regfree(regex_t *self) {
	free(self->@__REPB_PREFIX(buffer)@);
}


%
%#ifdef __USE_KOS
@@>> regerrordesc_np(3)
@@Return a human-readable description for a given regex `errcode'
@@@param: errcode: Regex error code (one of `REG_*'; s.a. `reg_errcode_t')
@@@return: * :   The human-readable description for `errcode'
@@@return: NULL: No description is available for `errcode'
[[const, wunused, impl_include("<asm/crt/regex.h>")]]
char const *regerrordesc_np(int errcode) {
	char const *result;
	switch (errcode) {
@@pp_ifdef __REG_ENOSYS@@
	case __REG_ENOSYS: /*  */ result = "Unable to load regex sub-system"; break;
@@pp_endif@@
@@pp_ifdef __REG_NOERROR@@
	case __REG_NOERROR: /* */ result = "Success"; break;
@@pp_endif@@
@@pp_ifdef __REG_NOMATCH@@
	case __REG_NOMATCH: /* */ result = "No match"; break;
@@pp_endif@@
@@pp_ifdef __REG_BADPAT@@
	case __REG_BADPAT: /*  */ result = "Invalid regex pattern"; break;
@@pp_endif@@
@@pp_ifdef __REG_ECOLLATE@@
	case __REG_ECOLLATE: /**/ result = "Invalid collation character"; break;
@@pp_endif@@
@@pp_ifdef __REG_ECTYPE@@
	case __REG_ECTYPE: /*  */ result = "Invalid character class name"; break;
@@pp_endif@@
@@pp_ifdef __REG_EESCAPE@@
	case __REG_EESCAPE: /* */ result = "Trailing backslash"; break;
@@pp_endif@@
@@pp_ifdef __REG_ESUBREG@@
	case __REG_ESUBREG: /* */ result = "Invalid back reference"; break;
@@pp_endif@@
@@pp_ifdef __REG_EBRACK@@
	case __REG_EBRACK: /*  */ result = "Unmatched [, [^, [:, [., or [="; break;
@@pp_endif@@
@@pp_ifdef __REG_EPAREN@@
	case __REG_EPAREN: /*  */ result = "Unmatched ("; break;
@@pp_endif@@
@@pp_ifdef __REG_EBRACE@@
	case __REG_EBRACE: /*  */ result = "Unmatched {"; break;
@@pp_endif@@
@@pp_ifdef __REG_BADBR@@
	case __REG_BADBR: /*   */ result = "Invalid content of {...}"; break;
@@pp_endif@@
@@pp_ifdef __REG_ERANGE@@
	case __REG_ERANGE: /*  */ result = "Set-range start is greater than its end"; break;
@@pp_endif@@
@@pp_ifdef __REG_ESPACE@@
	case __REG_ESPACE: /*  */ result = "Out of memory"; break;
@@pp_endif@@
@@pp_ifdef __REG_BADRPT@@
	case __REG_BADRPT: /*  */ result = "Nothing precedes +, *, ?, or {"; break;
@@pp_endif@@
@@pp_ifdef __REG_EEND@@
	case __REG_EEND: /*    */ result = "Unexpected end of pattern"; break;
@@pp_endif@@
@@pp_ifdef __REG_ESIZE@@
	case __REG_ESIZE: /*   */ result = "Regular expression violates a hard upper limit"; break;
@@pp_endif@@
@@pp_ifdef __REG_ERPAREN@@
	case __REG_ERPAREN: /* */ result = "Unmatched )"; break;
@@pp_endif@@
@@pp_ifdef __REG_EILLSEQ@@
	case __REG_EILLSEQ: /* */ result = "Illegal unicode character"; break;
@@pp_endif@@
@@pp_ifdef __REG_EILLSET@@
	case __REG_EILLSET: /* */ result = "Cannot combine raw bytes with unicode characters in charsets"; break;
@@pp_endif@@
@@pp_ifdef __REG_EMPTY@@
	case __REG_EMPTY: /*   */ result = "?"; break;
@@pp_endif@@
@@pp_ifdef __REG_ASSERT@@
	case __REG_ASSERT: /*  */ result = "?"; break;
@@pp_endif@@
@@pp_ifdef __REG_INVARG@@
	case __REG_INVARG: /*  */ result = "?"; break;
@@pp_endif@@
	default: result = NULL; break;
	}
	return result;
}
%#endif /* __USE_KOS */


%
%#ifdef _REGEX_RE_COMP

@@>> re_comp(3)
@@Compare the given `pattern' and assign it to an internal regex buffer which can
@@then later be used in conjunction with `re_exec(3)'. The Syntax options used by
@@this function are  `re_syntax_options | RE_ANCHORS_IGNORE_EFLAGS'. By  default,
@@the global `re_syntax_options' is set to `RE_SYNTAX_EMACS'.
@@WARNING: This function is not thread-safe!
@@@param: pattern: The pattern to compile (or `NULL' to verify that a pattern has already been compiled)
@@@return: NULL:   Success
@@@return: * :     Error (returned pointer is the human-readable error message, as returned by `regerrordesc_np(3)')
@@                 In this case, the internal, static regex buffer is left unaltered.
[[section(".text.crt.compat.glibc.regex")]]
char __KOS_FIXED_CONST *re_comp([[nullable]] char const *pattern);

@@>> re_exec(3)
@@Try to match the regex previous compiled by `re_comp(3)'
@@against some sub-string of `string'. This is equivalent to:
@@>> re_search(&REGEX_COMPILED_BY_RE_COMP, // self
@@>>           string,                     // string
@@>>           strlen(string),             // length
@@>>           0,                          // start
@@>>           strlen(string),             // range
@@>>           NULL) >= 0                  // regs
@@Note that to  force matching to  only happen at  the start of  `string',
@@the pattern passed to `re_comp(3)' should begin with "^" (thus requiring
@@that the pattern only matches at the start, or after a line-feed).
@@
@@If `re_comp(3)' has never been called, always returns `0'
@@@param: string: The pattern to compile (or `NULL' to verify that a pattern has already been compiled)
@@@return: 1:     The given `string' contains (at least) one matching sub-string
@@@return: 0:     The given `string' does not contain a sub-string that matches the previously compiled pattern.
[[pure, wunused, section(".text.crt.compat.glibc.regex")]]
int re_exec([[nonnull]] char const *string);

%#endif /* _REGEX_RE_COMP */

%
%#ifdef __USE_KOS
@@>> regsubprint(3), regsubprintv(3)
@@Perform sed-like substitution of from `sed_format' using matches previously obtained from `regexec(3)'.
@@This  function  writes  the  NUL-terminated   string  `sed_format'  to  `printer',  whilst   replacing:
@@ - '&'  with the contents of `pmatch[0]' (or an empty string when `nmatch == 0')
@@ - '\N' with the contents of `pmatch[N]' (or an empty string when `nmatch <= N'; N must be in `[0,9]')
@@ - '\&' Prints a literal '&'
@@ - '\\' Prints a literal '\'
@@NOTE: Matches that are unset (i.e. use start/end offset `-1') produce empty strings
@@@param: printer:    Output printer
@@@param: arg:        Cookie argument for `printer'
@@@param: sed_format: Sed format string
@@@param: srcbase:    IOV base (offsets from `pmatch' point into this)
@@@param: nmatch:     The # of matches defined by `pmatch'
@@@param: pmatch:     Vector of matches
@@@return: >= 0:      Sum of positive return values of `printer'
@@@return: -1:        First negative return value of `printer'
[[decl_include("<bits/crt/format-printer.h>", "<bits/crt/regex.h>")]]
[[decl_include("<bits/os/iovec.h>", "<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
ssize_t regsubprintv([[nonnull]] __pformatprinter printer, void *arg,
                     [[in]] char const *sed_format,
                     [[nonnull]] struct iovec const *srcbase, size_t nmatch,
                     [[in(nmatch)]] regmatch_t const pmatch[__restrict_arr]) {
	size_t imatch;
	ssize_t temp, result = 0;
	char ch;
	char const *flush_start;
	flush_start = sed_format;
again:
	ch = *sed_format++;
	switch (ch) {

	case '\0':
		--sed_format;
		break;

	case '&':
		imatch = 0;
insert_imatch:
		/* Flush until the start of the insert-sequence */
		--sed_format;
		if (sed_format > flush_start) {
			temp = (*printer)(arg, flush_start, (size_t)(sed_format - flush_start));
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (*sed_format == '\\')
			++sed_format;
		++sed_format;
		flush_start = sed_format;

		/* Insert the `imatch'th element from `pmatch' */
		if (imatch < nmatch && (pmatch[imatch].@rm_so@ != (regoff_t)-1 &&
		                        pmatch[imatch].@rm_eo@ != (regoff_t)-1)) {
			size_t offset, count;
			offset = (size_t)pmatch[imatch].@rm_so@;
			count  = (size_t)(pmatch[imatch].@rm_eo@ - pmatch[imatch].@rm_so@);
			if (count > 0) {
				/* Seek until the first source iov item. */
				struct iovec const *iov = srcbase;
				while (offset >= iov->@iov_len@) {
					offset -= iov->@iov_len@;
					++iov;
				}
				/* Print the next `count' bytes starting at `iov[+offset]' */
				for (;;) {
					size_t partlen;
					partlen = iov->@iov_len@ - offset;
					if (partlen > count)
						partlen = count;
					temp = (*printer)(arg, (char const *)((byte_t const *)iov->@iov_base@ + offset), partlen);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					if (partlen >= count)
						break;
					count -= partlen;
					offset = 0;
					++iov;
				}
			}
		}
		goto again;

	case '\\':
		ch = *sed_format;
		if (ch >= '0' && ch <= '9') {
			imatch = (size_t)(ch - '0');
			goto insert_imatch;
		} else if (ch == '&' || ch == '\\') {
			/* Escaped character */
			--sed_format;
			if (sed_format > flush_start) {
				temp = (*printer)(arg, flush_start, (size_t)(sed_format - flush_start));
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			++sed_format;
			flush_start = sed_format; /* Flush the escaped char the next time around */
			++sed_format;
		}
		goto again;

	default:
		goto again;
	}

	/* Flush any left-over remainder. */
	if (sed_format > flush_start) {
		temp = (*printer)(arg, flush_start, (size_t)(sed_format - flush_start));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}

[[doc_alias("regsubprintv"), requires_function(regsubprintv)]]
[[decl_include("<bits/crt/format-printer.h>", "<bits/crt/regex.h>", "<hybrid/typecore.h>")]]
[[impl_include("<bits/os/iovec.h>", "<hybrid/typecore.h>")]]
ssize_t regsubprint([[nonnull]] __pformatprinter printer, void *arg,
                    [[in]] char const *sed_format,
                    [[nonnull]] void const *srcbase, size_t nmatch,
                    [[in(nmatch)]] regmatch_t const pmatch[__restrict_arr]) {
	struct iovec iov[1];
	iov[0].@iov_base@ = (void *)srcbase;
	iov[0].@iov_len@  = (size_t)-1;
	return regsubprintv(printer, arg, sed_format, iov, nmatch, pmatch);
}

%#endif /* __USE_KOS */


%[define(DEFINE_FORMAT_APRINTF_DATA =
@@pp_ifndef __format_aprintf_data_defined@@
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *@ap_base@;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ @ap_avail@; /* Unused buffer size */
	__SIZE_TYPE__ @ap_used@;  /* Used buffer size */
};
@@pp_endif@@
)]


%
%#ifdef __USE_NETBSD
@@>> regnsub(3)
@@Wrapper for `regsubprint(3)' that writes the produced string into `buf...+=len'
@@@param: buf:        Output buffer base pointer
@@@param: len:        Length of `buf'
@@@param: sed_format: Sed format string
@@@param: pmatch:     A 10-element-long list of matches
@@@param: srcbase:    Source base pointer
@@@return: * :        Required buffer length (excluding a trailing NUL-character).
@@                    NOTE: On NetBSD, the return value is signed, but that didn't make
@@                          sense  since there is no error-case, so I made it unsigned.
[[decl_include("<bits/crt/regex.h>", "<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(regsubprint, format_snprintf_printer)]]
size_t regnsub([[out(? <= len)]] char *buf, size_t len,
               [[in]] char const *sed_format,
               [[nonnull/*in(10)*/]] regmatch_t const *pmatch,
               [[in]] char const *srcbase) {
	size_t result;
	struct __local_format_snprintf_data {
		char  *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		size_t sd_bufsiz; /* Remaining buffer size. */
	} pdata;
	pdata.sd_buffer = buf;
	pdata.sd_bufsiz = len;

	/* Do the substitution-print. */
	result = (size_t)regsubprint(&format_snprintf_printer, &pdata,
	                             sed_format, srcbase, 10, pmatch);

	/* Append trailing NUL-terminator (if there is still space for it). */
	if (pdata.sd_bufsiz)
		*pdata.sd_buffer = '\0';

	/* Return required buffer size (excluding the trailing NUL) */
	return result;
}


@@>> regasub(3)
@@Wrapper for `regsubprint(3)' that dynamically allocates a buffer and stores it in `*p_buf'
@@@param: p_buf:      Pointer to output buffer of sed-replaced text (terminated by '\0')
@@                    On error, `NULL' will be stored in this pointer.
@@@param: sed_format: Sed format string
@@@param: pmatch:     A 10-element-long list of matches
@@@param: srcbase:    Source base pointer
@@@return: * :        Length of the string stored in `*p_buf' (excluding the trailing '\0')
@@@return: -1:        [errno=ENOMEM] Out of memory
[[decl_include("<bits/crt/regex.h>", "<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE_FORMAT_APRINTF_DATA)]]
[[requires_function(format_aprintf_pack, format_aprintf_printer, regsubprint)]]
ssize_t regasub([[out]] char **p_buf, [[in]] char const *sed_format,
                [[nonnull/*in(10)*/]] regmatch_t const *pmatch,
                [[in]] char const *srcbase) {
	struct format_aprintf_data pdata;
	ssize_t result;
	char *resstr;

	/* Setup malloc-based printer. */
	pdata.@ap_base@  = NULL;
	pdata.@ap_avail@ = 0;
	pdata.@ap_used@  = 0;

	/* Do the substitution-print. */
	result = regsubprint(&format_aprintf_printer, &pdata,
	                     sed_format, srcbase, 10, pmatch);
	if unlikely(result < 0)
		goto err;

	/* package the produced string. */
	resstr = format_aprintf_pack(&pdata, (size_t *)&result);
	*p_buf = resstr;
	if unlikely(!resstr)
		result = -1;
	return result;
err:
@@pp_if $has_function(free)@@
	free(pdata.@ap_base@);
@@pp_endif@@
	*p_buf = NULL;
	return -1;
}

%#endif /* __USE_NETBSD */


%{

#endif /* __CC__ */

__SYSDECL_END

}
