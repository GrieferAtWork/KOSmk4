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

%[define_replacement(errno_t = __errno_t)]
%[define_replacement(s_reg_t = __LONGPTR_TYPE__)]
%[define_replacement(active_reg_t = __ULONGPTR_TYPE__)]
%[define_replacement(reg_syntax_t = __ULONGPTR_TYPE__)]
%[define_replacement(regmatch_t = regmatch_t)]
%[define_replacement(regex_t = "struct re_pattern_buffer")]
%[define_replacement(regoff_t = __INT32_TYPE__)]

%[default:section(".text.crt{|.dos}.utility.regex")]

%{
#include <features.h>

#include <hybrid/typecore.h>
#include <asm/crt/limits.h> /* __RE_DUP_MAX */
#include <sys/types.h>

/* NOTE: On KOS, regex is implemented by a dedicated library that gets loaded by libc
 *       once  the demand to do so comes up,  in order to emulate POSIX and GNU regex
 *       functionality. If you intend on making use of this library, its main  header
 *       can be included as `<libregex/regex.h>' */


/* The documentation of functions is taken from GLibc /usr/include/regex.h */
/* Definitions for data structures and routines for the regular
   expression library.
   Copyright (C) 1985, 1989-2017 Free Software Foundation, Inc.
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
typedef __LONGPTR_TYPE__ s_reg_t;
typedef __ULONGPTR_TYPE__ active_reg_t;
typedef __ULONGPTR_TYPE__ reg_syntax_t; /* Set of `RE_*' (see below) */
#endif /* __CC__ */

#ifdef __USE_GNU
/* Linux-compatible regex syntax flags */
#define RE_BACKSLASH_ESCAPE_IN_LISTS 0x00000001 /* == !REGEX_FLAG_NO_BACKSLASH_IN_RANGES */
#define RE_BK_PLUS_QM                0x00000002 /* == REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK */
#define RE_CHAR_CLASSES              0x00000004 /* == !REGEX_FLAG_NO_CHARACTER_CLASSES */
#define RE_CONTEXT_INDEP_ANCHORS     0x00000008 /* == !REGEX_FLAG_CONTEXT_DEPENDENT_START_END */
#define RE_CONTEXT_INDEP_OPS         0x00000010 /* == !(REGEX_FLAG_CONTEXT_DEPENDENT_RANGES|REGEX_FLAG_CONTEXT_DEPENDENT_GROUPS) */
#define RE_CONTEXT_INVALID_OPS       0x00000020 /* == !REGEX_FLAG_CONTEXT_DEPENDENT_REPEAT */
#define RE_DOT_NEWLINE               0x00000040 /* == REGEX_FLAG_DOTLF */
#define RE_DOT_NOT_NULL              0x00000080 /* == !REGEX_FLAG_DOTNUL */
#define RE_HAT_LISTS_NOT_NEWLINE     0x00000100 /* == REGEX_FLAG_RANGE_NOT_NEWLINE */
#define RE_INTERVALS                 0x00000200 /* == !REGEX_FLAG_NO_INTERVALS */
#define RE_LIMITED_OPS               0x00000400 /* == REGEX_FLAG_LIMITED_OPERATORS */
#define RE_NEWLINE_ALT               0x00000800 /* == REGEX_FLAG_NEWLINE_IS_PIPE */
#define RE_NO_BK_BRACES              0x00001000 /* == !REGEX_FLAG_ESCAPED_INTERVALS */
#define RE_NO_BK_PARENS              0x00002000 /* == !REGEX_FLAG_ESCAPED_GROUPS */
#define RE_NO_BK_REFS                0x00004000 /* Unsupported (behavior emulates this flag always being set; s.a. `REGEX_FLAG_NO_BACKSLASH_DIGIT') */
#define RE_NO_BK_VBAR                0x00008000 /* == !REGEX_FLAG_ESCAPED_PIPE */
#define RE_NO_EMPTY_RANGES           0x00010000 /* == !REGEX_FLAG_ALLOW_EMPTY_RANGES */
#define RE_UNMATCHED_RIGHT_PAREN_ORD 0x00020000 /* == REGEX_FLAG_CONTEXT_DEPENDENT_GROUPS */
#define RE_NO_POSIX_BACKTRACKING     0x00040000 /* Unsupported (Because I don't really understand what this flag is meant to do...) */
#define RE_NO_GNU_OPS                0x00080000 /* Unsupported (Because I don't know which operators are consider ~GNU extensions~) */
#define RE_DEBUG                     0x00100000 /* Unsupported */
#define RE_INVALID_INTERVAL_ORD      0x00200000 /* == REGEX_FLAG_IGNORE_INVALID_INTERVALS */
#define RE_ICASE                     0x00400000 /* == REGEX_FLAG_NOCASE */
#define RE_CARET_ANCHORS_HERE        0x00800000 /* == !REGEX_FLAG_CONTEXT_DEPENDENT_START_END (Implemented as alias for `RE_CONTEXT_INDEP_ANCHORS') */
#define RE_CONTEXT_INVALID_DUP       0x01000000 /* Unsupported (Because I don't really understand what this flag is meant to do...) */
#define RE_NO_SUB                    0x02000000 /* Unsupported (Because I don't really understand the actual purpose of this flag...) */
#endif /* __USE_GNU */

#ifdef __CRT_HAVE_re_syntax_options
/* Regex syntax used by certain interfaces. */
__CSDECLARE(,reg_syntax_t,re_syntax_options)
#endif /* __CRT_HAVE_re_syntax_options */

#ifdef __USE_GNU
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
#endif /* __USE_GNU */

/* Flags for `regcomp(3)'s `cflags' argument.
 * NOTE: REG_EXTENDED does the following:
 *  - Enable support for [:class:] (as opposed to being the
 *    equivalent  of  "[:clas]", aka  regular set-matching)
 *  - . matches \n  (as opposed to it not doing so)
 *  - . doesn't match \0  (as opposed to it doing so)
 *  - f{0-3} interval matching (as opposed to the equivalent of "f\{0-3\}")
 *  - [z-a] is invalid  (as opposed to never matched)
 *  - ^  and $ are  always matched as operators  (as opposed to only
 *    at the start or end of a pattern, and in "abc(^foo$|^bar$)def"
 *  - *, + and ? are always special (as opposed to only as a suffix;
 *    aka. in  non-suffix  places  using  these  becomes  an  error)
 *  - (foo|bar) groups and |-alternatives are supported (as
 *    opposed to  being the  equivalent of  "\(foo\|bar\)")
 *     - An unmatched ) is still allowed to be parsed as \), without causing an error
 *  - {, +, * or ? cannot appear at the start of a pattern, or after ( or |, as
 *    opposed to being processed like regular match-characters in these locations. */
#define REG_EXTENDED 0x0001 /* Use `RE_SYNTAX_POSIX_MINIMAL_BASIC' instead of `RE_SYNTAX_POSIX_BASIC' */
#define REG_ICASE    0x0002 /* == REGEX_FLAG_NOCASE
                             * Ignore casing during matching */
#define REG_NEWLINE  0x0004 /* == !REGEX_FLAG_MULTILINE
                             * ^ and $  don't match after/before  line-feeds,
                             * but only at the start/end of regex input data. */
#define REG_NOSUB    0x0008 /* If set:   Only return success/failure in regexec.
                             * If clear: Return success/failure/error in regexec. */

/* Flags for `regexec(3)'s `eflags' argument. */
#define REG_NOTBOL   0x0001 /* == REGEX_FLAG_NOT_BEGIN_OF_LINE
                             * ^ doesn't match the start of input data (but only at an actual begin-of-line) */
#define REG_NOTEOL   0x0002 /* == REGEX_FLAG_NOT_END_OF_LINE
                             * $ doesn't match the end of input data (but only before an actual line-feed) */
#define REG_STARTEND 0x0004 /* Use PMATCH[0] to delimit the start and end of the search in the buffer. */

/* If any error codes are removed, changed, or added, update the
   `re_error_msg' table in regex.c. */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum {
#if defined(_XOPEN_SOURCE) || defined(__USE_XOPEN2K)
	REG_ENOSYS   = -1, /* Returned when libc.so fails to load `libregex.so' for some reason */
#endif /* _XOPEN_SOURCE || __USE_XOPEN2K */
	REG_NOERROR  = 0,  /* Success. */
	REG_NOMATCH  = 1,  /* Didn't find a match (for regexec). */

	/* POSIX */
	REG_BADPAT   = 2,  /* Invalid pattern. */
	REG_ECOLLATE = 3,  /* Inalid collating element. */
	REG_ECTYPE   = 4,  /* Invalid character class name. */
	REG_EESCAPE  = 5,  /* Trailing backslash. */
	REG_ESUBREG  = 6,  /* Invalid back reference. */
	REG_EBRACK   = 7,  /* Unmatched left bracket. */
	REG_EPAREN   = 8,  /* Parenthesis imbalance. */
	REG_EBRACE   = 9,  /* Unmatched \{. */
	REG_BADBR    = 10, /* Invalid contents of \{\}. */
	REG_ERANGE   = 11, /* Invalid range end. */
	REG_ESPACE   = 12, /* Ran out of memory. */
	REG_BADRPT   = 13, /* No preceding re for repetition op. */

	/* GNU-specific errors */
	REG_EEND     = 14, /* Premature end. */
	REG_ESIZE    = 15, /* Compiled pattern bigger than 2^16 bytes. */
	REG_ERPAREN  = 16  /* Unmatched ) or \); not returned from regcomp. */
} reg_errcode_t;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if defined(_XOPEN_SOURCE) || defined(__USE_XOPEN2K)
#define REG_ENOSYS   REG_ENOSYS   /* Returned when libc.so fails to load `libregex.so' for some reason */
#endif /* _XOPEN_SOURCE || __USE_XOPEN2K */
#define REG_NOERROR  REG_NOERROR  /* Success. */
#define REG_NOMATCH  REG_NOMATCH  /* Didn't find a match (for regexec). */
/* POSIX */
#define REG_BADPAT   REG_BADPAT   /* Invalid pattern. */
#define REG_ECOLLATE REG_ECOLLATE /* Inalid collating element. */
#define REG_ECTYPE   REG_ECTYPE   /* Invalid character class name. */
#define REG_EESCAPE  REG_EESCAPE  /* Trailing backslash. */
#define REG_ESUBREG  REG_ESUBREG  /* Invalid back reference. */
#define REG_EBRACK   REG_EBRACK   /* Unmatched left bracket. */
#define REG_EPAREN   REG_EPAREN   /* Parenthesis imbalance. */
#define REG_EBRACE   REG_EBRACE   /* Unmatched \{. */
#define REG_BADBR    REG_BADBR    /* Invalid contents of \{\}. */
#define REG_ERANGE   REG_ERANGE   /* Invalid range end. */
#define REG_ESPACE   REG_ESPACE   /* Ran out of memory. */
#define REG_BADRPT   REG_BADRPT   /* No preceding re for repetition op. */
/* GNU-specific errors */
#define REG_EEND     REG_EEND     /* Premature end. */
#define REG_ESIZE    REG_ESIZE    /* Compiled pattern bigger than 2^16 bytes. */
#define REG_ERPAREN  REG_ERPAREN  /* Unmatched ) or \); not returned from regcomp. */
#else /* __COMPILER_PREFERR_ENUMS */
#if defined(_XOPEN_SOURCE) || defined(__USE_XOPEN2K)
#define REG_ENOSYS   (-1) /* Returned when libc.so fails to load `libregex.so' for some reason */
#endif /* _XOPEN_SOURCE || __USE_XOPEN2K */
#define REG_NOERROR  0    /* Success. */
#define REG_NOMATCH  1    /* Didn't find a match (for regexec). */
/* POSIX */
#define REG_BADPAT   2    /* Invalid pattern. */
#define REG_ECOLLATE 3    /* Inalid collating element. */
#define REG_ECTYPE   4    /* Invalid character class name. */
#define REG_EESCAPE  5    /* Trailing backslash. */
#define REG_ESUBREG  6    /* Invalid back reference. */
#define REG_EBRACK   7    /* Unmatched left bracket. */
#define REG_EPAREN   8    /* Parenthesis imbalance. */
#define REG_EBRACE   9    /* Unmatched \{. */
#define REG_BADBR    10   /* Invalid contents of \{\}. */
#define REG_ERANGE   11   /* Invalid range end. */
#define REG_ESPACE   12   /* Ran out of memory. */
#define REG_BADRPT   13   /* No preceding re for repetition op. */
/* GNU-specific errors */
#define REG_EEND     14   /* Premature end. */
#define REG_ESIZE    15   /* Compiled pattern bigger than 2^16 bytes. */
#define REG_ERPAREN  16   /* Unmatched ) or \); not returned from regcomp. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


#ifndef __RE_TRANSLATE_TYPE
#define __RE_TRANSLATE_TYPE unsigned char *
#endif /* !__RE_TRANSLATE_TYPE */
#ifdef __USE_GNU
#ifndef RE_TRANSLATE_TYPE
#define RE_TRANSLATE_TYPE __RE_TRANSLATE_TYPE
#endif /* !RE_TRANSLATE_TYPE */
#endif /* __USE_GNU */

#ifdef __USE_GNU
#define __REPB_PREFIX(name) name
#else
#define __REPB_PREFIX(name) __##name
#endif


#ifdef __USE_GNU
#define REGS_UNALLOCATED 0
#define REGS_REALLOCATE  1
#define REGS_FIXED       2
#endif

#ifdef __CC__
struct re_pattern_buffer {
	/* KOS doesn't  use any  of this  stuff. -  On KOS,  regex expressions  are
	 * evaluated in interpreted mode (aka.: there is no intermediate  bytecode)
	 * However, in the interest of future compatibility, I do reserve the right
	 * to implement a bytecode sub-system at some point in the future if I find
	 * sufficient reason to do this. */
	unsigned char *__REPB_PREFIX(buffer);
	__ULONG32_TYPE__ __REPB_PREFIX(allocated);
	__ULONG32_TYPE__ __REPB_PREFIX(used);
	reg_syntax_t __REPB_PREFIX(syntax);
	char *__REPB_PREFIX(fastmap);
	__RE_TRANSLATE_TYPE __REPB_PREFIX(translate);
	__size_t re_nsub;
	unsigned __REPB_PREFIX(can_be_null) : 1;
	unsigned __REPB_PREFIX(regs_allocated) : 2;
	unsigned __REPB_PREFIX(fastmap_accurate) : 1;
	unsigned __REPB_PREFIX(no_sub) : 1;
	unsigned __REPB_PREFIX(not_bol) : 1;
	unsigned __REPB_PREFIX(not_eol) : 1;
	unsigned __REPB_PREFIX(newline_anchor) : 1;
};
typedef struct re_pattern_buffer regex_t;
typedef __INT32_TYPE__ regoff_t;

#ifdef __USE_GNU
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("num_regs")
#pragma push_macro("start")
#pragma push_macro("end")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef num_regs
#undef start
#undef end
struct re_registers {
	__UINT32_TYPE__ num_regs;
	regoff_t       *start;
	regoff_t       *end;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("end")
#pragma pop_macro("start")
#pragma pop_macro("num_regs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifndef RE_NREGS
#define RE_NREGS 30
#endif /* !RE_NREGS */
#endif /* __USE_GNU */

typedef struct {
	regoff_t rm_so; /* Byte offset to the start of the match. */
	regoff_t rm_eo; /* Byte offset to the end of the match. */
} regmatch_t;

#endif /* __CC__ */

/* #undef __REPB_PREFIX // Not undef'ed by GLibc, either... */

#ifdef __CC__

}

%#ifdef __USE_GNU

@@Sets the current default syntax to `syntax', and return the old syntax.
@@You  can  also  simply  assign  to  the  `re_syntax_options'   variable
reg_syntax_t re_set_syntax(reg_syntax_t syntax);

@@Compile   the   regular  expression   `pattern',  with   length  `length'
@@and  syntax  given by  the  global `re_syntax_options',  into  the buffer
@@`buffer'.  Return  NULL  if  successful,  and  an  error  string  if not.
@@To  free  the allocated  storage, you  must  call `regfree'  on `buffer'.
@@Note  that  the  translate table  must  either have  been  initialized by
@@`regcomp', with a malloc'd value, or set to NULL before calling `regfree'
char const *re_compile_pattern(char const *pattern, size_t length,
                               struct re_pattern_buffer *buffer);

@@Compile  a  fastmap   for  the   compiled  pattern  in   `buffer';  used   to
@@accelerate searches. Return 0 if successful and `-2' if was an internal error
int re_compile_fastmap(struct re_pattern_buffer *buffer);

@@Search in the  string `string'  (with length `length')  for the  pattern
@@compiled into `buffer'. Start searching at position `start', for `range'
@@characters.  Return  the starting  position of  the  match, `-1'  for no
@@match,  or   `-2'  for   an  internal   error.  Also   return   register
@@information in  `regs'  (if  `regs' and  `buffer'->no_sub  are  nonzero)
int re_search(struct re_pattern_buffer *buffer, char const *string,
              int length, int start, int range, struct re_registers *regs);

@@Like `re_search', but search in the concatenation of `string1'
@@and `string2'. Also,  stop searching  at index  `start + stop'
int re_search_2(struct re_pattern_buffer *buffer, char const *string1, int length1,
                char const *string2, int length2, int start, int range,
                struct re_registers *regs, int stop);

@@Like `re_search', but return how many characters in `string'
@@the regexp in `buffer' matched, starting at position `start'
int re_match(struct re_pattern_buffer *buffer, char const *string,
             int length, int start, struct re_registers *regs);

@@Relates to `re_match' as `re_search_2' relates to `re_search'
int re_match_2(struct re_pattern_buffer *buffer, char const *string1,
               int length1, char const *string2, int length2, int start,
               struct re_registers *regs, int stop);

@@Set  `regs'   to  hold   `num_regs'  registers,   storing  them   in  `starts'   and
@@`ends'.   Subsequent  matches  using  `buffer'  and  `regs'  will  use  this  memory
@@for  recording  register  information.  `starts'   and  `ends'  must  be   allocated
@@with  malloc, and must each be at  least ``num_regs' * sizeof(regoff_t)' bytes long.
@@If `num_regs == 0', then subsequent matches should allocate their own register data.
@@Unless this function is called, the first search or match using
@@PATTERN_BUFFER will allocate its own register data, without freeing the old data
void re_set_registers(struct re_pattern_buffer *buffer, struct re_registers *regs,
                      unsigned int num_regs, regoff_t *starts, regoff_t *ends);
%#endif /* __USE_GNU */

%
%
%/* POSIX compatibility.  */

int regcomp(regex_t *__restrict preg, char const *__restrict pattern, int cflags);
int regexec(regex_t const *__restrict preg, char const *__restrict string,
            size_t nmatch, regmatch_t pmatch[__restrict_arr], int eflags);
size_t regerror(int errcode, regex_t const *__restrict preg,
                char *__restrict errbuf, size_t errbuf_size);
void regfree(regex_t *preg);

%{

#endif /* __CC__ */

__SYSDECL_END

}
