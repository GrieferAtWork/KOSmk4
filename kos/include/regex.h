/* HASH CRC-32:0x5120fb9d */
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
#ifndef _REGEX_H
#define _REGEX_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>

#include <asm/crt/limits.h> /* __RE_DUP_MAX */
#include <asm/crt/regex.h>
#include <bits/crt/regex.h>
#include <sys/types.h>

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
#ifdef __REG_EILLSET
#define REG_EILLSET  __REG_EILLSET  /* Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]") */
#endif /* __REG_EILLSET */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#if defined(__USE_GNU) || defined(__USE_KOS)
#ifdef __CC__
typedef __reg_syntax_t reg_syntax_t; /* Set of `RE_*' (see below) */
#endif /* __CC__ */

/* GLibc-compatible regex syntax flags */
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

#ifdef __CC__
typedef struct re_pattern_buffer regex_t;
typedef __regoff_t regoff_t;
typedef struct __regmatch regmatch_t;

#ifdef __USE_GNU

/* Regex syntax used by `re_compile_pattern(3)'. */
#ifndef re_syntax_options
#ifdef __LOCAL_re_syntax_options
#define re_syntax_options __LOCAL_re_syntax_options
#elif defined(__CRT_HAVE_re_syntax_options)
__CSDECLARE(,reg_syntax_t,re_syntax_options)
#define re_syntax_options re_syntax_options
#endif /* ... */
#endif /* !re_syntax_options */

#ifdef __CRT_HAVE_re_set_syntax
/* >> re_set_syntax(3)
 * Set  the  regex  syntax used  by  `re_compile_pattern(3)', and
 * return the old default syntax (same as `re_syntax_options(3)') */
__CDECLARE(,reg_syntax_t,__NOTHROW_NCX,re_set_syntax,(reg_syntax_t __syntax),(__syntax))
#else /* __CRT_HAVE_re_set_syntax */
#include <libc/template/re_syntax_options.h>
#ifdef __LOCAL_re_syntax_options
#include <libc/local/regex/re_set_syntax.h>
/* >> re_set_syntax(3)
 * Set  the  regex  syntax used  by  `re_compile_pattern(3)', and
 * return the old default syntax (same as `re_syntax_options(3)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(re_set_syntax, __FORCELOCAL __ATTR_ARTIFICIAL reg_syntax_t __NOTHROW_NCX(__LIBCCALL re_set_syntax)(reg_syntax_t __syntax) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(re_set_syntax))(__syntax); })
#endif /* __LOCAL_re_syntax_options */
#endif /* !__CRT_HAVE_re_set_syntax */
/* >> re_compile_pattern(3)
 * Compile a regular expression pattern (s.a. re_compiler_compile(3R)')
 * @param: pattern: Regex pattern string
 * @param: length:  Length of regex pattern string (in bytes)
 * @param: self:    The `regex_t' object to initialize.
 * @return: NULL:   Success
 * @return: * :     An error message, as would be produced by `regerror(3)' */
__CDECLARE_OPT(__ATTR_INS(1, 2) __ATTR_OUT(3),char const *,__NOTHROW_NCX,re_compile_pattern,(char const *__pattern, size_t __length, regex_t *__self),(__pattern,__length,__self))
#ifdef __CRT_HAVE_re_compile_fastmap
/* >> re_compile_fastmap(3)
 * Compile the fast-map of `self'. No-op on KOS, where the fastmap is always compiled immediatly.
 * @return: 0 : Always returns `0' */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,re_compile_fastmap,(regex_t *__self),(__self))
#else /* __CRT_HAVE_re_compile_fastmap */
#include <libc/local/regex/re_compile_fastmap.h>
/* >> re_compile_fastmap(3)
 * Compile the fast-map of `self'. No-op on KOS, where the fastmap is always compiled immediatly.
 * @return: 0 : Always returns `0' */
__NAMESPACE_LOCAL_USING_OR_IMPL(re_compile_fastmap, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL re_compile_fastmap)(regex_t *__self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(re_compile_fastmap))(__self); })
#endif /* !__CRT_HAVE_re_compile_fastmap */
#ifdef __CRT_HAVE_re_search
/* >> re_search(3)
 * Perform a regex search for the first matching byte-offset in `[start,start+range)'.
 * The  accessed area of  the input buffer  is restricted to `[string,string+length)'.
 * @param: self:   The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                  - `REG_NOTBOL = self->__not_bol'
 *                  - `REG_NOTEOL = self->__not_eol'
 *                 Sadly, this make this interface really badly designed, as this choice
 *                 (which was made by Glibc  btw), prevents multiple threads from  using
 *                 the same `regex_t' buffer simultaneously. Though note that this  same
 *                 restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                 if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                 the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string: Base pointer for input data.
 * @param: length: Length of input data (in bytes)
 * @param: start:  Starting offset where to begin searching
 * @param: range:  The max # of searches to attempt at successive byte-offsets starting at `start'
 * @param: regs:   Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @return: >= 0:  Was able to discover a match at this offset. (always `< range')
 * @return: -1:    No match was found
 * @return: -2:    Internal error (probably meaning out-of-memory) */
__CDECLARE(__ATTR_IN(1) __ATTR_INS(2, 3) __ATTR_OUT_OPT(6),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,re_search,(regex_t __KOS_FIXED_CONST *__self, char const *__string, __STDC_INT_AS_SIZE_T __length, __STDC_INT_AS_SIZE_T __start, __STDC_INT_AS_SIZE_T __range, struct __re_registers *__regs),(__self,__string,__length,__start,__range,__regs))
#elif defined(__CRT_HAVE_re_search_2)
#include <libc/local/regex/re_search.h>
/* >> re_search(3)
 * Perform a regex search for the first matching byte-offset in `[start,start+range)'.
 * The  accessed area of  the input buffer  is restricted to `[string,string+length)'.
 * @param: self:   The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                  - `REG_NOTBOL = self->__not_bol'
 *                  - `REG_NOTEOL = self->__not_eol'
 *                 Sadly, this make this interface really badly designed, as this choice
 *                 (which was made by Glibc  btw), prevents multiple threads from  using
 *                 the same `regex_t' buffer simultaneously. Though note that this  same
 *                 restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                 if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                 the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string: Base pointer for input data.
 * @param: length: Length of input data (in bytes)
 * @param: start:  Starting offset where to begin searching
 * @param: range:  The max # of searches to attempt at successive byte-offsets starting at `start'
 * @param: regs:   Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @return: >= 0:  Was able to discover a match at this offset. (always `< range')
 * @return: -1:    No match was found
 * @return: -2:    Internal error (probably meaning out-of-memory) */
__NAMESPACE_LOCAL_USING_OR_IMPL(re_search, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INS(2, 3) __ATTR_OUT_OPT(6) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL re_search)(regex_t __KOS_FIXED_CONST *__self, char const *__string, __STDC_INT_AS_SIZE_T __length, __STDC_INT_AS_SIZE_T __start, __STDC_INT_AS_SIZE_T __range, struct __re_registers *__regs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(re_search))(__self, __string, __length, __start, __range, __regs); })
#endif /* ... */
/* >> re_search_2(3)
 * Same as `re_search(3)',  but use the  virtual concatenation of  `string1...+=length1'
 * and  `string2...+=length2' as input  buffer. Also: use `stop'  as the end-offset into
 * this  virtual buffer of where to stop  doing non-extra accessing accesses (extra data
 * accesses are positional assertion checks at the end of the regex pattern, such as '$'
 * checking  if it is followed by a line-feed being allowed to read until the actual end
 * of the virtual buffer,  whilst actual byte-matching is  only allowed to happen  until
 * an offset of `stop' bytes has been reached)
 *
 * Note that on KOS, the underlying API used is `re_exec_search(3R)' from `libregex.so'
 * and exposed in `<libregex/regexec.h>', which allows for the virtual concatenation of
 * not just 2, but an arbitrary number of buffers which are then used as input.
 *
 * @param: self:    The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                   - `REG_NOTBOL = self->__not_bol'
 *                   - `REG_NOTEOL = self->__not_eol'
 *                  Sadly, this make this interface really badly designed, as this choice
 *                  (which was made by Glibc  btw), prevents multiple threads from  using
 *                  the same `regex_t' buffer simultaneously. Though note that this  same
 *                  restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                  if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                  the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string1: First base pointer for input data.
 * @param: length1: Length of first input data (in bytes)
 * @param: string2: Second base pointer for input data.
 * @param: length2: Length of second input data (in bytes)
 * @param: start:   Starting offset where to begin searching
 * @param: range:   The max # of searches to attempt at successive byte-offsets starting at `start'
 * @param: regs:    Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @param: stop:    Offset into the virtual input buffer that marks its end (must be `<= length1+length2')
 * @return: >= 0:   Was able to discover a match at this offset. (always `< range')
 * @return: -1:     No match was found
 * @return: -2:     Internal error (probably meaning out-of-memory) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_INS(2, 3) __ATTR_INS(4, 5) __ATTR_OUT_OPT(8),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,re_search_2,(regex_t __KOS_FIXED_CONST *__self, char const *__string1, __STDC_INT_AS_SIZE_T __length1, char const *__string2, __STDC_INT_AS_SIZE_T __length2, __STDC_INT_AS_SIZE_T __start, __STDC_INT_AS_SIZE_T __range, struct __re_registers *__regs, __STDC_INT_AS_SIZE_T __stop),(__self,__string1,__length1,__string2,__length2,__start,__range,__regs,__stop))
#ifdef __CRT_HAVE_re_match
/* >> re_match(3)
 * Match input data `[string+start,string+length)' against the regex pattern `self'
 * The accessed area of the input buffer is restricted to `[string,string+length)'.
 * @param: self:   The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                  - `REG_NOTBOL = self->__not_bol'
 *                  - `REG_NOTEOL = self->__not_eol'
 *                 Sadly, this make this interface really badly designed, as this choice
 *                 (which was made by Glibc  btw), prevents multiple threads from  using
 *                 the same `regex_t' buffer simultaneously. Though note that this  same
 *                 restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                 if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                 the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string: Base pointer for input data.
 * @param: length: Length of input data (in bytes)
 * @param: start:  Starting offset where to begin searching
 * @param: regs:   Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @return: >= 0:  The number of bytes starting at `start' that were matched against `self'
 * @return: -1:    No match was found
 * @return: -2:    Internal error (probably meaning out-of-memory) */
__CDECLARE(__ATTR_IN(1) __ATTR_INS(2, 3) __ATTR_OUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,re_match,(regex_t __KOS_FIXED_CONST *__self, char const *__string, __STDC_INT_AS_SIZE_T __length, __STDC_INT_AS_SIZE_T __start, struct __re_registers *__regs),(__self,__string,__length,__start,__regs))
#elif defined(__CRT_HAVE_re_match_2)
#include <libc/local/regex/re_match.h>
/* >> re_match(3)
 * Match input data `[string+start,string+length)' against the regex pattern `self'
 * The accessed area of the input buffer is restricted to `[string,string+length)'.
 * @param: self:   The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                  - `REG_NOTBOL = self->__not_bol'
 *                  - `REG_NOTEOL = self->__not_eol'
 *                 Sadly, this make this interface really badly designed, as this choice
 *                 (which was made by Glibc  btw), prevents multiple threads from  using
 *                 the same `regex_t' buffer simultaneously. Though note that this  same
 *                 restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                 if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                 the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string: Base pointer for input data.
 * @param: length: Length of input data (in bytes)
 * @param: start:  Starting offset where to begin searching
 * @param: regs:   Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @return: >= 0:  The number of bytes starting at `start' that were matched against `self'
 * @return: -1:    No match was found
 * @return: -2:    Internal error (probably meaning out-of-memory) */
__NAMESPACE_LOCAL_USING_OR_IMPL(re_match, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INS(2, 3) __ATTR_OUT_OPT(5) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL re_match)(regex_t __KOS_FIXED_CONST *__self, char const *__string, __STDC_INT_AS_SIZE_T __length, __STDC_INT_AS_SIZE_T __start, struct __re_registers *__regs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(re_match))(__self, __string, __length, __start, __regs); })
#endif /* ... */
/* >> re_match_2(3)
 * Same  as `re_match(3)',  but use  the virtual  concatenation of `string1...+=length1'
 * and  `string2...+=length2' as input  buffer. Also: use `stop'  as the end-offset into
 * this  virtual buffer of where to stop  doing non-extra accessing accesses (extra data
 * accesses are positional assertion checks at the end of the regex pattern, such as '$'
 * checking  if it is followed by a line-feed being allowed to read until the actual end
 * of the virtual buffer,  whilst actual byte-matching is  only allowed to happen  until
 * an offset of `stop' bytes has been reached)
 *
 * Note that on KOS, the underlying API used is `re_exec_match(3R)' from  `libregex.so'
 * and exposed in `<libregex/regexec.h>', which allows for the virtual concatenation of
 * not just 2, but an arbitrary number of buffers which are then used as input.
 *
 * @param: self:    The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                   - `REG_NOTBOL = self->__not_bol'
 *                   - `REG_NOTEOL = self->__not_eol'
 *                  Sadly, this make this interface really badly designed, as this choice
 *                  (which was made by Glibc  btw), prevents multiple threads from  using
 *                  the same `regex_t' buffer simultaneously. Though note that this  same
 *                  restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                  if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                  the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string1: First base pointer for input data.
 * @param: length1: Length of first input data (in bytes)
 * @param: string2: Second base pointer for input data.
 * @param: length2: Length of second input data (in bytes)
 * @param: start:   Starting offset where to begin searching
 * @param: range:   The max # of searches to attempt at successive byte-offsets starting at `start'
 * @param: regs:    Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @param: stop:    Offset into the virtual input buffer that marks its end (must be `<= length1+length2')
 * @return: >= 0:   The number of bytes starting at `start' that were matched against `self'
 * @return: -1:     No match was found
 * @return: -2:     Internal error (probably meaning out-of-memory) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_INS(2, 3) __ATTR_INS(4, 5) __ATTR_OUT_OPT(7),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,re_match_2,(regex_t __KOS_FIXED_CONST *__self, char const *__string1, __STDC_INT_AS_SIZE_T __length1, char const *__string2, __STDC_INT_AS_SIZE_T __length2, __STDC_INT_AS_SIZE_T __start, struct __re_registers *__regs, __STDC_INT_AS_SIZE_T __stop),(__self,__string1,__length1,__string2,__length2,__start,__regs,__stop))
#ifdef __CRT_HAVE_re_set_registers
/* >> re_set_registers(3)
 * Initializes `regs', and sets some weird internal flag in `self' (which it doesn't do on KOS) */
__CDECLARE_VOID(__ATTR_INOUT(1) __ATTR_OUT(2),__NOTHROW_NCX,re_set_registers,(regex_t *__self, struct __re_registers *__regs, unsigned int __num_regs, regoff_t *__starts, regoff_t *__ends),(__self,__regs,__num_regs,__starts,__ends))
#else /* __CRT_HAVE_re_set_registers */
#include <libc/local/regex/re_set_registers.h>
/* >> re_set_registers(3)
 * Initializes `regs', and sets some weird internal flag in `self' (which it doesn't do on KOS) */
__NAMESPACE_LOCAL_USING_OR_IMPL(re_set_registers, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_OUT(2) void __NOTHROW_NCX(__LIBCCALL re_set_registers)(regex_t *__self, struct __re_registers *__regs, unsigned int __num_regs, regoff_t *__starts, regoff_t *__ends) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(re_set_registers))(__self, __regs, __num_regs, __starts, __ends); })
#endif /* !__CRT_HAVE_re_set_registers */
#endif /* __USE_GNU */

/************************************************************************/
/* STANDARD POSIX REGEX FUNCTIONS                                       */
/************************************************************************/

/* >> regcomp(3)
 * Compile a regular expression `pattern' and initialize `self'
 * @param: self:    Storage for the produced regex pattern.
 * @param: pattern: The pattern to compile.
 * @param: cflags:  Set of `REG_EXTENDED | REG_ICASE | REG_NEWLINE | REG_NOSUB'
 * @return: REG_NOERROR: Success
 * @return: REG_BADPAT:  General pattern syntax error.
 * @return: REG_ECTYPE:  Invalid/unknown character class name.
 * @return: REG_EESCAPE: Trailing backslash.
 * @return: REG_ESUBREG: Invalid back reference.
 * @return: REG_EBRACK:  Unmatched '['.
 * @return: REG_EPAREN:  Unmatched '('.
 * @return: REG_EBRACE:  Unmatched '{'.
 * @return: REG_BADBR:   Invalid contents of '{...}'.
 * @return: REG_ERANGE:  Invalid range end (e.g. '[z-a]').
 * @return: REG_ESPACE:  Out of memory.
 * @return: REG_BADRPT:  Nothing is preceding '+', '*', '?' or '{'.
 * @return: REG_EEND:    Unexpected end of pattern.
 * @return: REG_ESIZE:   Compiled pattern bigger than 2^16 bytes.
 * @return: REG_ERPAREN: Unmatched ')' (only when `RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD' was set)
 * @return: REG_EILLSET: Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]")
 * @return: REG_ENOSYS:  Unable to load `libregex.so' (shouldn't happen) */
__CDECLARE_OPT(__ATTR_IN(2) __ATTR_OUT(1),int,__NOTHROW_NCX,regcomp,(regex_t *__restrict __self, char const *__restrict __pattern, int __cflags),(__self,__pattern,__cflags))
/* >> regcomp(3)
 * Compile a regular expression `pattern' and initialize `self'
 * @param: self:   Storage for the produced regex pattern.
 * @param: string: Input data base pointer (must be a NUL-terminated string, unless `REG_STARTEND' is given)
 * @param: nmatch: Max # of group start/end-offsets to write to `*pmatch' (ignored if `REG_NOSUB' was set)
 * @param: pmatch: Storage for at least `nmatch' group start/end-offsets (ignored if `REG_NOSUB' was set)
 * @param: eflags: Set of `REG_NOTBOL | REG_NOTEOL | REG_STARTEND'
 * @return: REG_NOERROR: Success
 * @return: REG_NOMATCH: General pattern syntax error.
 * @return: REG_ESPACE:  Out of memory.
 * @return: REG_ENOSYS:  Unable to load `libregex.so' (shouldn't happen) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_INOUTS(4, 3),int,__NOTHROW_NCX,regexec,(regex_t const *__restrict __self, char const *__restrict __string, size_t __nmatch, regmatch_t __pmatch[__restrict_arr], int __eflags),(__self,__string,__nmatch,__pmatch,__eflags))
#ifdef __CRT_HAVE_regerror
/* >> regerror(3)
 * Produce a human-readable description for a regex error code `errcode' (s.a. `regerrordesc_np(3)')
 * @param: errcode: Regex error code (one of `REG_*'; s.a. `reg_errcode_t')
 * @param: self:    The compiled regex pattern that produced the error (unused in this impl)
 * @return: * :     The required buffer size (including a trailing '\0'-byte) */
__CDECLARE(__ATTR_IN(2) __ATTR_OUTS(3, 4),size_t,__NOTHROW_NCX,regerror,(int __errcode, regex_t const *__restrict __self, char *__restrict __errbuf, size_t __errbuf_size),(__errcode,__self,__errbuf,__errbuf_size))
#else /* __CRT_HAVE_regerror */
#include <libc/local/regex/regerror.h>
/* >> regerror(3)
 * Produce a human-readable description for a regex error code `errcode' (s.a. `regerrordesc_np(3)')
 * @param: errcode: Regex error code (one of `REG_*'; s.a. `reg_errcode_t')
 * @param: self:    The compiled regex pattern that produced the error (unused in this impl)
 * @return: * :     The required buffer size (including a trailing '\0'-byte) */
__NAMESPACE_LOCAL_USING_OR_IMPL(regerror, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(3, 4) size_t __NOTHROW_NCX(__LIBCCALL regerror)(int __errcode, regex_t const *__restrict __self, char *__restrict __errbuf, size_t __errbuf_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(regerror))(__errcode, __self, __errbuf, __errbuf_size); })
#endif /* !__CRT_HAVE_regerror */
#ifdef __CRT_HAVE_regfree
/* >> regfree(3)
 * Free dynamic memory allocated during a successful call to `regcomp(3)'
 * @param: self: The compiled regex pattern to destroy */
__CDECLARE_VOID(,__NOTHROW_NCX,regfree,(regex_t *__self),(__self))
#elif (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)) && defined(__CRT_KOS)
#include <libc/local/regex/regfree.h>
/* >> regfree(3)
 * Free dynamic memory allocated during a successful call to `regcomp(3)'
 * @param: self: The compiled regex pattern to destroy */
__NAMESPACE_LOCAL_USING_OR_IMPL(regfree, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL regfree)(regex_t *__self) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(regfree))(__self); })
#endif /* ... */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_regerrordesc_np
/* >> regerrordesc_np(3)
 * Return a human-readable description for a given regex `errcode'
 * @param: errcode: Regex error code (one of `REG_*'; s.a. `reg_errcode_t')
 * @return: * :   The human-readable description for `errcode'
 * @return: NULL: No description is available for `errcode' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,regerrordesc_np,(int __errcode),(__errcode))
#else /* __CRT_HAVE_regerrordesc_np */
#include <libc/local/regex/regerrordesc_np.h>
/* >> regerrordesc_np(3)
 * Return a human-readable description for a given regex `errcode'
 * @param: errcode: Regex error code (one of `REG_*'; s.a. `reg_errcode_t')
 * @return: * :   The human-readable description for `errcode'
 * @return: NULL: No description is available for `errcode' */
__NAMESPACE_LOCAL_USING_OR_IMPL(regerrordesc_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL regerrordesc_np)(int __errcode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(regerrordesc_np))(__errcode); })
#endif /* !__CRT_HAVE_regerrordesc_np */
#endif /* __USE_KOS */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_REGEX_H */
